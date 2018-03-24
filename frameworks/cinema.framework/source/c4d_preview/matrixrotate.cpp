#include "c4d_general.h"
#include "c4d_shader.h"
#include "c4d_memory.h"

#include "matrixrotate.h"


#define	MAX_POINTS 16

struct MPOINT
{
	Float64	x;
	Float64	y;
};

struct MPOINT_LE
{
	MPOINT_LE* prev;
	MPOINT_LE* next;
	MPOINT		 p;
};

struct MBOUNDS
{
	Int32		no_pts;

	Float64	xmin;	// bounding rectangle
	Float64	ymin;
	Float64	xmax;
	Float64	ymax;

	MPOINT	pts[MAX_POINTS];
};

static void	rotate_m90(WEIGHT_FMATRIX* m);
static void	rotate_m180(WEIGHT_FMATRIX* m);
static void	rotate_m270(WEIGHT_FMATRIX* m);
static Float64 get_matrix_value(const WEIGHT_FMATRIX* m, Int32 x, Int32 y);
static void	add_to_matrix_value(WEIGHT_FMATRIX* m, Int32 x, Int32 y, Float64 value);
static void	distribute_source_element(Int32 x_src, Int32 y_src, Float64 src_value, Float64 r, WEIGHT_FMATRIX* output_matrix);
static void	matrix_entry_to_bounds(Int32 x, Int32 y, Float64 r, MBOUNDS* out);
static void	matrix_entries_to_bounds(Int32 x1, Int32 y1, Int32 x2, Int32 y2, Float64 r, MBOUNDS* out);
static Float64 get_intersection_area(MBOUNDS* src_me, MBOUNDS* dst_me);
static Bool	sect_polygons(MBOUNDS* src_me, MBOUNDS* dst_me, MBOUNDS* sect_me);
static Bool	sect_lines(MPOINT* line_a, MPOINT* line_b, MPOINT* sect);
static Int32 intersect_lines(MPOINT* s1, MPOINT* s2, MPOINT* out);
static Bool	test_inside(MPOINT* pts, Int32 no_pts, MPOINT* check_point);
static Float64 get_simple_polygon_area(MBOUNDS* me);


void rotate_matrix(const WEIGHT_FMATRIX* input_matrix, WEIGHT_FMATRIX* output_matrix, Float64 r)
{
	Float32* dst_value;
	Int32		 x_dst;
	Int32		 y_dst;
	Int32		 x_src;
	Int32		 y_src;
	Int32		 q;
	MBOUNDS	 mm;
	Int32		 xmin;
	Int32		 ymin;
	Int32		 xmax;
	Int32		 ymax;

	q	 = (Int32)floor(r / PI05);
	r	 = r - (q * PI05);
	q %= 4;	// # of 90 degree rotations
	if (q < 0)
		q = 4 - q;

	matrix_entries_to_bounds(-input_matrix->x_origin, input_matrix->y_origin - (input_matrix->no_matrix_columns - 1), input_matrix->no_matrix_rows - input_matrix->x_origin - 1, input_matrix->y_origin, r, &mm);
	xmin = (Int32)floor(mm.xmin + 0.5);	// x index of the first intersected destination element
	ymin = (Int32)floor(mm.ymin + 0.5);
	xmax = (Int32)ceil(mm.xmax + 0.5);	// x index of the first destination element that's not intersected anymore
	ymax = (Int32)ceil(mm.ymax + 0.5);
	xmax--;															// x index of the las element that's intersected
	ymax--;

	output_matrix->no_matrix_columns = xmax - xmin + 1;
	output_matrix->no_matrix_rows = ymax - ymin + 1;
	output_matrix->x_origin = -xmin;
	output_matrix->y_origin = ymax;

	if (output_matrix->no_matrix_columns > MAXTRIX_MAX_COLUMNS)
	{
		output_matrix->no_matrix_columns = MAXTRIX_MAX_COLUMNS;
		output_matrix->x_origin = MAXTRIX_MAX_COLUMNS >> 1;
	}

	if (output_matrix->no_matrix_rows > MAXTRIX_MAX_ROWS)
	{
		output_matrix->no_matrix_rows = MAXTRIX_MAX_ROWS;
		output_matrix->y_origin = MAXTRIX_MAX_ROWS >> 1;
	}

	if (r != 0.0)
	{
		dst_value = output_matrix->matrix_values;
		for (y_dst = 0; y_dst < output_matrix->no_matrix_rows; y_dst++)
		{
			for (x_dst = 0; x_dst < output_matrix->no_matrix_columns; x_dst++)
				*dst_value++ = 0.0;
		}

		for (y_src = 0; y_src < input_matrix->no_matrix_rows; y_src++)
		{
			for (x_src = 0; x_src < input_matrix->no_matrix_columns; x_src++)
			{
				Int32		xc;
				Int32		yc;
				Float64	src_value;

				xc = x_src - input_matrix->x_origin;	// negative x values are on the left in the matrix
				yc = input_matrix->y_origin - y_src;	// negative y values are at the bottom of the matrix (not like on the screen)

				if (xc == yc)
				{
					if (xc == 0)
						yc = xc;
				}

				src_value = get_matrix_value(input_matrix, xc, yc);
				distribute_source_element(xc, yc, src_value, r, output_matrix);
			}
		}
	}
	else	// simple rotation is sufficient
	{
		WEIGHT_FMATRIX_MAX* tmp;

		tmp	 = (WEIGHT_FMATRIX_MAX*) output_matrix;
		*tmp = *(WEIGHT_FMATRIX_MAX*) input_matrix;	// just copy the input matrix
	}

	switch (q)
	{
		case	1:	rotate_m90(output_matrix); break;
		case	2:	rotate_m180(output_matrix);	break;
		case	3:	rotate_m270(output_matrix);	break;
	}
}

