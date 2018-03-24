#include "c4d_general.h"
#include "c4d_shader.h"
#include "c4d_memory.h"
#include "c4d_resource.h"
#include "c4d_commandplugin.h"
#include "c4d_plugin.h"
#include "c4d_basebitmap.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "customgui_bitmapbutton.h"

#include "x4d_filter.h"
#include "c4d_bitmapfilter.h"
#include "lib_iconcollection.h"

#include	"filterpreview.h"
#include	"filter_private_id.h"
#include	"filter_prefs.h"

#define	SCALE_ONE	4
#define	SCALE_MAX	12

static Float32 scale_factor[] =
{
	100.0f / 800.0f,	// 800
	100.0f / 400.0f,	// 400
	100.0f / 200.0f,	// 200
	100.0f / 150.0f,	// 150

	100.0f / 100.0f,	// 100
	100.0f / 75.0f,		// 75
	100.0f / 66.6f,		// 66
	100.0f / 50.0f,		// 50
	100.0f / 33.3f,		// 33
	100.0f / 25.0f,		// 25
	100.0f / 20.0f,		// 20
	100.0f / 12.5f,		// 12.5
};

//----------------------------------------------------------------------------------------
// private functions
//----------------------------------------------------------------------------------------
static Bool	is_bigger_than_life(BM_REF bm, const RECT32* src_rect);
static void	get_clipped_size(BM_REF bm, const RECT32* src_rect, const Int32 w, const Int32 h, RECT32* clipped_rect, Int32* clipped_w, Int32* clipped_h);
static BM_TILE* get_preview_source(BM_REF bm, const RECT32* src_rect, Int32 w, Int32 h, Int32 tile_mode, Int32 flags);
static Int32 paste_tile_into_bmp(BM_REF bm, BM_TILE* dt, BaseBitmap* bmp);
static void	darken_bmp(BM_REF bm, BaseBitmap* bmp);
static void	blend_line(UChar* dst, Int32 y, Int32 w, Int32 l);

//----------------------------------------------------------------------------------------
// Apply checkboard pattern to bitmap tile
// Function result:		-
// tile:							bitmap tile
//----------------------------------------------------------------------------------------
inline UChar BLEND_WHITE(UChar v)	{ return UChar(((v << 2) - v + 0xffL) >> 2); }
inline UChar BLEND_BLACK(UChar v) { return UChar(((v << 2) - v + 0x80L) >> 2); }

inline UInt16 BLEND_WHITE(UInt16 v)	{ return UInt16(((v << 2) - v + (0xffL << 8)) >> 2); }
inline UInt16 BLEND_BLACK(UInt16 v) { return UInt16(((v << 2) - v + (0x80L << 8)) >> 2); }

inline Float32 BLEND_WHITE(Float32 v)	{ return ((v * 4) - v + 0xffL / 255.0f) / 4; }
inline Float32 BLEND_BLACK(Float32 v) { return ((v * 4) - v + 0x80L / 255.0f) / 4; }

template <class T> inline void blend_pattern(BM_TILE* tile, T dummy)
{
#define	PAT_WIDTH	 8
#define	PAT_HEIGHT 8

	T*		dst, v;
	Int32	dst_offset, w, i, j, x, y, l, bytes;

	dst = (T*) tile->addr;
	w = (tile->xmax - tile->xmin) * get_PX_CMPNTS(tile->px_format);
	l = get_PX_CMPNTS(tile->px_format) * PAT_WIDTH;
	bytes = get_PX_BITS(tile->px_format) / get_PX_CMPNTS(tile->px_format) / 8;
	dst_offset = tile->width / bytes - w;

	for (y = tile->ymax - tile->ymin; y > 0; )
	{
		for (j = (y > PAT_HEIGHT ? PAT_HEIGHT : y); j > 0; j--)
		{
			for (x = w; x > 0; )
			{
				for (i = (x > l ? l : x); i > 0; i--)
				{
					v = *dst;
					*dst++ = BLEND_WHITE(v);
				}
				x -= l;

				for (i = (x > l ? l : x); i > 0; i--)
				{
					v = *dst;
					*dst++ = BLEND_BLACK(v);
				}
				x -= l;
			}
			dst += dst_offset;
		}
		y -= PAT_HEIGHT;

		for (j = (y > PAT_HEIGHT ? PAT_HEIGHT : y); j > 0; j--)
		{
			for (x = w; x > 0; )
			{
				for (i = (x > l ? l : x); i > 0; i--)
				{
					v = *dst;
					*dst++ = BLEND_BLACK(v);
				}
				x -= l;

				for (i = (x > l ? l : x); i > 0; i--)
				{
					v = *dst;
					*dst++ = BLEND_WHITE(v);
				}
				x -= l;
			}
			dst += dst_offset;
		}
		y -= PAT_HEIGHT;
	}
	#undef	PAT_HEIGHT
	#undef	PAT_WIDTH
}

//----------------------------------------------------------------------------------------


PreviewBmp::PreviewBmp(void)
{
	BaseContainer	prefs;

	prefs = GetGlobalFilterPrefs(BF_PREFS_GLOBAL);

	bm = 0;							// bitmap reference
	bmp_valid	 = false;	// contains no data
	offset_x	 = 0;			// 0 means centered with respect to the selection area
	offset_y	 = 0;
	real_time	 = false;
	down_scale = prefs.GetInt32(BF_PREFS_PREVIEW_PERCENT, SCALE_ONE);	// ###NOTE: hier ist noch Gefrickel zwischen PreviewBmp und PreviewGroup. Bei Gelegenheit aufraeumen

	document_preview = false;
	changed_settings = true;
}

