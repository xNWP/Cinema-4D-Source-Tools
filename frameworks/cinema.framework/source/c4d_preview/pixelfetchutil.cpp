#include "c4d_general.h"
#include "c4d_shader.h"
#include "c4d_memory.h"
#include "c4d_bitmapfilter.h"

#define	DEBUG					 0
#define	USE_TILE_CACHE 1
#define	MAX_COMPONENTS 8	// maximum number of components per pixel

#include "pixelfetchutil.h"

struct TILE_LRU
{
	TILE_LRU*	 prev;
	TILE_LRU*	 next;

	Int32			 grid_x;
	Int32			 grid_y;
	TILE_LRU** grid_entry;

	BM_TILE*	 data;	// data
};

struct	PIXEL_ROOT
{
	BM_REF bm;	// needed for accessing tiles
	Int32	 color_space;
	UInt32 px_format;
	Int32	 _pixel_size;	// bytes per pixel
	Int32	 _channels;		// chper pixel
	Int32	 tile_flags;	// flags for clipping/texture wrapping

#if	USE_TILE_CACHE
#if DEBUG
	Int32	no_tile_unloads;	// # of times tiles had to be kicked out of the cache
#endif

	TILE_LRU	dummy_first;
	TILE_LRU	dummy_last;

	Int32			tile_shifts;
	Int32			tile_mask;
	Int32			tile_wh;

	Int32			no_tiles;			// number of currently cached tiles
	Int32			no_max_tiles;	// maximum number of tiles that should be cached

	UInt32		grid_width;		// # of tiles along the x axis (must be UInt32!)
	UInt32		grid_height;	// # of tiles along the y axis (must be UInt32!)
	TILE_LRU* tile_grid[VARIABLE_ARRAY_SIZE];

#else

	BM_TILE* tile;

#endif
};

//----------------------------------------------------------------------------------------
// Create a new pixel fetcher object
// Function result:		pixel fetcher reference
// bm:								bitmap reference
// tile_flags:				TILE_REPEAT_BORDER or TILE_REPEAT_TILING
// no_cached_tiles:		0: use default settings > 0: maximum number of cached tiles
//----------------------------------------------------------------------------------------
PIXEL_REF	new_pixel_fetcher(BM_REF bm, Int32 tile_flags, Int32 no_cached_tiles)
{
	Int32			tile_shifts;
	Int32			tile_wh;
	Int32			grid_w;
	Int32			grid_h;
	Int32			grid_size;
	PIXEL_REF pf;

	tile_shifts = 7;	// tile size is 128 * 128
	tile_wh = 128;

	grid_w = (bm->image_rect.x2 + tile_wh - 1) / tile_wh;	// width of the lookup table in tiles
	grid_h = (bm->image_rect.y2 + tile_wh - 1) / tile_wh;	// height of the lookup table in tiles
	grid_size = grid_w * grid_h * sizeof(TILE_LRU*);

	ifnoerr (((UChar*&)pf) = NewMemClear(UChar, sizeof(PIXEL_ROOT) + grid_size))
	{
		pf->bm = bm;
		pf->color_space = bm->image_color_space;
		pf->px_format = bm->image_px_format;
		pf->_pixel_size = get_PX_BITS(bm->image_px_format) >> 3;
		pf->_channels	 = get_PX_CMPNTS(bm->image_px_format);
		pf->tile_flags = tile_flags;

#if USE_TILE_CACHE
#if DEBUG
		pf->no_tile_unloads = 0;
#endif

		pf->dummy_first.prev = 0;	// indicates that this ist first dummy entry
		pf->dummy_first.next = &pf->dummy_last;
		pf->dummy_first.grid_x = LIMIT<Int32>::MIN;
		pf->dummy_first.grid_y = LIMIT<Int32>::MIN;
		pf->dummy_first.grid_entry = 0;
		pf->dummy_first.data = 0;

		pf->dummy_last.prev = &pf->dummy_first;
		pf->dummy_last.next = 0;	// indicates that this is the final dummy entry
		pf->dummy_last.grid_x = LIMIT<Int32>::MIN;
		pf->dummy_last.grid_y = LIMIT<Int32>::MIN;
		pf->dummy_last.grid_entry = 0;
		pf->dummy_last.data = 0;

		pf->tile_shifts = tile_shifts;	// tile size is 128 * 128
		pf->tile_wh = tile_wh;
		pf->tile_mask = tile_wh - 1;

		pf->no_tiles = 0;	// currently no tiles allocated
		pf->no_max_tiles	 = (bm->image_rect.x2 - bm->image_rect.x1 + tile_wh - 1) >> tile_shifts;
		pf->no_max_tiles <<= 1;
		if (no_cached_tiles > 0)
			pf->no_max_tiles = no_cached_tiles;

		pf->grid_width	= grid_w;
		pf->grid_height = grid_h;
		ClearMem(pf->tile_grid, grid_size, 0);	// empty lookup table
#else
		pf->tile = nullptr;
#endif
	}
	return pf;
}