//----------------------------------------------------------------------------------------
// Rotate a matrix by 90 degrees (counterclockwise)
// Function result:		-
// m:									matrix object
//----------------------------------------------------------------------------------------
static void	rotate_m90(WEIGHT_FMATRIX* m)
{
	WEIGHT_FMATRIX_MAX tmp;
	Float32* src;
	Float32* dst;
	Int32		 x;
	Int32		 y;

	tmp = *(WEIGHT_FMATRIX_MAX*) m;
	src = tmp.matrix_values;

	m->no_matrix_columns = tmp.no_matrix_rows;
	m->no_matrix_rows = tmp.no_matrix_columns;
	m->x_origin = tmp.y_origin;
	m->y_origin = tmp.x_origin;

	for (x = 0; x < m->no_matrix_columns; x++)
	{
		dst	 = m->matrix_values + x;
		dst += m->no_matrix_rows * m->no_matrix_columns;

		for (y = m->no_matrix_rows; y > 0; y--)
		{
			dst -= m->no_matrix_columns;
			*dst = *src++;
		}
	}
}

//----------------------------------------------------------------------------------------
// Rotate a matrix by 180 degrees (counterclockwise)
// Function result:		-
// m:									matrix object
//----------------------------------------------------------------------------------------
static void	rotate_m180(WEIGHT_FMATRIX* m)
{
	WEIGHT_FMATRIX_MAX tmp;
	Float32* src;
	Float32* dst;
	Int32		 x;
	Int32		 y;

	tmp = *(WEIGHT_FMATRIX_MAX*) m;
	src = tmp.matrix_values;

	m->no_matrix_columns = tmp.no_matrix_columns;
	m->no_matrix_rows = tmp.no_matrix_rows;
	m->x_origin = tmp.y_origin;
	m->y_origin = tmp.x_origin;

	dst	 = m->matrix_values;
	dst += m->no_matrix_rows * m->no_matrix_columns;

	for (x = 0; x < m->no_matrix_columns; x++)
	{
		for (y = m->no_matrix_rows; y > 0; y--)
			*(--dst) = *src++;
	}
}

//----------------------------------------------------------------------------------------
// Rotate a matrix by 270 degrees (counterclockwise)
// Function result:		-
// m:									matrix object
//----------------------------------------------------------------------------------------
static void	rotate_m270(WEIGHT_FMATRIX* m)
{
	WEIGHT_FMATRIX_MAX tmp;
	Float32* src;
	Float32* dst;
	Int32		 x;
	Int32		 y;

	tmp = *(WEIGHT_FMATRIX_MAX*) m;
	src = tmp.matrix_values;

	m->no_matrix_columns = tmp.no_matrix_rows;
	m->no_matrix_rows = tmp.no_matrix_columns;
	m->x_origin = tmp.y_origin;
	m->y_origin = tmp.x_origin;

	for (x = m->no_matrix_columns - 1; x >= 0; x--)
	{
		dst = m->matrix_values + x;

		for (y = m->no_matrix_rows; y > 0; y--)
		{
			*dst = *src++;
			dst += m->no_matrix_columns;
		}
	}
}

