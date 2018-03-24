#include "c4d_general.h"
#include "c4d_memory.h"
#include "c4d_gui.h"

#include "x4d_filter.h"
#include "c4d_bitmapfilter.h"
#include "linefetchutil.h"

struct	ROW_BLOCK
{
	ROW_BLOCK* next;

	BM_TILE*	 tile;
	Int32			 xymin;			// first line
	Int32			 xymax;			// last line
	Int32			 ref;				// usage counter
	Bool			 is_static;	// true: do not detach this tile
};

struct	ROW_ROOT
{
	BM_REF		 bm;
	Int32			 x1;
	Int32			 y1;
	Int32			 x2;
	Int32			 y2;
	Int32			 tile_flags;
	Int32			 tile_mode;
	BM_TILE*	 static_tile;
	Int32			 update_flags;
	ROW_BLOCK* root;
};

ROW_REF GetRR();

//----------------------------------------------------------------------------------------
// Create a new horizontal line fetcher object
// Function result:		line fetcher reference
// bm:								bitmap reference
// x1, x2:						minimum and maximum x coordinate (must be constant for all tiles in root)
// tile_flags:				TILE_REPEAT_BORDER, TILE_REPEAT_TILING, TILE_LAST_RESULT
// tile_mode:					TILE_BM_READ_ONLY, TILE_BM_WRITE, TILE_BM_READ_WRITE, TILE_BM_READ_SCRATCH
// static_tile:				use this parameter if all request are to be satisfied by this tile (and no other one)
//----------------------------------------------------------------------------------------
ROW_REF	new_row_fetcher(BM_REF bm, Int32 x1, Int32 x2, Int32 tile_flags, Int32 tile_mode, BM_TILE* static_tile, Int32 update_flags)
{
	ROW_REF	rr;

	ifnoerr (rr = NewMemClear(ROW_ROOT, 1))
	{
		rr->bm = bm;
		rr->tile_flags = tile_flags;
		rr->tile_mode	 = tile_mode;
		rr->x1 = x1;
		rr->y1 = 0;
		rr->x2 = x2;
		rr->y2 = 0;
		rr->static_tile	 = static_tile;
		rr->update_flags = update_flags;
		rr->root = 0;

		if (static_tile)
		{
			ROW_BLOCK* curr;

			ifnoerr (curr = NewMemClear(ROW_BLOCK, 1))
			{
				curr->next	= 0;
				curr->tile	= static_tile;	// ###NOTE: no support for TILE_MODE_READ_SCRATCH
				curr->xymin = static_tile->ymin;
				curr->xymax = static_tile->ymax;
				curr->ref = 1;
				curr->is_static = true;	// do not detach this tile!
				rr->root = curr;
			}
			else
			{
				DeleteMem(rr);
				rr = 0;
			}
		}
	}
	return rr;
}

//----------------------------------------------------------------------------------------
// Delete a line fetcher object
// Function result:		-
// rr:								line fetcher reference
// discard_all:				true: discard changes (is ignored for source tiles)
//----------------------------------------------------------------------------------------
void delete_row_fetcher(ROW_REF rr, Bool discard_all)
{
	if (rr)
	{
		while (rr->root)	// are there any slices that have to be returned?
		{
			ROW_BLOCK* curr;

			curr = rr->root;
			rr->root = curr->next;

			if (curr->is_static == false)	// can we detach this tile?
			{
				if ((rr->tile_mode & TILE_MODE_WRITE) && (discard_all == false))
				{
					BfBitmapTileDetach(rr->bm, curr->tile, true);
					if (rr->update_flags & ROW_FETCH_UPDATE_VIEW)
						BfUpdateView(rr->bm);		// update document view
				}
				else
				{
					BfBitmapTileDetach(rr->bm, curr->tile, false);
				}
			}

			DeleteMem(curr);	// gosh!
		}
		DeleteMem(rr);
	}
}