//----------------------------------------------------------------------------------------
// Delete a pixel fetcher object
// Function result:		-
// pf:								pixel fetcher object
//----------------------------------------------------------------------------------------
void delete_pixel_fetcher(PIXEL_REF pf)
{
	if (pf)
	{
#if USE_TILE_CACHE
		TILE_LRU* lru_tile;

		lru_tile = pf->dummy_first.next;
		while (lru_tile->next)	// loop till the last dummy entry is reached
		{
			TILE_LRU* tmp;

			tmp = lru_tile;
			lru_tile = lru_tile->next;

			BfBitmapTileDetach(pf->bm, tmp->data, false);	// free the tile data
			DeleteMem(tmp);																// free lru entry
		}
#else
		if (pf->tile)
			BfBitmapTileDetach(pf->bm, pf->tile, false);
#endif
		DeleteMem(pf);
	}
}

#if USE_TILE_CACHE

//----------------------------------------------------------------------------------------
// Return a pixel's address
// Function result:		pixel address or 0
// pf:								pixel fetcher object
// x, y:							coordinates in the image's coordinate space
//----------------------------------------------------------------------------------------
inline static UChar* get_pixel_addr(PIXEL_REF pf, Int32 x, Int32 y)
{
	UInt32		grid_x;
	UInt32		grid_y;
	TILE_LRU* lru_tile;
	BM_TILE*	tile;

	grid_x = ((UInt32) x) >> pf->tile_shifts;
	grid_y = ((UInt32) y) >> pf->tile_shifts;
	lru_tile = pf->dummy_first.next;																										// the last recently used tile

	if ((grid_x != (UInt32) lru_tile->grid_x) || (grid_y != (UInt32) lru_tile->grid_y))	// are we not accessing the last recently used tile?
	{
		if ((grid_x >= pf->grid_width) || (grid_y >= pf->grid_height))
		{
			RECT32* r;

			r = &pf->bm->image_rect;
			if (pf->tile_flags & TILE_REPEAT_TILING)	// wrap around at the border
			{
				x -= r->x1;
				y -= r->y1;

				x %= r->x2 - r->x1;	// note: the modulo result is negative, if x was < 0
				y %= r->y2 - r->y1;

				if (x < 0)
					x += r->x2;
				else
					x += r->x1;

				if (y < 0)
					y += r->y2;
				else
					y += r->y1;
			}
			else	// TILE_REPEAT_BORDER
			{
				if (x < pf->bm->image_rect.x1)
					x = pf->bm->image_rect.x1;

				if (x >= pf->bm->image_rect.x2)
					x = pf->bm->image_rect.x2 - 1;

				if (y < pf->bm->image_rect.y1)
					y = pf->bm->image_rect.y1;

				if (y >= pf->bm->image_rect.y2)
					y = pf->bm->image_rect.y2 - 1;
			}
			grid_x = ((UInt32) x) >> pf->tile_shifts;
			grid_y = ((UInt32) y) >> pf->tile_shifts;
		}

		lru_tile = pf->tile_grid[(grid_y * pf->grid_width) + grid_x];
		if (lru_tile == 0)	// no tile for this area?
		{
			RECT32 tile_rect;

			tile_rect.x1 = grid_x << pf->tile_shifts;
			tile_rect.y1 = grid_y << pf->tile_shifts;
			tile_rect.x2 = (grid_x + 1) << pf->tile_shifts;
			tile_rect.y2 = (grid_y + 1) << pf->tile_shifts;

			if (pf->no_tiles >= pf->no_max_tiles)	// free the least important tile?
			{
				pf->no_tiles--;
				lru_tile = pf->dummy_last.prev;
				lru_tile->prev->next = lru_tile->next;	// unlink
				lru_tile->next->prev = lru_tile->prev;

				*lru_tile->grid_entry = 0;													// delete the entry in the lookup grid

				BfBitmapTileDetach(pf->bm, lru_tile->data, false);	// free the tile data

#if DEBUG
				pf->no_tile_unloads++;
#endif
			}
			else	// add a new lru entry
			{
				iferr (lru_tile = NewMemClear(TILE_LRU, 1))
					return nullptr;
			}

			lru_tile->data = BfBitmapTileGet(pf->bm, &tile_rect, 0, 0, TILE_BM_READ_ONLY, pf->tile_flags);

			if (lru_tile->data == 0)	// unable to access the tile?
			{
				DeleteMem(lru_tile);
				return nullptr;	// Houston, we have a problem
			}

			pf->no_tiles++;

			lru_tile->next = pf->dummy_first.next;	// insert in the chain as the first
			lru_tile->prev = &pf->dummy_first;
			lru_tile->prev->next = lru_tile;
			lru_tile->next->prev = lru_tile;

			lru_tile->grid_x = grid_x;	// save that grid position for a quick lru check at the top of the function
			lru_tile->grid_y = grid_y;
			lru_tile->grid_entry	= &pf->tile_grid[(grid_y * pf->grid_width) + grid_x];
			*lru_tile->grid_entry = lru_tile;	// add entry in the lookup grid
		}

		if (lru_tile != pf->dummy_first.next)			// change the lru order?
		{
			lru_tile->next->prev = lru_tile->prev;	// unlink from the chain
			lru_tile->prev->next = lru_tile->next;

			pf->dummy_first.next->prev = lru_tile;	// link with the previously used tile
			lru_tile->next = pf->dummy_first.next;

			lru_tile->prev = &pf->dummy_first;	// link with the dummy root
			pf->dummy_first.next = lru_tile;
		}
	}

	tile = lru_tile->data;
	x -= tile->xmin;
	y -= tile->ymin;
	return (UChar*) tile->addr + (tile->width * y) + (pf->_pixel_size * x);
}

