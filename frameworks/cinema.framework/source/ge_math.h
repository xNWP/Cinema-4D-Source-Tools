/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef GE_MATH_H__
#define GE_MATH_H__

#include "ge_sys_math.h"

#ifndef GCC34T
	#define GCC34T
#endif

typedef UChar PIX;					///< 8-bit integer pixel type.
typedef UChar PIX_C;				///< 8-bit integer pixel type.
typedef UInt16 PIX_W;				///< 16-bit integer pixel type.
typedef Float32 PIX_F;			///< 32-bit float pixel type.

/// @addtogroup group_comparecheckrepair_float Compare/Check/Repair Float
/// @ingroup group_function
/// @{

//----------------------------------------------------------------------------------------
/// Checks if two floats are close to each other on a bit basis (rather than a fixed epsilon).\n
/// Single precision version.
/// @param[in] a									A float value.
/// @param[in] b									A float value.
/// @return												@trueIfOtherwiseFalse{a and b are sufficiently close to each other}
//----------------------------------------------------------------------------------------
Bool CompareFloatTolerant(Float32 a, Float32 b);

//----------------------------------------------------------------------------------------
/// Checks if two floats are close to each other on a bit basis (rather than a fixed epsilon).\n
/// Double precision version.
/// @param[in] a									A float value.
/// @param[in] b									A float value.
/// @return												@trueIfOtherwiseFalse{a and b are sufficiently close to each other}
//----------------------------------------------------------------------------------------
Bool CompareFloatTolerant(Float64 a, Float64 b);

//----------------------------------------------------------------------------------------
/// Checks if @formatParam{r} is a valid floating point number.\n
/// Single precision version.
/// @param[in] r									The value to check.
/// @return												@trueIfOtherwiseFalse{@formatParam{r} is a valid floating point number}\n
///																@formatConstant{true} for @em FP_NORMAL, @em FP_SUBNORMAL and @em FP_ZERO.\n
///																@formatConstant{false} for @em FP_NAN, @em FP_INFINITE.
//----------------------------------------------------------------------------------------
inline Bool CheckFloat(Float32 r)
{
	union { Float32 f; UInt32 u; } u = { r };

	return ((u.u >> 23) & 0xff) != 0xff;
}

//----------------------------------------------------------------------------------------
/// Checks if @formatParam{r} is a valid floating point number.\n
/// Double precision version.
/// @param[in] r									The value to check.
/// @return												@trueIfOtherwiseFalse{@formatParam{r} is a valid floating point number}\n
///																@formatConstant{true} for @em FP_NORMAL, @em FP_SUBNORMAL and @em FP_ZERO.\n
///																@formatConstant{false} for @em FP_NAN, @em FP_INFINITE.
//----------------------------------------------------------------------------------------
inline Bool CheckFloat(Float64 r)
{
	union { Float64 f; UInt64 u; } u = { r };

	return ((~u.u >> 52) & 0x7ff) != 0;
}

//----------------------------------------------------------------------------------------
/// Repairs floating point values.\n
/// Single precision version.
/// @warning Only NaN and Infinity are corrected. Denormalized numbers are not.
/// @note Useful when importing other formats where the floating point data is not always valid.
/// @param[in] r									The float value to repair.
/// @return												The repaired value.
//----------------------------------------------------------------------------------------
inline Float32 RepairFloat(Float32 r)
{
	if (!CheckFloat(r))
		return 0.0;

	return r;
}

//----------------------------------------------------------------------------------------
/// Repairs floating point values.\n
/// Double precision version.
/// @warning Only NaNs and Infinity are corrected. Denormalized numbers are not.
/// @note Useful when importing other formats where the floating point data is not always valid.
/// @param[in] r									The float value to repair.
/// @return												The repaired value.
//----------------------------------------------------------------------------------------
inline Float64 RepairFloat(Float64 r)
{
	if (!CheckFloat(r))
		return 0.0;

	return r;
}

//----------------------------------------------------------------------------------------
/// Converts a 16 bit half precision float value into a 32 bit float.
/// @note The input value must be a IEEE 754r half precision bit pattern.
/// @param[in] val								The half precision float to convert.
/// @return												The converted 32 bit float value.
//----------------------------------------------------------------------------------------
inline Float32 Float16ToFloat32(const UInt16 val)
{
	Float32 res = 0.0;

	UInt32 t1 = val & 0x7fff;	// All bits without sign bit
	UInt32 t2 = val & 0x8000;	// Sign bit only
	UInt32 t3 = val & 0x7c00;	// Exponent

	t1 <<= 13;								// Align mantissa on MSB
	t2 <<= 16;								// Shift sign bit into 32 bit position

	t1 += 0x38000000;					// Adjust the bias
	t1	= (t3 == 0 ? 0 : t1);	// Set bits to zero if exponent is zero
	t1 |= t2;									// Insert sign bit back

	*((UInt32*)&res) = t1;		// Copy the data into the 32 bit float

	return res;
};