PreviewBmp::~PreviewBmp(void)
{
	preview_thread.End();	// stop the preview preview_thread
}

void PreviewBmp::SetDragEffect(Bool showeffect)
{
	real_time = showeffect;
}

//----------------------------------------------------------------------------------------
// Limit offset_x/y (if necessary) and return the source rect for the current scale. The
// source rect can be bigger than the source bitmap. In this case clipping has to be done
// before or when scaling the bitmap.
// Function result:		-
// r:									pointer to source rect (or zero if you only want to clip the offsets)
//----------------------------------------------------------------------------------------
void PreviewBmp::ClipOffsets(RECT32* r)
{
	Int32	 image_width;
	Int32	 image_height;
	Int32	 w;
	Int32	 h;
	Int32	 w_scaled;
	Int32	 h_scaled;
	Int32	 tmp;
	RECT32 tmp_rect;

	if (r == 0)
		r = &tmp_rect;

	w = GetWidth();
	h = GetHeight();

	w_scaled = Int32(w * scale_factor[down_scale]);	// resize the source area according to the magnification
	h_scaled = Int32(h * scale_factor[down_scale]);

	image_width	 = bm->image_rect.x2 - bm->image_rect.x1;
	image_height = bm->image_rect.y2 - bm->image_rect.y1;

	r->x1	 = (bm->mask_rect.x2 + bm->mask_rect.x1) >> 1;	// center of the selection
	r->y1	 = (bm->mask_rect.y2 + bm->mask_rect.y1) >> 1;
	r->x1 += offset_x - (w_scaled >> 1);
	r->y1 += offset_y - (h_scaled >> 1);
	r->x2	 = r->x1 + w_scaled;
	r->y2	 = r->y1 + h_scaled;

	if (image_width >= w_scaled)
	{
		if (r->x1 < bm->image_rect.x1)
		{
			tmp = bm->image_rect.x1 - r->x1;
			offset_x += tmp;
			r->x1 += tmp;
			r->x2 += tmp;
		}
		if (r->x2 > bm->image_rect.x2)
		{
			tmp = bm->image_rect.x2 - r->x2;
			offset_x += tmp;
			r->x1 += tmp;
			r->x2 += tmp;
		}
	}
	else	// center horizontally
	{
		r->x1 -= offset_x;
		r->x2 -= offset_x;
		offset_x = 0;
	}

	if (image_height >= h_scaled)
	{
		if (r->y1 < bm->image_rect.y1)
		{
			tmp = bm->image_rect.y1 - r->y1;
			offset_y += tmp;
			r->y1 += tmp;
			r->y2 += tmp;
		}
		if (r->y2 > bm->image_rect.y2)
		{
			tmp = bm->image_rect.y2 - r->y2;
			offset_y += tmp;
			r->y1 += tmp;
			r->y2 += tmp;
		}
	}
	else	// center vertically
	{
		r->y1 -= offset_y;
		r->y2 -= offset_y;
		offset_y = 0;
	}
}