//----------------------------------------------------------------------------------------
// Return a matrix value (positions outside the matrix are clipped)
// Function result:		matrix value
// m:									matrix object
// x:									x coordinate (relative to the matrix center, negative values are left)
// y:									y coordinate (relative to the matrix center, positive values are top)
//----------------------------------------------------------------------------------------
static Float64 get_matrix_value(const WEIGHT_FMATRIX* m, Int32 x, Int32 y)
{
	const Float32* v;

	x += m->x_origin;
	y	 = m->y_origin - y;

	if ((x < 0) || (x >= m->no_matrix_columns) || (y < 0) || (y >= m->no_matrix_rows))
		return 0.0;

	v	 = m->matrix_values;
	v += y * m->no_matrix_columns;
	v += x;

	return *v;
}

//----------------------------------------------------------------------------------------
// Add a value to a matrix element's value
// Function result:		-
// m:									matrix object
// x:									x coordinate (relative to the matrix center, negative values are left)
// y:									y coordinate (relative to the matrix center, positive values are top)
// value:							value to add
//----------------------------------------------------------------------------------------
static void	add_to_matrix_value(WEIGHT_FMATRIX* m, Int32 x, Int32 y, Float64 value)
{
	Float32* v;

	x += m->x_origin;
	y	 = m->y_origin - y;

	if ((x < 0) || (x >= m->no_matrix_columns) || (y < 0) || (y >= m->no_matrix_rows))
		return;

	v	 = m->matrix_values;
	v += y * m->no_matrix_columns;
	v += x;

	*v += (Float32)value;
}

//----------------------------------------------------------------------------------------
// Distribute the value of a rotated source matrix element over the intersected destination
// matrix elements by weighting its value with the intersection area
// Function result:		-
// x_src:							x coordinate in the source matrix (relative to the matrix center)
// y_src:							y coordinate in the source matrix	(relative to the matrix center)
// src_value:					value of the source matrix element
// r:									rotation angle for x_src and y_src
// output_matrix:
//----------------------------------------------------------------------------------------
static void	distribute_source_element(Int32 x_src, Int32 y_src, Float64 src_value, Float64 r, WEIGHT_FMATRIX* output_matrix)
{
	MBOUNDS	src_me;
	Int32		xmin;
	Int32		ymin;
	Int32		xmax;
	Int32		ymax;
	Int32		x;
	Int32		y;
	Float64	ws;

	//	Tab Size: 2
	//	Comments:																								*Column 60*

	matrix_entry_to_bounds(x_src, y_src, r, &src_me);	// create a bounding polygon

	xmin = (Int32)floor(src_me.xmin + 0.5);						// x index of the first intersected destination element
	ymin = (Int32)floor(src_me.ymin + 0.5);
	xmax = (Int32)ceil(src_me.xmax + 0.5);						// x index of the first destination element that's not intersected anymore
	ymax = (Int32)ceil(src_me.ymax + 0.5);

	ws = 0;

	for (y = ymin; y < ymax; y++)
	{
		for (x = xmin; x < xmax; x++)
		{
			MBOUNDS	dst_me;
			Float64	weight;

			matrix_entry_to_bounds(x, y, 0, &dst_me);	// create a bounding polygon for the destination element
			weight = get_intersection_area(&src_me, &dst_me);

			ws += weight;

			if (weight != 0.0)
			{
				add_to_matrix_value(output_matrix, x, y, src_value * weight);
			}
		}
	}
}