//----------------------------------------------------------------------------------------
// Return a pixel
// Function result:		true: everything is fine false: can't access the pixel
// pf:								pixel fetcher object
// x:									discrete x coordinate
// y:									discrete y coordinate
// dst:								used to return the pixel
//----------------------------------------------------------------------------------------
	#define T PIX_C
Bool pf_get_pixel(PIXEL_REF pf, Int32 x, Int32 y, T* dst)
{
	T* p;

	p = (T*)get_pixel_addr(pf, x, y);
	if (p)
	{
		Int32	i;

		for (i = pf->_channels; i; i--)
			*dst++ = *p++;

		return true;
	}
	return false;
}
	#undef T

	#define T PIX_W
Bool pf_get_pixel(PIXEL_REF pf, Int32 x, Int32 y, T* dst)
{
	T* p;

	p = (T*)get_pixel_addr(pf, x, y);
	if (p)
	{
		Int32	i;

		for (i = pf->_channels; i; i--)
			*dst++ = *p++;

		return true;
	}
	return false;
}
	#undef T

	#define T PIX_F
Bool pf_get_pixel(PIXEL_REF pf, Int32 x, Int32 y, T* dst)
{
	T* p;

	p = (T*)get_pixel_addr(pf, x, y);
	if (p)
	{
		Int32	i;

		for (i = pf->_channels; i; i--)
			*dst++ = *p++;

		return true;
	}
	return false;
}
	#undef T

//----------------------------------------------------------------------------------------
// Return a pixel's address
// Function result:		pixel address or 0
// pf:								pixel fetcher object
// x:									discrete x coordinate
// y:									discrete y coordinate
//----------------------------------------------------------------------------------------
UChar* pf_get_pixel_addr(PIXEL_REF pf, Int32 x, Int32 y)
{
	return get_pixel_addr(pf, x, y);
}