//----------------------------------------------------------------------------------------
// Update preview area (start preview thread, ...)
// Function result:		-
// do_effect:					used to disable the preview thread while dragging
//----------------------------------------------------------------------------------------
Bool PreviewBmp::UpdateBitmap(Bool do_effect)
{
	BM_TILE* draw = nullptr;
	Bool		 updated;
	Int32		 w;
	Int32		 h;

	updated = false;
	w = GetWidth();	// at the beginning the gadget might have no size
	h = GetHeight();

	if (bm && bmp && w && h)
	{
		RECT32 clipped_src_rect;
		RECT32 src_rect;
		Int32	 clipped_w;
		Int32	 clipped_h;
		Int32	 dx;
		Int32	 dy;

		ClipOffsets(&src_rect);

		if (apply_effect)	// apply the effect?
		{
			BM_TILE* thread_tile = nullptr;

			if (real_time)
			{
				preview_thread.End();	// stop the current preview_thread

				get_clipped_size(bm, &src_rect, w, h, &clipped_src_rect, &clipped_w, &clipped_h);
				thread_tile = BfBitmapTileGet(bm, &clipped_src_rect, clipped_w, clipped_h, TILE_BM_SCRATCH, 0);

				if (thread_tile)
				{
					if (clipped_w < w)	// special case for preview_effect/paste_tile_into_bmp?
					{
						dx = (clipped_src_rect.x1 - src_rect.x1) * w / (src_rect.x2 - src_rect.x1);

						thread_tile->xmax -= dx + thread_tile->xmin;
						thread_tile->xmin	 = -dx;
					}

					if (clipped_h < h)	// special case for preview_effect/paste_tile_into_bmp?
					{
						dy = (clipped_src_rect.y1 - src_rect.y1) * h / (src_rect.y2 - src_rect.y1);

						thread_tile->ymax -= dy + thread_tile->ymin;
						thread_tile->ymin	 = -dy;
					}

					if (preview_effect(bm, &clipped_src_rect, thread_tile, this, false, 0) == FILTER_OK)
						updated = true;
				}
			}
			else
			{
				preview_thread.End();	// stop the current preview_thread
				if (changed_settings && bmp_valid && (last_x == offset_x) && (last_y == offset_y))
				{
					darken_bmp(bm, bmp);
					Redraw();
					updated = true;
				}
				else	// moving the preview area
				{
					draw = get_preview_source(bm, &src_rect, w, h, TILE_BM_READ_WRITE, 0);
					if (draw)
					{
						if (bmp_valid)
						{
							switch (get_PX_DEPTH(bm->image_px_format))
							{
								case PX_DEPTH_8:	blend_pattern<UChar>(draw, 0); break;
								case PX_DEPTH_16:	blend_pattern<UInt16>(draw, 0); break;
								case PX_DEPTH_32:	blend_pattern<Float32>(draw, 0); break;
							}
						}

						if (BfConvertTileToBasebmp(draw, nullptr, bmp, 0))
						{
							if (bmp_valid == false)
								darken_bmp(bm, bmp);

							bmp_valid = true;
							Redraw();
							updated = true;
							last_x	= offset_x;
							last_y	= offset_y;
						}
						BfBitmapTileDetach(bm, draw, false);
						draw = nullptr;
					}
				}

				if (updated && do_effect)
				{
					get_clipped_size(bm, &src_rect, w, h, &clipped_src_rect, &clipped_w, &clipped_h);

					thread_tile = BfBitmapTileGet(bm, &clipped_src_rect, clipped_w, clipped_h, TILE_BM_SCRATCH, 0);
					if (thread_tile)
					{
						if (clipped_w < w)	// special case for preview_effect/paste_tile_into_bmp?
						{
							dx = (clipped_src_rect.x1 - src_rect.x1) * w / (src_rect.x2 - src_rect.x1);

							thread_tile->xmax -= dx + thread_tile->xmin;
							thread_tile->xmin	 = -dx;
						}

						if (clipped_h < h)	// special case for preview_effect/paste_tile_into_bmp?
						{
							dy = (clipped_src_rect.y1 - src_rect.y1) * h / (src_rect.y2 - src_rect.y1);

							thread_tile->ymax -= dy + thread_tile->ymin;
							thread_tile->ymin	 = -dy;
						}

						if (changed_settings)			// settings changed?
							document_thread.End();	// then stop the document thread

						preview_thread.Init(bm, &clipped_src_rect, thread_tile, (FT_APPLY_EFFECT*) preview_effect, (BM_FILTER_SETTINGS*)this, false);
						updated = preview_thread.Start();	// this tile has to be released by the preview_thread
					}
				}
			}
		}
		else
		{
			draw = get_preview_source(bm, &src_rect, w, h, TILE_BM_READ_ONLY, 0);
			if (draw)
			{
				if (BfConvertTileToBasebmp(draw, nullptr, bmp, 0))
				{
					Redraw();
					updated = true;
				}
				BfBitmapTileDetach(bm, draw, false);
				draw = nullptr;
			}
		}
	}
	return updated;
}

//----------------------------------------------------------------------------------------
// Set bitmap, filter function, parameters and redraw flag for preview area
// Function result:		-
// t_bm:							bitmap reference (used for allocating and freeing tiles)
// _apply_effect:			filter function
// t_settings:				filter settings
// redraw:						true: redraw preview area
//----------------------------------------------------------------------------------------
void PreviewBmp::SetBitmap(BM_REF t_bm, FT_APPLY_EFFECT* _apply_effect, BM_FILTER_SETTINGS* t_settings, Bool redraw)
{
	apply_effect = _apply_effect;
	bm = t_bm;
	settings = t_settings;

	if (bm)
	{
		ClipOffsets(0);
	}
	else
	{
		offset_x = 0;
		offset_y = 0;
	}
	if (redraw)
		UpdateBitmap(true);
}

//----------------------------------------------------------------------------------------
// Set the new bitmap offset relative to the center
// Function result:		-
// x:									x offset
// y:									y offset
// do_effect:					false: show bitmap without effect	true: apply effect
// scale_xy:					false: x and y are already scaled true: apply scale factor
//----------------------------------------------------------------------------------------
void PreviewBmp::SetOffset(Int32 x, Int32 y, Bool do_effect, Bool scale_xy)
{
	if (scale_xy)
	{
		x = Int32(x * scale_factor[down_scale]);
		y = Int32(y * scale_factor[down_scale]);
	}

	if ((offset_x != x) || (offset_y != y) || do_effect)
	{
		if (bm)
		{
			offset_x = x;
			offset_y = y;

			ClipOffsets(0);
			UpdateBitmap(do_effect);
		}
		else
		{
			offset_x = 0;
			offset_y = 0;
		}
	}
}

//----------------------------------------------------------------------------------------
// Decrease preview zoom
// Function result:		-
// do_effect:					true: apply effect when redrawing
// redraw:						true: redraw preview bitmap
//----------------------------------------------------------------------------------------
Int32	PreviewBmp::Shrink(Bool do_effect, Bool redraw)
{
	if (bm)
	{
		if (down_scale < SCALE_MAX - 1)
		{
			down_scale++;
			ClipOffsets(0);

			if (redraw)
				UpdateBitmap(do_effect);
		}
	}
	return (Int32) ((100.0 / scale_factor[down_scale]) + 0.5);
}

//----------------------------------------------------------------------------------------
// Increase preview zoom
// Function result:		-
// do_effect:					true: apply effect when redrawing
// redraw:						true: redraw preview bitmap
//----------------------------------------------------------------------------------------
Int32	PreviewBmp::Grow(Bool do_effect, Bool redraw)
{
	if (down_scale > 0)
		down_scale -= 1;

	if (redraw)
		UpdateBitmap(do_effect);

	return (Int32) ((100.0 / scale_factor[down_scale]) + 0.5);
}