//----------------------------------------------------------------------------------------
// Return the pointer to a requested horizontal line
// Function result:		pointer to the source line
// rr:								line fetcher reference
// y:									requested line
//----------------------------------------------------------------------------------------
UChar* rf_get_bitmap_row(ROW_REF rr, Int32 y)
{
	ROW_BLOCK** prev;

	prev = &rr->root;
	while (1)
	{
		ROW_BLOCK* curr;
		BM_TILE*	 tile;

		curr = *prev;
		if (curr)	// is there a buffered tile?
		{
			tile = curr->tile;

			if ((y >= curr->xymin) && (y < curr->xymax))
			{
				curr->ref++;
				return (UChar*) tile->addr + (tile->width * (y - curr->xymin));
			}

			if ((curr->ref == 0) && (curr->is_static == false))	// is this tile not currently used and can we detach this tile?
			{
				*prev = curr->next;

				if (rr->tile_mode & TILE_MODE_WRITE)				// return a destination tile?
				{
					BfBitmapTileDetach(rr->bm, tile, true);		// destination tiles must (!!) be used in sequential order
					if (rr->update_flags & ROW_FETCH_UPDATE_VIEW)
						BfUpdateView(rr->bm);										// update document view
				}
				else																				// it's a source tile
				{
					BfBitmapTileDetach(rr->bm, tile, false);	// this assumes that source lines are processed in a more or less sequential order

				}
				DeleteMem(curr);
				continue;	// check the next tile
			}
		}
		else	// get a new tile
		{
			RECT32 rect;

			if (rr->static_tile)	// are we not allowed to allocate a new tile?
				break;

			ifnoerr (curr = NewMemClear(ROW_BLOCK, 1))
			{
				Int32	mode;

				mode = rr->tile_mode;
				if (mode & TILE_MODE_READ_SCRATCH)
				{
					mode &= ~TILE_MODE_READ_SCRATCH;
					mode |= TILE_MODE_READ_WRITE;	// handle this like a destination tile that will be thrown away
				}

				rect.x1 = rr->x1;
				rect.y1 = y;
				rect.x2 = rr->x2;
				rect.y2 = y + rr->bm->preferred_tile_height;	// get preferred tile height

				tile = BfBitmapTileGet(rr->bm, &rect, 0, 0, mode, rr->tile_flags);
				if (tile)
				{
					curr->next	= rr->root;
					curr->tile	= tile;
					curr->xymin = rect.y1;
					curr->xymax = rect.y2;
					curr->ref = 1;
					curr->is_static = false;

					rr->root = curr;

					return (UChar*) curr->tile->addr + (curr->tile->width * (y - curr->xymin));
				}
				else
				{
					DeleteMem(curr);
					return 0;
				}
			}
			else
			{
				break;
			}
		}
		prev = &curr->next;
	}
	return 0;
}

void rf_free_bitmap_row(ROW_REF rr, Int32 y)
{
	ROW_BLOCK** prev;

	prev = &rr->root;
	while (*prev)
	{
		ROW_BLOCK* curr;

		curr = *prev;
		if ((y >= curr->xymin) && (y < curr->xymax))
		{
			curr->ref--;
			if (curr->ref == 0)		// do not free this tile immediately if ref is zero (wait for the next request)
			{
				*prev = curr->next;	// unlink
				curr->next = rr->root;
				rr->root = curr;		// make sure that this is the first tile that will be examined
			}
			break;								// thank you very much
		}
		prev = &curr->next;
	}
}

//----------------------------------------------------------------------------------------
// Create a new vertical line fetcher object
// Function result:		line fetcher reference
// bm:								bitmap reference
// y1, y2:						minimum and maximum y coordinate (must be constant for all tiles in root)
// tile_flags:				TILE_REPEAT_BORDER, TILE_REPEAT_TILING, TILE_LAST_RESULT
// tile_mode:					TILE_BM_READ_ONLY, TILE_BM_WRITE, TILE_BM_READ_WRITE, TILE_BM_READ_SCRATCH
// static_tile:				use this parameter if all request are to be satisfied by this tile (and no other one)
//----------------------------------------------------------------------------------------
ROW_REF	new_column_fetcher(BM_REF bm, Int32 y1, Int32 y2, Int32 tile_flags, Int32 tile_mode, BM_TILE* static_tile, Int32 update_flags)
{
	ROW_REF	rr;

	ifnoerr (rr = NewMemClear(ROW_ROOT, 1))
	{
		rr->bm = bm;
		rr->tile_flags = tile_flags;
		rr->tile_mode	 = tile_mode;
		rr->x1 = 0;
		rr->y1 = y1;
		rr->x2 = 0;
		rr->y2 = y2;
		rr->static_tile	 = static_tile;
		rr->update_flags = update_flags;
		rr->root = 0;

		if (static_tile)
		{
			ROW_BLOCK* curr;

			ifnoerr (curr = NewMemClear(ROW_BLOCK, 1))
			{
				curr->next	= 0;
				curr->tile	= static_tile;	// ###NOTE: no support for TILE_MODE_READ_SCRATCH
				curr->xymin = static_tile->xmin;
				curr->xymax = static_tile->xmax;
				curr->ref = 1;
				curr->is_static = true;	// do not detach this tile!
				rr->root = curr;
			}
			else
			{
				DeleteMem(rr);
				rr = 0;
			}
		}
	}
	return rr;
}