//----------------------------------------------------------------------------------------
// Create a bounding polygon for a matrix entry. Matrix Entry x/y = ( 0 /0 ) means that the
// polygon will be ( -0.5/-0.5 ), ( 0.5/-0.5 ), ( 0.5/0.5 ), ( -0.5/0.5 ) and again ( -0.5/-0.5 )
// The polygon is counterclockwise.
// Function result:		-
// x:									x coordinate (relative to the matrix center)
// y:									y coordinate (relative to the matrix center)
// r:									rotation angle
// out:								used to return the polygon
//----------------------------------------------------------------------------------------
static void	matrix_entry_to_bounds(Int32 x, Int32 y, Float64 r, MBOUNDS* out)
{
	Float64	cosa;
	Float64	sina;
	Float64	fx;
	Float64	fy;
	Int32		i;

	fx = (Float64) x - 0.5;
	fy = (Float64) y - 0.5;

	cosa = Cos(r);
	sina = Sin(r);

	if ((sina == 1.0) || (sina == -1.0))	// this litte extra checking is necessary because Cos( PI05 ) is not zero!
		cosa = 0.0;

	if ((cosa == 1.0) || (cosa == -1.0))
		sina = 0.0;

	out->no_pts = 5;
	out->pts[0].x = (cosa * fx) - (sina * fy);
	out->pts[0].y = (sina * fx) + (cosa * fy);

	fx += 1.0;
	out->pts[1].x = (cosa * fx) - (sina * fy);
	out->pts[1].y = (sina * fx) + (cosa * fy);

	fy += 1.0;
	out->pts[2].x = (cosa * fx) - (sina * fy);
	out->pts[2].y = (sina * fx) + (cosa * fy);

	fx -= 1.0;
	out->pts[3].x = (cosa * fx) - (sina * fy);
	out->pts[3].y = (sina * fx) + (cosa * fy);

	out->pts[4].x = out->pts[0].x;
	out->pts[4].y = out->pts[0].y;

	out->xmin = out->pts[0].x;
	out->ymin = out->pts[0].y;
	out->xmax = out->pts[0].x;
	out->ymax = out->pts[0].y;

	for (i = 3; i > 0; i--)	// find bounding rect
	{
		if (out->pts[i].x < out->xmin)
			out->xmin = out->pts[i].x;

		if (out->pts[i].x > out->xmax)
			out->xmax = out->pts[i].x;

		if (out->pts[i].y < out->ymin)
			out->ymin = out->pts[i].y;

		if (out->pts[i].y > out->ymax)
			out->ymax = out->pts[i].y;
	}
}

//----------------------------------------------------------------------------------------
// Create a bounding polygon for a matrix entry. Matrix Entry x/y = ( 0 /0 ) means that the
// polygon will be ( -0.5/-0.5 ), ( 0.5/-0.5 ), ( 0.5/0.5 ), ( -0.5/0.5 ) and again ( -0.5/-0.5 )
// The polygon is counterclockwise.
// Function result:		-
// x:									x coordinate (relative to the matrix center)
// y:									y coordinate (relative to the matrix center)
// r:									rotation angle
// out:								used to return the polygon
//----------------------------------------------------------------------------------------
static void	matrix_entries_to_bounds(Int32 x1, Int32 y1, Int32 x2, Int32 y2, Float64 r, MBOUNDS* out)
{
	Float64	cosa;
	Float64	sina;
	Float64	fx1;
	Float64	fy1;
	Float64	fx2;
	Float64	fy2;
	Int32		i;

	fx1 = (Float64) x1 - 0.5;
	fy1 = (Float64) y1 - 0.5;
	fx2 = (Float64) x2 + 0.5;
	fy2 = (Float64) y2 + 0.5;

	cosa = Cos(r);
	sina = Sin(r);

	if ((sina == 1.0) || (sina == -1.0))	// this litte extra checking is necessary because Cos( PI05 ) is not zero!
		cosa = 0.0;

	if ((cosa == 1.0) || (cosa == -1.0))
		sina = 0.0;

	out->no_pts = 5;
	out->pts[0].x = (cosa * fx1) - (sina * fy1);
	out->pts[0].y = (sina * fx1) + (cosa * fy1);

	out->pts[1].x = (cosa * fx2) - (sina * fy1);
	out->pts[1].y = (sina * fx2) + (cosa * fy1);

	out->pts[2].x = (cosa * fx2) - (sina * fy2);
	out->pts[2].y = (sina * fx2) + (cosa * fy2);

	out->pts[3].x = (cosa * fx1) - (sina * fy2);
	out->pts[3].y = (sina * fx1) + (cosa * fy2);

	out->pts[4].x = out->pts[0].x;
	out->pts[4].y = out->pts[0].y;

	out->xmin = out->pts[0].x;
	out->ymin = out->pts[0].y;
	out->xmax = out->pts[0].x;
	out->ymax = out->pts[0].y;

	for (i = 3; i > 0; i--)	// find bounding rect
	{
		if (out->pts[i].x < out->xmin)
			out->xmin = out->pts[i].x;

		if (out->pts[i].x > out->xmax)
			out->xmax = out->pts[i].x;

		if (out->pts[i].y < out->ymin)
			out->ymin = out->pts[i].y;

		if (out->pts[i].y > out->ymax)
			out->ymax = out->pts[i].y;
	}
}