//----------------------------------------------------------------------------------------
// Return zoom index
// Function result:		zoom index
//----------------------------------------------------------------------------------------
Int32	PreviewBmp::GetScale(void)
{
	return down_scale;
}

//----------------------------------------------------------------------------------------
// De/activate document preview
// Function result:		-
// document_preview:	true: start document preview thread after bitmap preview has finished
//----------------------------------------------------------------------------------------
void PreviewBmp::SetDocumentPreview(Bool _document_preview)
{
	preview_thread.WaitforCompletion();	// wait until preview object is done
	document_thread.End();							// stop the document preview

	if (_document_preview)
	{
		changed_settings = true;
		document_preview = true;

		preview_effect(bm, 0, 0, this, false, 0);	// no preview; just start up the document thread
	}
	else
	{
		document_preview = false;

		BfDiscardChanges(bm);	// discard the previous filter result
		BfUpdateView(bm);			// restore view
	}
}

Bool PreviewBmp::GetMinSize(Int32& w, Int32& h)
{
	return false;
}

Bool PreviewBmp::InitValues(void)
{
	UpdateBitmap(true);

	return true;
}

void PreviewBmp::DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer& msg)
{
	// skip the redraw in case if focus change
	Int32 reason = msg.GetInt32(BFM_DRAW_REASON);
	if (reason == BFM_GOTFOCUS || reason == BFM_LOSTFOCUS)
		return;

	OffScreenOn();
	if (bm && bmp)
		DrawBitmap(bmp, 0, 0, bmp->GetBw(), bmp->GetBh(), 0, 0, bmp->GetBw(), bmp->GetBh(), 0);
}

Bool PreviewBmp::InputEvent(const BaseContainer& msg)
{
	Int32 dev = msg.GetInt32(BFM_INPUT_DEVICE);
	Int32 chn = msg.GetInt32(BFM_INPUT_CHANNEL);

	if (dev == BFM_INPUT_MOUSE)
	{
		BaseContainer action(BFM_ACTION);
		action.SetInt32(BFM_ACTION_ID, GetId());
		action.SetInt32('ACT1', offset_x);
		action.SetInt32('ACT2', offset_y);

		if (chn == BFM_INPUT_MOUSELEFT)
		{
			BaseContainer z;
			Int32					mxn = 0, myn = 0;
			Int32					mx	= msg.GetInt32(BFM_INPUT_X);
			Int32					my	= msg.GetInt32(BFM_INPUT_Y);
			Float					fraction_x = 0;
			Float					fraction_y = 0;

			while (GetInputState(BFM_INPUT_MOUSE, BFM_INPUT_MOUSELEFT, z))
			{
				if (z.GetInt32(BFM_INPUT_VALUE) == 0)
					break;

				mxn = z.GetInt32(BFM_INPUT_X);
				myn = z.GetInt32(BFM_INPUT_Y);

				if (mxn != mx || myn != my)
				{
					Float	ox;
					Float	oy;

					ox = fraction_x + (Float) offset_x + ((mx - mxn) * scale_factor[down_scale]);
					oy = fraction_y + (Float) offset_y + ((my - myn) * scale_factor[down_scale]);

					fraction_x = ox;
					fraction_y = oy;

					if (ox < 0)
						ox = ceil(ox);
					else
						ox = floor(ox);

					if (oy < 0)
						oy = ceil(oy);
					else
						oy = floor(oy);

					fraction_x -= ox;
					fraction_y -= oy;

					SetOffset((Int32)ox, (Int32)oy, real_time, false);

					mx = mxn;
					my = myn;
					action.SetInt32('ACT1', offset_x);
					action.SetInt32('ACT2', offset_y);
					action.SetInt32(BFM_ACTION_INDRAG, true);
					SendParentMessage(action);
				}
			}
			UpdateBitmap(true);
			action.SetInt32(BFM_ACTION_INDRAG, false);
			SendParentMessage(action);
		}
	}
	return true;
}

Int32 PreviewBmp::Message(const BaseContainer& msg, BaseContainer& result)
{
	switch (msg.GetId())
	{
		case BFM_GETCURSORINFO:
			//			if (!CheckPoint(m)) return;
			//			if (CfIsDisabled(true)) return;

			result.SetId(1);
			result.SetInt32(RESULT_CURSOR, MOUSE_MOVE_HAND);
			return true;
	}
	return GeUserArea::Message(msg, result);
}

static Bool	is_bigger_than_life(BM_REF bm, const RECT32* src_rect)
{
	if ((src_rect->x1 < bm->image_rect.x1) || (src_rect->y1 < bm->image_rect.y1) ||
			(src_rect->x2 > bm->image_rect.x2) || (src_rect->y2 > bm->image_rect.y2))
		return true;
	else
		return false;
}