//----------------------------------------------------------------------------------------
// Delete a vertical line fetcher object
// Function result:		-
// rr:								line fetcher reference
// discard_all:				true: discard changes (is ignored for source tiles)
//----------------------------------------------------------------------------------------
void delete_column_fetcher(ROW_REF rr, Bool discard_all)
{
	delete_row_fetcher(rr, discard_all);
}

//----------------------------------------------------------------------------------------
// Return the pointer to a requested vertical line
// Function result:		pointer to the source line
// rr:								line fetcher reference
// x:									requested line
// pixel_offset:			the distance to the next pixel is returned here (in bytes)
//----------------------------------------------------------------------------------------
UChar* rf_get_bitmap_column(ROW_REF rr, Int32 x, Int32* pixel_offset)
{
	ROW_BLOCK** prev;

	prev = &rr->root;
	while (1)
	{
		ROW_BLOCK* curr;
		BM_TILE*	 tile;

		curr = *prev;
		if (curr)	// is there a buffered tile?
		{
			tile = curr->tile;
			if ((x >= curr->xymin) && (x < curr->xymax))
			{
				curr->ref++;
				*pixel_offset = tile->width;
				return (UChar*) tile->addr + (((x - curr->xymin) * get_PX_BITS(tile->px_format)) >> 3);
			}

			if ((curr->ref == 0) && (curr->is_static == false))	// is this tile not currently used and can we detach this tile?
			{
				*prev = curr->next;

				if (rr->tile_mode & TILE_MODE_WRITE)				// return a destination tile?
				{
					BfBitmapTileDetach(rr->bm, tile, true);		// destination tiles must (!!) be used in sequential order
					if (rr->update_flags & ROW_FETCH_UPDATE_VIEW)
						BfUpdateView(rr->bm);										// update document view
				}
				else																				// it's a source tile
				{
					BfBitmapTileDetach(rr->bm, tile, false);	// this assumes that source lines are processed in a more or less sequential order

				}
				DeleteMem(curr);
				continue;	// check the next tile
			}
		}
		else	// get a new tile
		{
			RECT32 rect;

			if (rr->static_tile)	// are we not allowed to allocate a new tile?
				break;

			ifnoerr (curr = NewMemClear(ROW_BLOCK, 1))
			{
				Int32	mode;

				mode = rr->tile_mode;
				if (mode & TILE_MODE_READ_SCRATCH)
				{
					mode &= ~TILE_MODE_READ_SCRATCH;
					mode |= TILE_MODE_READ_WRITE;	// handle this like a destination tile that will be thrown away
				}

				rect.x1 = x;
				rect.y1 = rr->y1;
				rect.x2 = x + rr->bm->preferred_tile_width;	// get preferred tile width
				rect.y2 = rr->y2;

				tile = BfBitmapTileGet(rr->bm, &rect, 0, 0, mode, rr->tile_flags);
				if (tile)
				{
					curr->next	= rr->root;
					curr->tile	= tile;
					curr->xymin = rect.x1;
					curr->xymax = rect.x2;
					curr->ref = 1;
					curr->is_static = false;

					rr->root = curr;

					*pixel_offset = tile->width;
					return (UChar*) tile->addr + (((x - curr->xymin) * get_PX_BITS(tile->px_format)) >> 3);
				}
				else
				{
					DeleteMem(curr);
					return 0;
				}
			}
			else
			{
				break;
			}
		}
		prev = &curr->next;
	}
	return 0;
}

void rf_free_bitmap_column(ROW_REF rr, Int32 x)
{
	rf_free_bitmap_row(rr, x);
}



//----------------------------------------------------------------------------------------
// Convert from separated to premultiplied alpha
// Function result:		-
// buf:								line to be converted
// width:							# of pixels to copy
// no_components:			# of components per pixel
// pixel_offset:			offset from one pixel to the next in bytes
//----------------------------------------------------------------------------------------
void premultiply_alpha(UChar* buf, Int32 width, Int32 no_components, Int32 pixel_offset)
{
	pixel_offset -= no_components;
	no_components--;	// decrement because it is used for the counter

	for (; width > 0; width--)
	{
		Int32	 i;
		UInt32 alpha;

		alpha = *buf++;

		if (alpha == 255)
		{
			buf += no_components;	// pixels won't change
		}
		else
		{
			for (i = no_components; i > 0; i--)
			{
				UInt32 v;

				v	 = *buf * alpha;
				v += 128;											// round
				v	 = (v + (v >> 8) + 1) >> 8;	// divide by 255 (v must be <= 65280)
				*buf++ = (UChar) v;
			}
		}

		buf += pixel_offset;	// skip pixels (only vertical line)
	}
}