//----------------------------------------------------------------------------------------
/// Converts a 32 bit float value into a 16 bit half precision float.
/// @note The return value will be a IEEE 754r half precision bit pattern.
/// @param[in] val								The 32 bit float value to convert.
/// @return												The converted half precision float value.
//----------------------------------------------------------------------------------------
inline UInt16 Float32ToFloat16(const Float32 val)
{
	UInt16 res = 0;

	UInt32 inu = *((UInt32*)&val);				// Convert into a 32 bit unsigned integer buffer

	UInt32 t1 = inu & 0x7fffffff;					// All bits without sign bit
	UInt32 t2 = inu & 0x80000000;					// Sign bit only
	UInt32 t3 = inu & 0x7f800000;					// Exponent

	t1 >>= 13;														// Align mantissa on MSB
	t2 >>= 16;														// Shift sign bit into position

	t1 -= 0x1c000;												// Adjust the bias

	t1 = (t3 < 0x38800000) ? 0 : t1;			// Flush to zero
	t1 = (t3 > 0x8e000000) ? 0x7bff : t1;	// Clamp to max

	t1 |= t2;															// Insert sign bit back

	res = (UInt16)t1;											// Copy the pattern in a 16 bit unsigned int buffer

	return res;
};

/// @}

#define C4D_FOUR_BYTE(x1, x2, x3, x4)			((x1 << 24) | (x2 << 16) | (x3 << 8) | x4)
#define C4D_RESERVE_PRIVATE_TYPE(type, x)	type x

#ifndef USE_API_MAXON
struct Vector64;
struct Matrix64;
struct Vector32;
struct Matrix32;
#endif

enum _DONTCONSTRUCT
{
	DC			///< Pass this to invoke the no-op constructor.
};

enum _EMPTYCONSTRUCT
{
	EC			///< Pass this to invoke the no-op empty constructor.
};

#ifndef USE_API_MAXON
/// @cond IGNORE

// Necessary to import in exactly this order
#include "ge_vector.h"
#include "ge_lvector.h"
#include "ge_matrix.h"
#include "ge_lmatrix.h"

/// @endcond

#ifdef MAXON_TARGET_SINGLEPRECISION
typedef Vector32 Vector;
typedef Matrix32 Matrix;
#else
typedef Vector64 Vector;
typedef Matrix64 Matrix;
#endif

struct Matrix32;
struct Vector32;
struct Matrix64;
struct Vector64;
#else

#include "maxon/vector.h"
#include "maxon/vector2d.h"

static const maxon::ENUM_DONT_INITIALIZE DONT_INITIALIZE = maxon::ENUM_DONT_INITIALIZE::VALUE;

/// Single-Precision Vector.
/// A vector contains three components X, Y and Z
typedef maxon::Vec3<maxon::Float32, 1> Vector32;

/// Double-Precision Vector.
/// A vector contains three components X, Y and Z
typedef maxon::Vec3<maxon::Float64, 1> Vector64;

typedef maxon::Vec3<maxon::Float64, 1> Vector;

typedef maxon::Vec2<maxon::Float64, 1> Vector2d;

typedef maxon::Vec2<maxon::Float64, 1> Vector2d64;

#include "maxon/matrix.h"

// Necessary to import in exactly this order

/// @endcond

typedef maxon::Mat3<maxon::Vector64> Matrix64;

typedef maxon::Mat3<maxon::Vector32> Matrix32;

typedef maxon::Mat3<maxon::Vector64> Matrix;

#endif

namespace maxon
{
class String;
class Url;
class FormatStatement;
}

maxon::String ToString(const Matrix32& val, const maxon::FormatStatement* formatStatement, maxon::Bool checkDatatype = false);
maxon::String ToString(const Vector32& val, const maxon::FormatStatement* formatStatement, maxon::Bool checkDatatype = false);
maxon::String ToString(const Matrix64& val, const maxon::FormatStatement* formatStatement, maxon::Bool checkDatatype = false);
maxon::String ToString(const Vector64& val, const maxon::FormatStatement* formatStatement, maxon::Bool checkDatatype = false);

#endif // GE_MATH_H__