static void	get_clipped_size(BM_REF bm, const RECT32* src_rect, const Int32 w, const Int32 h, RECT32* clipped_rect, Int32* clipped_w, Int32* clipped_h)
{
	*clipped_rect = *src_rect;

	if (is_bigger_than_life(bm, src_rect))
	{
		Int32	src_w;
		Int32	src_h;

		src_w = src_rect->x2 - src_rect->x1;
		src_h = src_rect->y2 - src_rect->y1;

		if (clipped_rect->x1 < bm->image_rect.x1)
			clipped_rect->x1 = bm->image_rect.x1;

		if (clipped_rect->y1 < bm->image_rect.y1)
			clipped_rect->y1 = bm->image_rect.y1;

		if (clipped_rect->x2 > bm->image_rect.x2)
			clipped_rect->x2 = bm->image_rect.x2;

		if (clipped_rect->y2 > bm->image_rect.y2)
			clipped_rect->y2 = bm->image_rect.y2;

		*clipped_w = w * (clipped_rect->x2 - clipped_rect->x1) / src_w;
		*clipped_h = h * (clipped_rect->y2 - clipped_rect->y1) / src_h;
	}
	else
	{
		*clipped_w = w;
		*clipped_h = h;
	}
}

//----------------------------------------------------------------------------------------
// Convert BM_TILE to BaseBitmap. If the tile is smaller, clear the borders of the BaseBitmap
// Function result:		FILTER_OK or FILTER_MEM_ERR
// bm:								bitmap reference
// dt:								bitmap tile (might be smaller than the BaseBitmap)
// bmp:								base bitmap (must equal size or bigger than the bitmap tile)
//----------------------------------------------------------------------------------------
static Int32 paste_tile_into_bmp(BM_REF bm, BM_TILE* dt, BaseBitmap* bmp)
{
	Int32	bmp_w;
	Int32	bmp_h;
	Int32	dw;
	Int32	dh;

	bmp_w = bmp->GetBw();
	bmp_h = bmp->GetBh();
	dw = dt->xmax - dt->xmin;
	dh = dt->ymax - dt->ymin;

	if ((bmp_w > dw) || (bmp_h > dh))	// is the tile smaller than the preview area?
	{
		BM_TILE* scratch_tile;
		RECT32	 scratch_rect;

		scratch_rect.x1 = 0;
		scratch_rect.y1 = 0;
		scratch_rect.x2 = bmp_w;
		scratch_rect.y2 = bmp_h;

		scratch_tile = BfBitmapTileGet(bm, &scratch_rect, bmp_w, bmp_h, TILE_BM_SCRATCH, 0);
		if (scratch_tile)	// scratch tile allocated?
		{
			UChar* src;
			UChar* dst;
			UInt32 bits;

			ClearMem(scratch_tile->addr, scratch_tile->width * (scratch_tile->ymax - scratch_tile->ymin));

			bits = get_PX_BITS(scratch_tile->px_format);
			src	 = (UChar*) dt->addr;
			dst	 = (UChar*) scratch_tile->addr;
			if (dt->ymin < 0)
				dst += scratch_tile->width * (-dt->ymin);		// please note: if the preview area is higher than the tile, ymin contains the negative offset to the top of the preview area!
			if (dt->xmin < 0)
				dst += (bits * (-dt->xmin)) >> 3;						// please note: if the preview area is wider than the tile, xmin contains the negative offset to the left of the preview area!

			dw = (dw * bits) >> 3;												// number of bytes to copy

			for (; dh > 0; dh--)
			{
				CopyMem(src, dst, dw);
				src += dt->width;
				dst += scratch_tile->width;
			}

			BfConvertTileToBasebmp(scratch_tile, nullptr, bmp, 0);
			BfBitmapTileDetach(bm, scratch_tile, false);
		}
		else
		{
			return FILTER_MEM_ERR;
		}
	}
	else	// convert directly
	{
		BfConvertTileToBasebmp(dt, nullptr, bmp, 0);
	}

	return FILTER_OK;
}

//----------------------------------------------------------------------------------------
// Return a preview tile. If the tile is smaller than the preview area, clear the borders of the tile
// Function result:		pointer to allocated tile
// bm:								bitmap reference
// src_rect:					source area
// w:
// dt:								bitmap tile (might be smaller than the BaseBitmap)
// bmp:								base bitmap (must equal size or bigger than the bitmap tile)
//----------------------------------------------------------------------------------------
static BM_TILE* get_preview_source(BM_REF bm, const RECT32* src_rect, Int32 w, Int32 h, Int32 tile_mode, Int32 flags)
{
	BM_TILE* result_tile = nullptr;

	if (is_bigger_than_life(bm, src_rect) == false)
		return BfBitmapTileGet(bm, src_rect, w, h, tile_mode, flags);

	result_tile = BfBitmapTileGet(bm, src_rect, w, h, TILE_BM_SCRATCH, 0);
	if (result_tile)
	{
		RECT32	 clipped_src_rect;
		BM_TILE* clipped_tile = nullptr;
		Int32		 clipped_w;
		Int32		 clipped_h;

		get_clipped_size(bm, src_rect, w, h, &clipped_src_rect, &clipped_w, &clipped_h);

		clipped_tile = BfBitmapTileGet(bm, &clipped_src_rect, clipped_w, clipped_h, tile_mode, 0);
		if (clipped_tile)
		{
			UChar* src;
			UChar* dst;
			UInt32 dw;
			UInt32 dh;

			ClearMem(result_tile->addr, result_tile->width * (result_tile->ymax - result_tile->ymin));

			src	 = (UChar*) clipped_tile->addr;
			dst	 = (UChar*) result_tile->addr;
			dst += result_tile->width * (clipped_tile->ymin - result_tile->ymin);
			dst += (get_PX_BITS(result_tile->px_format) * (clipped_tile->xmin - result_tile->xmin)) >> 3;

			dw = (get_PX_BITS(result_tile->px_format) * (clipped_tile->xmax - clipped_tile->xmin)) >> 3;

			for (dh = clipped_tile->ymax - clipped_tile->ymin; dh > 0; dh--)
			{
				CopyMem(src, dst, dw);
				src += clipped_tile->width;
				dst += result_tile->width;
			}
			BfBitmapTileDetach(bm, clipped_tile, false);
		}
		else
		{
			BfBitmapTileDetach(bm, result_tile, false);
			result_tile = 0;
		}
	}
	return result_tile;
}

