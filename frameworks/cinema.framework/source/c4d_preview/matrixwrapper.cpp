#include "c4d_general.h"
#include "c4d_memory.h"
#include "c4d_gui.h"

#include "x4d_filter.h"
#include "c4d_bitmapfilter.h"
#include	"filterpreview.h"
#include	"matrixutil.h"
#include	"matrixwrapper.h"
#include	"linefetchutil.h"

Int32	do_matrix_effect_1dt(BM_REF bm, BM_TILE* dt, MATRIX_REF _emr, Int32 tile_flags)
{
	RECT32	bounds;
	UChar*	dst = nullptr;
	Int32		x1, y1, x2, y2;
	Int32		width;
	Int32		y;
	UChar*	src_rows[MAXTRIX_MAX_COLUMNS];
	Int32		err = FILTER_OK;
	ROW_REF	src_rr;
	Int32		x_offset;
	Int32		y_offset;
	Int32		no_columns;
	Int32		no_rows;

	bounds = *(RECT32*) &dt->xmin;
	x1 = bounds.x1;
	y1 = bounds.y1;
	x2 = bounds.x2;
	y2 = bounds.y2;

	dst = (UChar*) dt->addr;

	width = bounds.x2 - bounds.x1;	// width of the selected area

	get_effect_matrix_info(_emr, &no_columns, &no_rows, &x_offset, &y_offset);

	if ((src_rr = new_row_fetcher(bm, x1 - x_offset, x2 + (no_columns - x_offset - 1), tile_flags, TILE_BM_READ_ONLY, 0)) != 0)
	{
		Int32	j;

		for (j = 0; j < no_rows - 1; j++)
		{
			src_rows[j] = rf_get_bitmap_row(src_rr, y1 - y_offset + j);
			if (src_rows[j] == 0L)							// unable to access this line?
			{
				delete_row_fetcher(src_rr, true);	// free all buffered lines
				return FILTER_MEM_ERR;
			}
		}

		for (y = y1; y < y2; y++)
		{
			j = no_rows - 1;
			src_rows[j] = rf_get_bitmap_row(src_rr, y + (j - y_offset));	// ask for the next line

			if (src_rows[j] == 0L)																				// unable to access this line?
			{
				err = FILTER_MEM_ERR;
				break;
			}

			apply_matrix_effect(_emr, (void**) src_rows, dst, width);	// apply the matrix function to the current destination line
			rf_free_bitmap_row(src_rr, y - y_offset);									// we don't need this line for the next loop

			for (j = 1; j < no_rows; j++)															// swap the source line pointers
				src_rows[j - 1] = src_rows[j];

			dst += dt->width;								// next destination line
		}
		delete_row_fetcher(src_rr, true);	// free all buffered lines
	}
	return err;
}

Int32 do_matrix_effect(BM_REF bm, MATRIX_REF _emr, BaseThread* thread, Int32 tile_flags, Bool update_view, String* apply_filter_str)
{
	BM_TILE*		dt;
	RECT32			bounds;
	UChar*			dst = nullptr;
	Int32				x1, y1, x2, y2;
	Int32				width, height;
	Int32				y;
	UChar*			src_rows[MAXTRIX_MAX_COLUMNS];
	Int32				err = FILTER_OK;
	ROW_REF			src_rr;
	Int32				x_offset;
	Int32				y_offset;
	Int32				no_columns;
	Int32				no_rows;
	PROGRESS_ID	pid = 0;

	Int32	progress_cnt;
	Int32	progress_max;

	x1 = bm->mask_rect.x1;
	y1 = bm->mask_rect.y1;
	x2 = bm->mask_rect.x2;
	y2 = bm->mask_rect.y2;

	width	 = bm->mask_rect.x2 - bm->mask_rect.x1;	// width of the selected area
	height = bm->mask_rect.y2 - bm->mask_rect.y1;	// height of the selected area

	progress_cnt = 0;
	progress_max = (height + bm->preferred_tile_height - 1) / bm->preferred_tile_height;
	pid = BfProgressNew(bm);

	get_effect_matrix_info(_emr, &no_columns, &no_rows, &x_offset, &y_offset);

	if ((src_rr = new_row_fetcher(bm, x1 - x_offset, x2 + (no_columns - x_offset - 1), tile_flags, TILE_BM_READ_ONLY, 0)) != 0)
	{
		Int32	j;

		for (j = 0; j < no_rows - 1; j++)
		{
			src_rows[j] = rf_get_bitmap_row(src_rr, y1 - y_offset + j);
			if (src_rows[j] == 0L)							// unable to access this line?
			{
				delete_row_fetcher(src_rr, true);	// free all buffered lines
				return FILTER_MEM_ERR;
			}
		}

		bounds = bm->mask_rect;
		dt = nullptr;

		for (y = y1; y < y2; y++)
		{
			if (((y - y1) % bm->preferred_tile_height) == 0)
			{
				BfProgressUpdate(bm, pid, progress_cnt++, progress_max, *apply_filter_str);

				if (dt)
				{
					BfBitmapTileDetach(bm, dt, true);	// apply the destination tile
					BfUpdateView(bm);
				}

				bounds.y1 = y;
				bounds.y2 = LMin(y2, y + bm->preferred_tile_height);
				dt = BfBitmapTileGet(bm, &bounds, 0, 0, TILE_BM_WRITE, 0);

				if (dt == nullptr)
				{
					err = FILTER_MEM_ERR;
					break;
				}

				dst = (UChar*) dt->addr;

				if (thread && thread->TestBreak())	// force exit?
				{
					err = FILTER_ABORT;
					break;
				}
			}

			j = no_rows - 1;
			src_rows[j] = rf_get_bitmap_row(src_rr, y + (j - y_offset));	// ask for the next line

			if (src_rows[j] == 0L)																				// unable to access this line?
			{
				err = FILTER_MEM_ERR;
				break;
			}

			apply_matrix_effect(_emr, (void**) src_rows, dst, width);	// apply the matrix function to the current destination line
			rf_free_bitmap_row(src_rr, y - y_offset);									// we don't need this line for the next loop

			for (j = 1; j < no_rows; j++)															// swap the source line pointers
				src_rows[j - 1] = src_rows[j];

			dst += dt->width;	// next destination line
		}

		if (dt)
		{
			BfBitmapTileDetach(bm, dt, err == FILTER_OK);	// apply the destination tile
			BfUpdateView(bm);
		}

		delete_row_fetcher(src_rr, true);	// free all buffered lines
		BfProgressDelete(bm, pid);
	}

	return err;
}