#else

template <class T> Bool pf_get_pixel(PIXEL_REF pf, Int32 x, Int32 y, T* pixel)
{
	T*			 p;
	Int32		 i;
	BM_TILE* tile;

	tile = pf->tile;

	if ((tile == 0) || (x < tile->xmin) || (x >= tile->xmax) || (y < tile->ymin) || (y >= tile->ymax))
	{
		BM_REF bm;
		RECT32 tile_rect;
		Int32	 col;
		Int32	 row;

		bm = pf->bm;

		if (x < bm->image_rect.x1)
			x = bm->image_rect.x1;

		if (x >= bm->image_rect.x2)
			x = bm->image_rect.x2 - 1;

		if (y < bm->image_rect.y1)
			y = bm->image_rect.y1;

		if (y >= bm->image_rect.y2)
			y = bm->image_rect.y2 - 1;

		if ((tile == 0) || (x < tile->xmin) || (x >= tile->xmax) || (y < tile->ymin) || (y >= tile->ymax))
		{
			col = x / bm->preferred_tile_width;
			row	= y / bm->preferred_tile_height;

			if (pf->tile)
				BfBitmapTileDetach(bm, pf->tile, false);

			tile_rect = bm->image_rect;
			tile = BfBitmapTileGet(bm, &tile_rect, 0, 0, TILE_BM_READ_ONLY, 0);

			if (tile == 0)
				return false;

			pf->tile = tile;
		}
	}

	p	 = (T*) tile->addr;
	p += tile->width * (y - tile->ymin);
	p += pf->_channels * (x - tile->xmin);

	for (i = pf->_channels; i; i--)
		*pixel++ = *p++;

	return true;
}

UChar* pf_get_pixel_addr(PIXEL_REF pf, Int32 x, Int32 y)
{
	UChar*	 p;
	BM_TILE* tile;

	tile = pf->tile;

	if ((tile == 0) || (x < tile->xmin) || (x >= tile->xmax) || (y < tile->ymin) || (y >= tile->ymax))
	{
		BM_REF bm;
		RECT32 tile_rect;
		Int32	 col;
		Int32	 row;

		bm = pf->bm;

		if (x < bm->image_rect.x1)
			x = bm->image_rect.x1;

		if (x >= bm->image_rect.x2)
			x = bm->image_rect.x2 - 1;

		if (y < bm->image_rect.y1)
			y = bm->image_rect.y1;

		if (y >= bm->image_rect.y2)
			y = bm->image_rect.y2 - 1;

		if ((tile == 0) || (x < tile->xmin) || (x >= tile->xmax) || (y < tile->ymin) || (y >= tile->ymax))
		{
			col = x / bm->preferred_tile_width;
			row	= y / bm->preferred_tile_height;

			if (pf->tile)
				BfBitmapTileDetach(bm, pf->tile, false);

			tile_rect = bm->image_rect;
			tile = BfBitmapTileGet(bm, &tile_rect, 0, 0, TILE_BM_READ_ONLY, 0);

			if (tile == 0)
				return 0;

			pf->tile = tile;
		}
	}

	p	 = (UChar*) tile->addr;
	p += tile->width * (y - tile->ymin);
	p += pf->_pixel_size * (x - tile->xmin);
	return p;
}
#endif