//----------------------------------------------------------------------------------------
// FT_APPLY_EFFECT: Preview function that applies the effect and stores the result in a destination tile
// After the dialog preview is finished the thread for the document preview is started.
// Function result:		FILTER_OK or FILTER_MEM_ERR
// bm:								bitmap reference
// src_rect:					source area the effect should be applied on
// dt:								destination for storing the preview result (dispose of it when finished) or zero (start document thread)
// pb:								preview bitmap class
// update_view:				should be false
// preview_thread:		filter thread class or zero (not threaded)
//----------------------------------------------------------------------------------------
Int32	preview_effect(BM_REF bm, const RECT32* src_rect, BM_TILE* dt, PreviewBmp* pb, Bool update_view, BaseThread* preview_thread)
{
	Int32	err;

	err = FILTER_OK;

	if (dt)	// redraw the preview object?
	{
		err = pb->apply_effect(bm, src_rect, dt, pb->settings, update_view, preview_thread);
		if (err == FILTER_OK)
		{
			err = paste_tile_into_bmp(bm, dt, pb->bmp);	// paste tile into the existing bitmap
			BfBitmapTileDetach(bm, dt, false);

			if (err == FILTER_OK)
				pb->Redraw(preview_thread != 0);	// send a message if this is a thread (immediate redraw does not work in this case)
		}
		else																	// filter was canceled, free tile
		{
			BfBitmapTileDetach(bm, dt, false);
		}
	}

	if (err == FILTER_OK)
	{
		if (pb->changed_settings)
		{
			pb->changed_settings = false;	// changed settings have been noticed
			if (pb->document_preview)			// start thread for document preview?
			{
				pb->document_thread.Init(bm, 0, 0, pb->apply_effect, pb->settings, true);
				if (!pb->document_thread.Start())
					err = FILTER_MISC_ERR;
			}
		}
	}

	return err;
}

//----------------------------------------------------------------------------------------
// Apply checkboard pattern to the preview bitmap
// Function result:		-
// bm:								bitmap reference
// bmp:								base bitmap
//----------------------------------------------------------------------------------------
static void	darken_bmp(BM_REF bm, BaseBitmap* bmp)
{
	Int32	 w;
	Int32	 h;
	Int32	 bpp;
	Int32	 bits;
	Int32	 width;
	UChar* line;

	w = bmp->GetBw();
	h = bmp->GetBh();
	bits	= bmp->GetBt();		// bits per pixel
	width = bmp->GetBpz();	// bytes per line
	bpp = bits >> 3;				// bytes per pixel

	if (bpp > 3)
		bpp = 3;	// BaseBitmap is using only three bytes per pixel; even if it is saying something different

	if (width < (w * 3))
		width = w * 3;

	if (width <= 0)
		return;

	ifnoerr (line = NewMemClear(UChar, width))	// but the line width has to take the extra bytes into account (otherwise GetLine overwrites memory)
	{
		Int32	y;

		for (y = 0; y < h; y++)
		{
			bmp->GetPixelCnt(0, y, w, (PIX*)line, bpp, COLORMODE_RGB, PIXELCNT_0);
			blend_line(line, y, w * bpp, bpp << 3);
			bmp->SetPixelCnt(0, y, w, (PIX*)line, bpp, COLORMODE_RGB, PIXELCNT_0);
		}
		DeleteMem(line);
	}
}

//----------------------------------------------------------------------------------------
// Blend a line with a checkboard pattern
// Function result:		-
// dst:								line pointer
// y:									y-coordinate of the line
// w:									width of the line in bytes
// l:									length of the light/dark area in bytes
//----------------------------------------------------------------------------------------
static void	blend_line(UChar* dst, Int32 y, Int32 w, Int32 l)
{
#define	PAT_WIDTH	 8
#define	PAT_HEIGHT 8
#define	BLEND_WHITE(v) (((v << 3) - v + 0xc0L) >> 3)
#define	BLEND_BLACK(v) (((v << 3) - v + 0xa0L) >> 3)

	Int32	i;
	Int32	x;
	Int32	v;

	if (y & PAT_HEIGHT)
	{
		for (x = w; x > 0; )
		{
			for (i = (x > l ? l : x); i > 0; i--)
			{
				v = *dst;
				*dst++ = (UChar) BLEND_BLACK(v);
			}
			x -= l;

			for (i = (x > l ? l : x); i > 0; i--)
			{
				v = *dst;
				*dst++ = (UChar) BLEND_WHITE(v);
			}
			x -= l;
		}
	}
	else
	{
		for (x = w; x > 0; )
		{
			for (i = (x > l ? l : x); i > 0; i--)
			{
				v = *dst;
				*dst++ = (UChar) BLEND_WHITE(v);
			}
			x -= l;

			for (i = (x > l ? l : x); i > 0; i--)
			{
				v = *dst;
				*dst++ = (UChar) BLEND_BLACK(v);
			}
			x -= l;
		}
	}

	#undef	BLEND_BLACK
	#undef	BLEND_WHITE
	#undef	PAT_HEIGHT
	#undef	PAT_WIDTH
}

