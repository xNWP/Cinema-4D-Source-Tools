#include "ge_math.h"

// Bug #6516
// Due to a bug in the gcc compiler when compiling release code and using the Relax IEEE option and fast code optimization,
// the recognition of NaN and INF doesn't work (should be fixed in gcc 4.2 - to be tested).
// Attention: isnan/infinite is only replaced in the context of this source file (when using gcc)!
//
// IDEA #31877: NaN and INF Bug is fixed in gcc 4.2 and therefore the workaround is only applied to older gcc 4.x versions
#if ((__GNUC__ == 4) && (__GNUC_MINOR__ < 2))
#undef	isnan
#undef	isinfinite

Bool isnan(Float32 f)
{
	UInt32 exp, mant;

	mant	= exp = *((UInt32*)&f);
	exp	 &= 0x7f800000L;							// ieee 754 float has 1 sign bit + 8 bits for exponent
	mant &= 0x007fffffL;							// and 23 bits for the mantissa;
	if ((exp == 0x7f800000L) && mant)	// NaN?: all exponent bits set (sign doesn't matter) + mant != 0
		return true;
	else
		return false;
}

Bool isnan(Float64 d)
{
	UInt64 exp, mant;

	mant	= exp = *((UInt64*)&d);
	exp	 &= 0x7ff0000000000000LL;								// ieee 754 double has 1 sign bit + 11 bits for exponent
	mant &= 0x000fffffffffffffLL;								// and 52 bits for the mantissa;

	if ((exp == 0x7ff0000000000000LL) && mant)	// NaN?: all exponent bits set (sign doesn't matter) + mant != 0
		return true;
	else
		return false;
}


Bool isinfinite(Float32 f)
{
	UInt32 exp, mant;

	mant	= exp = *((UInt32*)&f);
	exp	 &= 0x7f800000L;											// ieee 754 float has 1 sign bit + 8 bits for exponent
	mant &= 0x007fffffL;											// and 23 bits for the mantissa;

	if ((exp == 0x7f800000L) && (mant == 0))	// INF?: all exponent bits set (sign doesn't matter) + mant == 0
		return true;
	else
		return false;
}

Bool isinfinite(Float64 d)
{
	UInt64 exp, mant;

	mant	= exp = *((UInt64*)&d);
	exp	 &= 0x7ff0000000000000LL;											// ieee 754 double has 1 sign bit + 11 bits for exponent
	mant &= 0x000fffffffffffffLL;											// and 52 bits for the mantissa;

	if ((exp == 0x7ff0000000000000LL) && (mant == 0))	// INF?: all exponent bits set (sign doesn't matter) + mant == 0
		return true;
	else
		return false;
}
#endif	// __GNUC__

#if defined MAXON_TARGET_WINDOWS || defined MAXON_TARGET_LINUX
	#include "float.h"
#else
	#include "ge_math.h"
#endif

Bool CompareFloatTolerant(Float32 a, Float32 b)
{
	Int32* va = (Int32*) &a;
	Int32* vb = (Int32*) &b;

	// UInt32 is necessary because -x-x is 0x80000000 where abs(0x80000000 is illegal)
	return UInt32(Abs(*va - *vb)) <= 7;
}

Bool CompareFloatTolerant(Float64 a, Float64 b)
{
	Int64* va = (Int64*) &a;
	Int64* vb = (Int64*) &b;

	// UInt32 is necessary because -x-x is 0x80000000 where abs(0x80000000 is illegal)
	return UInt64(Abs(*va - *vb)) <= 7;
}