//----------------------------------------------------------------------------------------
// Return a bilinear filtered pixel
// Function result:		true: everything is fine false: can't access the pixel
// pf:								pixel fetcher object
// fx:								continous x coordinate (.5 is pixel center)
// fy:								continous y coordinate (.5 is pixel center)
// dst:								used to return the pixel
//----------------------------------------------------------------------------------------
Bool pf_get_pixel_bilinear(PIXEL_REF pf, Float fx, Float fy, PIX_C* dst)
{
	PIX_C pbuf[4][MAX_COMPONENTS];
	Int32	ix;
	Int32	iy;

	fx -= 0.5;
	fy -= 0.5;

	ix = (Int32) floor(fx);
	iy = (Int32) floor(fy);

	if (pf_get_pixel(pf, ix, iy, pbuf[0]))
	{
		if (pf_get_pixel(pf, ix + 1, iy, pbuf[1]))
		{
			if (pf_get_pixel(pf, ix, iy + 1, pbuf[2]))
			{
				if (pf_get_pixel(pf, ix + 1, iy + 1, pbuf[3]))
				{
					Float	values[4];
					Int32	i;

					if (pf->color_space & CSPACE_ALPHA_FLAG)
					{
						Float	alpha[4];
						Float	new_alpha;

						values[0] = (Float) pbuf[0][0];
						values[1] = (Float) pbuf[1][0];
						values[2] = (Float) pbuf[2][0];
						values[3] = (Float) pbuf[3][0];
						alpha[0]	= values[0] / 255.0;
						alpha[1]	= values[1] / 255.0;
						alpha[2]	= values[2] / 255.0;
						alpha[3]	= values[3] / 255.0;

						new_alpha = bilinear_double(fx, fy, values);
						*dst++ = (UChar) (new_alpha + 0.5);
						new_alpha /= 255.0;
						if (new_alpha == 0.0)
							new_alpha = 1.0;

						for (i = 1; i < pf->_channels; i++)
						{
							Float	v;

							values[0] = (Float) pbuf[0][i] * alpha[0];
							values[1] = (Float) pbuf[1][i] * alpha[1];
							values[2] = (Float) pbuf[2][i] * alpha[2];
							values[3] = (Float) pbuf[3][i] * alpha[3];

							v	 = bilinear_double(fx, fy, values);
							v /= new_alpha;
							if (v < 0.0)
								v = 0.0;
							if (v > 255.0)
								v = 255.0;
							*dst++ = (UChar) (v + 0.5);
						}
					}
					else
					{
						for (i = 0; i < pf->_channels; i++)
						{
							values[0] = (Float) pbuf[0][i];
							values[1] = (Float) pbuf[1][i];
							values[2] = (Float) pbuf[2][i];
							values[3] = (Float) pbuf[3][i];

							*dst++ = (UChar) (bilinear_double(fx, fy, values) + 0.5);
						}
					}
					return true;
				}
			}
		}
	}
	return false;
}

Bool pf_get_pixel_bilinear(PIXEL_REF pf, Float fx, Float fy, PIX_W* dst)
{
	PIX_W pbuf[4][MAX_COMPONENTS];
	Int32	ix;
	Int32	iy;

	fx -= 0.5;
	fy -= 0.5;

	ix = (Int32) floor(fx);
	iy = (Int32) floor(fy);

	if (pf_get_pixel(pf, ix, iy, pbuf[0]))
	{
		if (pf_get_pixel(pf, ix + 1, iy, pbuf[1]))
		{
			if (pf_get_pixel(pf, ix, iy + 1, pbuf[2]))
			{
				if (pf_get_pixel(pf, ix + 1, iy + 1, pbuf[3]))
				{
					Float	values[4];
					Int32	i;

					if (pf->color_space & CSPACE_ALPHA_FLAG)
					{
						Float	alpha[4];
						Float	new_alpha;

						values[0] = (Float) pbuf[0][0];
						values[1] = (Float) pbuf[1][0];
						values[2] = (Float) pbuf[2][0];
						values[3] = (Float) pbuf[3][0];
						alpha[0]	= values[0] / 65535.0;
						alpha[1]	= values[1] / 65535.0;
						alpha[2]	= values[2] / 65535.0;
						alpha[3]	= values[3] / 65535.0;

						new_alpha = bilinear_double(fx, fy, values);
						*dst++ = (PIX_W) (new_alpha + 0.5);
						new_alpha /= 65535.0;
						if (new_alpha == 0.0)
							new_alpha = 1.0;

						for (i = 1; i < pf->_channels; i++)
						{
							Float	v;

							values[0] = (Float) pbuf[0][i] * alpha[0];
							values[1] = (Float) pbuf[1][i] * alpha[1];
							values[2] = (Float) pbuf[2][i] * alpha[2];
							values[3] = (Float) pbuf[3][i] * alpha[3];

							v	 = bilinear_double(fx, fy, values);
							v /= new_alpha;
							if (v < 0.0)
								v = 0.0;
							if (v > 65535.0)
								v = 65535.0;
							*dst++ = (PIX_W) (v + 0.5);
						}
					}
					else
					{
						for (i = 0; i < pf->_channels; i++)
						{
							values[0] = (Float) pbuf[0][i];
							values[1] = (Float) pbuf[1][i];
							values[2] = (Float) pbuf[2][i];
							values[3] = (Float) pbuf[3][i];

							*dst++ = (PIX_W) (bilinear_double(fx, fy, values) + 0.5);
						}
					}
					return true;
				}
			}
		}
	}
	return false;
}