PreviewGroup::PreviewGroup(void)
{
	dlg = 0;
	src_preview_id = 0;
	dst_preview_id = 0;
	zoom_in_id	= 0;
	zoom_out_id = 0;
	zoom_percent_id = 0;
	real_time = false;
}

PreviewGroup::~PreviewGroup(void)
{
	BaseContainer	prefs;

	prefs = GetGlobalFilterPrefs(BF_PREFS_GLOBAL);

	if (src_preview_id)
		prefs.SetInt32(BF_PREFS_PREVIEW_PERCENT, src_preview.GetScale());
	else if (dst_preview_id)
		prefs.SetInt32(BF_PREFS_PREVIEW_PERCENT, dst_preview.GetScale());

	SetGlobalFilterPrefs(BF_PREFS_GLOBAL, prefs);
}

//----------------------------------------------------------------------------------------
// Set preview source bitmap
// Function result:		-
//----------------------------------------------------------------------------------------
void PreviewGroup::Create(GeDialog* _dlg, Int32 _group_id)
{
	BaseContainer	prefs;
	Int32					w;
	Int32					h;
	Int32					scale;
	Bool do_hlayout;

	prefs = GetGlobalFilterPrefs(BF_PREFS_GLOBAL);

	w = prefs.GetInt32(BF_PREFS_PREVIEW_WIDTH, BF_PREFS_PREVIEW_WIDTH_DFLT);
	h = prefs.GetInt32(BF_PREFS_PREVIEW_HEIGHT, BF_PREFS_PREVIEW_HEIGHT_DFLT);
	scale = Int32((100.0 / scale_factor[prefs.GetInt32(BF_PREFS_PREVIEW_PERCENT, SCALE_ONE)]) + 0.5);
	real_time = true;

	dlg = _dlg;

	if (prefs.GetInt32(BF_PREFS_SRC_PREVIEW, BF_PREFS_SRC_PREVIEW_DFLT))
		src_preview_id = GAGDET_BMFILTER_SRC;
	dst_preview_id = GAGDET_BMFILTER_DST;
	zoom_in_id	= GAGDET_BMFILTER_GROW;
	zoom_out_id = GAGDET_BMFILTER_SHRINK;
	zoom_percent_id = GAGDET_BMFILTER_PERCENT;

	dlg->LayoutFlushGroup(_group_id);

	if ((src_preview_id == 0) || (dst_preview_id == 0))
		do_hlayout = false;		// zoom icons are below the preview
	else
		do_hlayout = true;		// zoom icons are between the previews

	dlg->GroupBegin(0, BFH_CENTER | BFV_TOP, !do_hlayout, do_hlayout, String(), 0);
	{
		dlg->GroupBorderSpace(0, 0, 0, 16);	// add at bottom border

		if (src_preview_id)
			AddPreview(dlg, w, h, src_preview, src_preview_id);
		else if (dst_preview_id)
			AddPreview(dlg, w, h, dst_preview, dst_preview_id);

		if (zoom_in_id && zoom_out_id)
		{
			dlg->GroupBegin(0, BFV_CENTER, do_hlayout, !do_hlayout, String(), 0);
			{
				BitmapButtonCustomGui* zoomin	 = nullptr;
				BitmapButtonCustomGui* zoomout = nullptr;

				dlg->GroupBorderSpace(4, 4, 4, 4);	// some room for the icons
				{
					BaseContainer settings;
					settings.SetBool(BITMAPBUTTON_BUTTON, true);
					settings.SetInt32(BITMAPBUTTON_BORDER, BORDER_OUT);
					zoomin = (BitmapButtonCustomGui*)dlg->AddCustomGui(zoom_in_id, CUSTOMGUI_BITMAPBUTTON, String(), BFH_FIT, 0, 0, settings);
				}
				dlg->AddStaticText(zoom_percent_id, BFH_CENTER, SizeChr(60), 0, String::IntToString(scale) + "\\u0020\\u0025", 0);
				{
					BaseContainer settings;
					settings.SetBool(BITMAPBUTTON_BUTTON, true);
					settings.SetInt32(BITMAPBUTTON_BORDER, BORDER_OUT);
					zoomout = (BitmapButtonCustomGui*)dlg->AddCustomGui(zoom_out_id, CUSTOMGUI_BITMAPBUTTON, String(), BFH_FIT, 0, 0, settings);
				}

				if (zoomin)
				{
					IconData dat;
					GetIcon(RESOURCEIMAGE_BITMAPFILTERPLUS, &dat);
					zoomin->SetImage(&dat);
				}
				if (zoomout)
				{
					IconData dat;
					GetIcon(RESOURCEIMAGE_BITMAPFILTERMINUS, &dat);
					zoomout->SetImage(&dat);
				}
			}
			dlg->GroupEnd();
		}

		if (src_preview_id && dst_preview_id)
			AddPreview(dlg, w, h, dst_preview, dst_preview_id);
	}
	dlg->GroupEnd();

	dlg->LayoutChanged(_group_id);
}