void premultiply_alpha(UInt16* buf, Int32 width, Int32 no_components, Int32 pixel_offset)
{
	pixel_offset -= no_components;
	no_components--;	// decrement because it is used for the counter

	for (; width > 0; width--)
	{
		Int32	 i;
		UInt32 alpha;

		alpha = *buf++;

		if (alpha == 65535)
		{
			buf += no_components;	// pixels won't change
		}
		else
		{
			for (i = no_components; i > 0; i--)
			{
				UInt32 v;

				v	 = *buf * alpha;
				v += 32768;											// round
				v	 = (v + (v >> 16) + 1) >> 16;	// divide by 255 (v must be <= 65280)
				*buf++ = (UInt16) v;
			}
		}

		buf += pixel_offset;	// skip pixels (only vertical line)
	}
}

void premultiply_alpha(Float32* buf, Int32 width, Int32 no_components, Int32 pixel_offset)
{
	pixel_offset -= no_components;
	no_components--;	// decrement because it is used for the counter

	for (; width > 0; width--)
	{
		Int32		i;
		Float32 alpha;

		alpha = *buf++;

		if (alpha == 1.0)
		{
			buf += no_components;	// pixels won't change
		}
		else
		{
			if (alpha < 0.0)
			{
				alpha = 0;
				buf[-1] = alpha;
			}
			else if (alpha > 1.0)
			{
				alpha = 1.0;
				buf[-1] = alpha;
			}

			for (i = no_components; i > 0; i--)
			{
				Float32 v;
				v = *buf * alpha;
				*buf++ = v;
			}
		}

		buf += pixel_offset;	// skip pixels (only vertical line)
	}
}

//----------------------------------------------------------------------------------------
// Convert from premultiplied to separated alpha
// Function result:		-
// buf:								line to be converted
// width:							# of pixels to copy
// no_components:			# of components per pixel
// pixel_offset:			offset from one pixel to the next in bytes
//----------------------------------------------------------------------------------------
void separate_alpha(UChar* buf, Int32 width, Int32 no_components, Int32 pixel_offset)
{
	pixel_offset -= no_components;
	no_components--;	// decrement because it is used for the counter

	for (; width > 0; width--)
	{
		UInt32 alpha;

		alpha = *buf++;

		if ((alpha == 0) || (alpha == 255))
		{
			buf += no_components;	// no need to change the pixel values
		}
		else
		{
			Int32	 i;
			UInt32 recip_alpha;

			recip_alpha = (255L << 16) / alpha;
			for (i = no_components; i > 0; i--)
			{
				UInt32 v;

				v = ((*buf * recip_alpha) + 32768L) >> 16;	// v * ( 255.0 / (Float) alpha )
				if (v > 255)
					v = 255;																	// premultiplied values can exceed the normal range
				*buf++ = (UChar)v;
			}
		}

		buf += pixel_offset;	// skip pixels (only vertical line)
	}
}

void separate_alpha(UInt16* buf, Int32 width, Int32 no_components, Int32 pixel_offset)
{
	pixel_offset -= no_components;
	no_components--;	// decrement because it is used for the counter

	for (; width > 0; width--)
	{
		UInt32 alpha;

		alpha = *buf++;

		if ((alpha == 0) || (alpha == 65535))
		{
			buf += no_components;	// no need to change the pixel values
		}
		else
		{
			Int32	i;
			for (i = no_components; i > 0; i--)
			{
				UInt32 v;

				v = ((*buf) << 16) / alpha;	// recip_alpha ) + 32768L ) >> 16;				// v * ( 255.0 / (Float) alpha )
				if (v > 65535)
					v = 65535;								// premultiplied values can exceed the normal range
				*buf++ = (UInt16)v;
			}
		}

		buf += pixel_offset;	// skip pixels (only vertical line)
	}
}

void separate_alpha(Float32* buf, Int32 width, Int32 no_components, Int32 pixel_offset, Float32 clip)
{
	pixel_offset -= no_components;
	no_components--;	// decrement because it is used for the counter

	for (; width > 0; width--)
	{
		Float32 alpha;

		alpha = *buf++;

		if (alpha < clip)
		{
			alpha = 0.0;
			buf[-1] = alpha;
		}
		else if (alpha > 1.0)
		{
			alpha = 1.0;
			buf[-1] = alpha;
		}

		if ((alpha == 0.0) || (alpha == 1.0))
		{
			buf += no_components;	// no need to change the pixel values
		}
		else
		{
			Int32		i;
			Float32 recip_alpha;

			recip_alpha = 1.0f / alpha;
			for (i = no_components; i > 0; i--)
			{
				Float32 v;
				v = Float32(*buf) * recip_alpha;
				*buf++ = v;
			}
		}


		buf += pixel_offset;	// skip pixels (only vertical line)
	}
}