Bool pf_get_pixel_bilinear(PIXEL_REF pf, Float fx, Float fy, PIX_F* dst)
{
	PIX_F pbuf[4][MAX_COMPONENTS];
	Int32	ix;
	Int32	iy;

	fx -= 0.5;
	fy -= 0.5;

	ix = (Int32) floor(fx);
	iy = (Int32) floor(fy);

	if (pf_get_pixel(pf, ix, iy, pbuf[0]))
	{
		if (pf_get_pixel(pf, ix + 1, iy, pbuf[1]))
		{
			if (pf_get_pixel(pf, ix, iy + 1, pbuf[2]))
			{
				if (pf_get_pixel(pf, ix + 1, iy + 1, pbuf[3]))
				{
					Float	values[4];
					Int32	i;

					if (pf->color_space & CSPACE_ALPHA_FLAG)
					{
						Float	alpha[4];
						Float	new_alpha;

						values[0] = pbuf[0][0];
						values[1] = pbuf[1][0];
						values[2] = pbuf[2][0];
						values[3] = pbuf[3][0];
						alpha[0]	= values[0];
						alpha[1]	= values[1];
						alpha[2]	= values[2];
						alpha[3]	= values[3];

						new_alpha = bilinear_double(fx, fy, values);

						*dst++ = (Float32)new_alpha;

						if (new_alpha == 0.0)
							new_alpha = 1.0;

						for (i = 1; i < pf->_channels; i++)
						{
							Float	v;

							values[0] = (Float) pbuf[0][i] * alpha[0];
							values[1] = (Float) pbuf[1][i] * alpha[1];
							values[2] = (Float) pbuf[2][i] * alpha[2];
							values[3] = (Float) pbuf[3][i] * alpha[3];

							v	 = bilinear_double(fx, fy, values);
							v /= new_alpha;
							if (v < 0.0)
								v = 0.0;
							*dst++ = (Float32)v;
						}
					}
					else
					{
						for (i = 0; i < pf->_channels; i++)
						{
							values[0] = (Float) pbuf[0][i];
							values[1] = (Float) pbuf[1][i];
							values[2] = (Float) pbuf[2][i];
							values[3] = (Float) pbuf[3][i];

							*dst++ = (Float32)bilinear_double(fx, fy, values);
						}
					}
					return true;
				}
			}
		}
	}
	return false;
}

UChar	bilinear8(Float x, Float y, UChar* values)
{
	Float m0, m1;

	x -= floor(x);
	y -= floor(y);

	// the following line ist just another way of writing m0 = ( values[0] * ( 1 - x )) + ( values[1] * x )
	m0 = (Float) values[0] + (x * ((Float) values[1] - values[0]));
	m1 = (Float) values[2] + (x * ((Float) values[3] - values[2]));

	return (UChar) (m0 + (y * (m1 - m0)));
}

UInt16 bilinear16(Float x, Float y, UInt16* values)
{
	Float m0, m1;

	x -= floor(x);
	y -= floor(y);

	m0 = (Float) values[0] + (x * ((Float) values[1] - values[0]));
	m1 = (Float) values[2] + (x * ((Float) values[3] - values[2]));

	return (UInt16) (m0 + (y * (m1 - m0)));
}

Float	bilinear_double(Float x, Float y, Float* values)
{
	Float m0, m1;

	x -= floor(x);
	y -= floor(y);

	// the following line ist just another way of writing m0 = ( values[0] * ( 1 - x )) + ( values[1] * x )
	m0 = values[0] + (x * (values[1] - values[0]));
	m1 = values[2] + (x * (values[3] - values[2]));

	return m0 + (y * (m1 - m0));
}