//----------------------------------------------------------------------------------------
// Set preview source bitmap
// Function result:		-
//----------------------------------------------------------------------------------------
void PreviewGroup::SetSource(BM_REF bm, BM_FILTER_SETTINGS* settings, Bool redraw)
{
	src_preview.SetBitmap(bm, 0, settings, redraw);
	src_preview.SetDragEffect(true);
}

//----------------------------------------------------------------------------------------
// Set preview filter bitmap and filter function
// Function result:		-
//----------------------------------------------------------------------------------------
void PreviewGroup::SetDestination(BM_REF bm, FT_APPLY_EFFECT* apply_effect, BM_FILTER_SETTINGS* settings, Bool redraw, Bool document_preview)
{
	dst_preview.document_preview = document_preview;
	dst_preview.changed_settings = true;

	dst_preview.SetBitmap(bm, apply_effect, settings, redraw);
	dst_preview.SetDragEffect(real_time);
}

void PreviewGroup::UpdateSource(Bool do_effect)
{
	src_preview.UpdateBitmap(do_effect);
}

void PreviewGroup::UpdateDestination(Bool do_effect)
{
	dst_preview.UpdateBitmap(do_effect);
}

//----------------------------------------------------------------------------------------
// Decrease zoom level
// Function result:		-
//----------------------------------------------------------------------------------------
void PreviewGroup::ZoomOut(void)
{
	Int32	zoom_value;

	zoom_value = 0;
	if (src_preview_id)
		zoom_value = src_preview.Shrink(false, true);

	if (dst_preview_id)
		zoom_value = dst_preview.Shrink(true, true);

	if (zoom_value)
		dlg->SetString(zoom_percent_id, String::IntToString(zoom_value) + "\\u0020\\u0025");
}

//----------------------------------------------------------------------------------------
// Increase zoom level
// Function result:		-
//----------------------------------------------------------------------------------------
void PreviewGroup::ZoomIn(void)
{
	Int32	zoom_value;

	zoom_value = 0;
	if (src_preview_id)
		zoom_value = src_preview.Grow(false, true);

	if (dst_preview_id)
		zoom_value = dst_preview.Grow(true, true);

	if (zoom_value)
		dlg->SetString(zoom_percent_id, String::IntToString(zoom_value) + "\\u0020\\u0025");
}

//----------------------------------------------------------------------------------------
// Handle events regarding the preview group
// Function result:		false: event was for other gadgets true: event was handled
//----------------------------------------------------------------------------------------
Bool PreviewGroup::Command(Int32 id, const BaseContainer& msg)
{
	if (id == src_preview_id)
		dst_preview.SetOffset(msg.GetInt32('ACT1'), msg.GetInt32('ACT2'), real_time || !msg.GetInt32(BFM_ACTION_INDRAG), false);
	else if (id == dst_preview_id)
		src_preview.SetOffset(msg.GetInt32('ACT1'), msg.GetInt32('ACT2'), true, false);
	else if (id == zoom_in_id)
		ZoomIn();
	else if (id == zoom_out_id)
		ZoomOut();
	else
		return false;

	return true;
}

void PreviewGroup::AddPreview(GeDialog* dialog, Int32 w, Int32 h, PreviewBmp& preview, Int32 previewId)
{
	dialog->GroupBegin(0, BFV_CENTER, 1, 0, String(), 0);
	{
		dialog->GroupBorderNoTitle(BORDER_THIN_IN);
		dialog->AddUserArea(previewId, BFH_LEFT, SizePix(w), SizePix(h));
	}
	dialog->GroupEnd();

	dialog->AttachUserArea(preview, previewId, USERAREA_COREMESSAGE | USERAREA_DONT_MIRROR);
}

//----------------------------------------------------------------------------------------
// De/activate document preview
// Function result:		-
// document_preview:	true: start document preview thread false: stop document preview and discard results
//----------------------------------------------------------------------------------------
void PreviewGroup::SetDocumentPreview(Bool document_preview)
{
	dst_preview.SetDocumentPreview(document_preview);
}

//----------------------------------------------------------------------------------------
// Stop preview and document thread because of changed filter settings
// Function result:		-
//----------------------------------------------------------------------------------------
void PreviewGroup::ChangedSettings(void)
{
	dst_preview.preview_thread.End();
	dst_preview.document_thread.End();

	dst_preview.changed_settings = true;	// set dirty flag
}

//----------------------------------------------------------------------------------------
// Update (destination) preview area (after filter settings have been changed)
// Function result:		-
//----------------------------------------------------------------------------------------
void PreviewGroup::Update(void)
{
	dst_preview.UpdateBitmap(true);
}

//----------------------------------------------------------------------------------------
// Wait until the effect has been applied to the document
// Function result:		-
//----------------------------------------------------------------------------------------
void PreviewGroup::FinishDocumentUpdate(void)
{
	if (dst_preview.document_preview == false)	// document preview disabled?
	{
		dst_preview.preview_thread.End();					// stop redraw in the preview area
		dst_preview.SetDocumentPreview(true);			// start document preview thread
	}
	else
	{
		if (dst_preview.preview_thread.IsRunning())								// is the preview running
		{
			if (dst_preview.changed_settings)												// update the document?
			{
				if (dst_preview.document_thread.IsRunning() == false)	// is the document thread not running so far?
				{
					dst_preview.preview_thread.End();										// stop the preview
					dst_preview.SetDocumentPreview(true);								// start the document thread
				}
			}
		}
	}

	dst_preview.document_thread.WaitforCompletion();	// wait until the document thread has finished
}