static Float64 get_intersection_area(MBOUNDS* src_me, MBOUNDS* dst_me)
{
	Float64	area;
	MBOUNDS	sect_me;

	area = 0;

	if (sect_polygons(src_me, dst_me, &sect_me))
		area = get_simple_polygon_area(&sect_me);

	if (area > 1.0)
		area = 1.0;

	return area;
}

static Bool	sect_polygons(MBOUNDS* src_me, MBOUNDS* dst_me, MBOUNDS* sect_me)
{
	Int32	 i;
	Int32	 j;
	Int32	 k;
	MPOINT tmp;
	Bool	 add_pt;

	sect_me->no_pts = 0;

	for (i = 0; i < dst_me->no_pts - 1; i++)	// intersect all source and destination lines and put the intersection points into sect_me
	{
		Int32	fi;

		fi	= sect_me->no_pts;
		tmp = dst_me->pts[i];

		if (test_inside(src_me->pts, src_me->no_pts - 1, &tmp))	// is a vertex of dst inside src?
		{
			add_pt = true;
			for (k = 0; k < sect_me->no_pts; k++)	// check if this point is already present
			{
				if ((sect_me->pts[k].x == tmp.x) && (sect_me->pts[k].y == tmp.y))
				{
					add_pt = false;
					break;
				}
			}
			if (add_pt)
			{
				sect_me->pts[sect_me->no_pts] = tmp;
				sect_me->no_pts++;
			}
		}

		for (j = 0; j < src_me->no_pts - 1; j++)
		{
			tmp = src_me->pts[i];

			if (test_inside(dst_me->pts, dst_me->no_pts - 1, &tmp))	// is a vertex of src inside dst?
			{
				add_pt = true;
				for (k = 0; k < sect_me->no_pts; k++)	// check if this point is already present
				{
					if ((sect_me->pts[k].x == tmp.x) && (sect_me->pts[k].y == tmp.y))
					{
						add_pt = false;
						break;
					}
				}
				if (add_pt)
				{
					sect_me->pts[sect_me->no_pts] = tmp;
					sect_me->no_pts++;
				}
			}

			if (sect_lines(src_me->pts + j, dst_me->pts + i, &tmp))
			{
				add_pt = true;
				for (k = 0; k < sect_me->no_pts; k++)	// check if this point is already present
				{
					if ((sect_me->pts[k].x == tmp.x) && (sect_me->pts[k].y == tmp.y))
					{
						add_pt = false;
						break;
					}
				}
				if (add_pt)
				{
					sect_me->pts[sect_me->no_pts] = tmp;
					sect_me->no_pts++;
				}
			}
		}

		{
			Int32	x_dir;
			Int32	y_dir;
			Int32	cnt;

			if (dst_me->pts[i].x <= dst_me->pts[i + 1].x)
				x_dir = 1;
			else
				x_dir = -1;

			if (dst_me->pts[i].y <= dst_me->pts[i + 1].y)
				y_dir = 1;
			else
				y_dir = -1;

			cnt = sect_me->no_pts - fi;
			if (cnt > 1)
			{
				MPOINT* p;
				MPOINT	s;

				p = sect_me->pts + fi;

				for (j = cnt - 1; j > 0; j--)
				{
					for (k = 0; k < j; k++)
					{
						s = p[k];

						if (x_dir > 0)
						{
							if (p[k].x > p[k + 1].x)
							{
								p[k] = p[k + 1];
								p[k + 1] = s;
							}
							else if (p[k].x == p[k + 1].x)
							{
								if (y_dir > 0)
								{
									if (p[k].y > p[k + 1].y)
									{
										p[k] = p[k + 1];
										p[k + 1] = s;
									}
								}
								else
								{
									if (p[k].y < p[k + 1].y)
									{
										p[k] = p[k + 1];
										p[k + 1] = s;
									}
								}
							}
						}
						else
						{
							if (p[k].x < p[k + 1].x)
							{
								p[k] = p[k + 1];
								p[k + 1] = s;
							}
							else if (p[k].x == p[k + 1].x)
							{
								if (y_dir > 0)
								{
									if (p[k].y > p[k + 1].y)
									{
										p[k] = p[k + 1];
										p[k + 1] = s;
									}
								}
								else
								{
									if (p[k].y < p[k + 1].y)
									{
										p[k] = p[k + 1];
										p[k + 1] = s;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (sect_me->no_pts)
	{
		sect_me->xmin = sect_me->pts[0].x;
		sect_me->ymin = sect_me->pts[0].y;
		sect_me->xmax = sect_me->pts[0].x;
		sect_me->ymax = sect_me->pts[0].y;

		for (i = sect_me->no_pts - 1; i > 0; i--)	// find bounding rect
		{
			if (sect_me->pts[i].x < sect_me->xmin)
				sect_me->xmin = sect_me->pts[i].x;

			if (sect_me->pts[i].x > sect_me->xmax)
				sect_me->xmax = sect_me->pts[i].x;

			if (sect_me->pts[i].y < sect_me->ymin)
				sect_me->ymin = sect_me->pts[i].y;

			if (sect_me->pts[i].y > sect_me->ymax)
				sect_me->ymax = sect_me->pts[i].y;
		}

		sect_me->pts[sect_me->no_pts] = sect_me->pts[0];	// close polygon
		sect_me->no_pts++;

		return true;
	}

	return false;
}

static Bool	sect_lines(MPOINT* line_a, MPOINT* line_b, MPOINT* sect)
{
	if ((line_a[0].x == line_b[0].x) && (line_a[0].y == line_b[0].y))
	{
		*sect = line_a[0];
		return true;
	}

	if (intersect_lines(line_a, line_b, sect) == 1)
		return true;

	return false;
}

//----------------------------------------------------------------------------------------
// Check wheter two lines intersect (or a colinear)
// Function result:		0: no intersection 1: intersection 2: colinear (no or all points intersect)
// s1:								points of the first line
// s2:								points of the second line
// out:								if there's an intersection, the point is returned here
//----------------------------------------------------------------------------------------
static Int32 intersect_lines(MPOINT* s1, MPOINT* s2, MPOINT* out)
{
#define SAME_SIGNS(a, b)		(a < 0 ? (b < 0 ? 1 : 0) : (b < 0 ? 0 : 1))
#define	maxmin(x1, x2, min) (x1 >= x2 ? (min = x2, x1) : (min = x1, x2))

	Float64	a, b, c, d, tdet, sdet, det;
	Float64	max1, max2, min1, min2;
	MPOINT	p1, p2, q1, q2;
	Float64	s;

	p1 = s1[0];
	p2 = s1[1];
	q1 = s2[0];
	q2 = s2[1];

	// First make the bounding box test.

	max1 = maxmin(p1.x, p2.x, min1);
	max2 = maxmin(q1.x, q2.x, min2);
	if ((max1 < min2) || (min1 > max2))
		return 0;		// no intersection

	max1 = maxmin(p1.y, p2.y, min1);
	max2 = maxmin(q1.y, q2.y, min2);
	if ((max1 < min2) || (min1 > max2))
		return 0;		// no intersection

	// See if the endpoints of the second segment lie on the opposite sides of the first.	If not, return 0.

	a = ((q1.x - p1.x) * (p2.y - p1.y)) - ((q1.y - p1.y) * (p2.x - p1.x));
	b = ((q2.x - p1.x) * (p2.y - p1.y)) - ((q2.y - p1.y) * (p2.x - p1.x));
	if ((a != 0) && (b != 0) && SAME_SIGNS(a, b))
		return 0;

	// See if the endpoints of the first segment lie on the opposite sides of the second.	If not, return 0.
	c = ((p1.x - q1.x) * (q2.y - q1.y)) - ((p1.y - q1.y) * (q2.x - q1.x));
	d = ((p2.x - q1.x) * (q2.y - q1.y)) - ((p2.y - q1.y) * (q2.x - q1.x));
	if ((c != 0) && (d != 0) && SAME_SIGNS(c, d))
		return 0;

	// At this point each segment meets the line of the other.
	det = a - b;
	if (det == 0)	// are the lines colinear?
		return 2;

	// The segments intersect since each segment crosses the other's line;
	// however, since the lines are not parallel, either a or b is not
	// zero.	Similarly either c or d is not zero.

	tdet = -c;
	sdet = a;
	if (det < 0)	// The denominator of the parameter must be positive.
	{
		det	 = -det;
		sdet = -sdet;
		tdet = -tdet;
	}

	s = sdet / det;

	out->x = (q2.x - q1.x) * s + q1.x;
	out->y = (q2.y - q1.y) * s + q1.y;
	return 1;

	#undef	SAME_SIGN
	#undef	maxmin
}

//----------------------------------------------------------------------------------------
// Check wheter a point is inside a convex polygon (GGIV 1.4 Crossings)
// Shoot a test ray along +X axis.  The strategy, from MacMartin, is to
// compare vertex Y values to the testing point's Y and quickly discard
// edges which are entirely to one side of the test ray.
// Function result:		true: inside false: outside
// pts:								points of the polygon
// no_pts:						number of points in the polygon (polygon is not closed)
// check_point:				the test point
//----------------------------------------------------------------------------------------
static Bool	test_inside(MPOINT* pts, Int32 no_pts, MPOINT* check_point)
{
	Bool		inside_flag;
	Bool		line_flag;
	Int32		i, yflag0, yflag1, xflag0;
	Float64 ty;
	Float64	tx;
	MPOINT* vtx0;
	MPOINT* vtx1;

	tx = check_point->x;
	ty = check_point->y;

	vtx0 = pts + no_pts - 1;
	yflag0 = (vtx0->y >= ty);	// get test bit for above/below X axis
	vtx1 = pts;

	inside_flag = false;
	line_flag = false;

	for (i = no_pts + 1; --i; )
	{
		yflag1 = (vtx1->y >= ty);

		// check if endpoints straddle (are on opposite sides) of X axis
		// (i.e. the Y's differ); if so, +X ray could intersect this edge.

		if (yflag0 != yflag1)
		{
			xflag0 = (vtx0->x >= tx);
			// check if endpoints are on same side of the Y axis (i.e. X's
			// are the same); if so, it's easy to test if edge hits or misses.

			if (xflag0 == (vtx1->x >= tx))
			{
				if (xflag0)	// if edge's X values both right of the point, must hit
					inside_flag = !inside_flag;
			}
			else
			{
				// compute intersection of pts segment with +X ray, note if >= point's X; if so, the ray hits it.
				if ((vtx1->x - (vtx1->y - ty) * (vtx0->x - vtx1->x) / (vtx0->y - vtx1->y)) >= tx)
				{
					inside_flag = !inside_flag;
				}
			}

			if (line_flag)	// if this is second edge hit, that's it (convex polygon)
				break;

			line_flag = true;	// note that one edge has been hit by the ray's line
		}

		yflag0 = yflag1;	// move to next pair of vertices, retaining info as possible
		vtx0 = vtx1;
		vtx1++;
	}

	return inside_flag;
}

//----------------------------------------------------------------------------------------
// Calculate the area of a polygon (GGII 1.1). Point order should be counterclockwise.
// Function result:		Area
// me:								polygon
//----------------------------------------------------------------------------------------
static Float64 get_simple_polygon_area(MBOUNDS* me)
{
	Int32		i;
	Float64	area;

	area = 0;
	for (i = 1; i < me->no_pts; i++)
	{
		area += (me->pts[i - 1].x) * (me->pts[i].y);
		area -= (me->pts[i].x) * (me->pts[i - 1].y);
	}

	area /= 2;

	if (area < 0)	// wrong point order?
		area = -area;

	return area;
}
