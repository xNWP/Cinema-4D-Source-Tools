#ifdef __API_INTERN__
	#error "Not in kernel"
#endif

#include "c4d_library.h"
#include "lib_big_integer.h"

BigIntegerLib* lib_big_integer = nullptr;

static BigIntegerLib *CheckLibAES(Int32 offset)
{
	return (BigIntegerLib*)CheckLib(BIG_INTEGER_LIB, offset, (C4DLibrary**)&lib_big_integer);
}

#define BigIntegerLibCall(b) 		BigIntegerLib *lib = CheckLibAES(LIBOFFSET(BigIntegerLib, b)); \
	if (!lib || !lib->b) return; \
	(((iBigInteger*)this)->*lib->b)

#define BigIntegerLibCallR(a, b)  BigIntegerLib *lib = CheckLibAES(LIBOFFSET(BigIntegerLib, b)); \
	if (!lib || !lib->b) return a; \
	return (((iBigInteger*)this)->*lib->b)

BigInteger* BigInteger::Alloc()
{
	BigIntegerLib *lib = CheckLibAES(LIBOFFSET(BigIntegerLib, BigInteger_Alloc)); if (!lib) return nullptr;
	return lib->BigInteger_Alloc();
}

void BigInteger::Free(BigInteger *&p)
{
	if (!p) return;
	BigIntegerLib *lib = CheckLibAES(LIBOFFSET(BigIntegerLib, BigInteger_Free)); if (!lib) return;
	lib->BigInteger_Free(p);
	p = nullptr;
}

Bool BigInteger::Set(maxon::Char c)
{
	BigIntegerLibCallR(false, Set1)(c);
}

Bool BigInteger::Set(maxon::UChar c)
{
	BigIntegerLibCallR(false, Set2)(c);
}

Bool BigInteger::Set(maxon::Int16 i)
{
	BigIntegerLibCallR(false, Set3)(i);
}

Bool BigInteger::Set(maxon::UInt16 u)
{
	BigIntegerLibCallR(false, Set4)(u);
}

Bool BigInteger::Set(maxon::Int32 i)
{
	BigIntegerLibCallR(false, Set5)(i);
}

Bool BigInteger::Set(maxon::UInt32 u)
{
	BigIntegerLibCallR(false, Set6)(u);
}

Bool BigInteger::Set(maxon::Int64 i)
{
	BigIntegerLibCallR(false, Set7)(i);
}

Bool BigInteger::Set(maxon::UInt64 u)
{
	BigIntegerLibCallR(false, Set8)(u);
}

Bool BigInteger::SetRandom(maxon::Int bitCount, SecureRandomProvider provider)
{
	BigIntegerLibCallR(false, SetRandom)(bitCount, provider);
}

Bool BigInteger::SetRandomPrime(maxon::Int bitCount, maxon::UInt certainty, SecureRandomProvider provider)
{
	BigIntegerLibCallR(false, SetRandomPrime)(bitCount, certainty, provider);
}

Bool BigInteger::IsEven() const
{
	BigIntegerLibCallR(false, IsEven)();
}

Bool BigInteger::IsOdd() const
{
	BigIntegerLibCallR(false, IsOdd)();
}

Bool BigInteger::IsOne() const
{
	BigIntegerLibCallR(false, IsOne)();
}

Bool BigInteger::IsZero() const
{
	BigIntegerLibCallR(false, IsZero)();
}

Bool BigInteger::IsNegative() const
{
	BigIntegerLibCallR(false, IsNegative)();
}

Bool BigInteger::IsPowerOfTwo() const
{
	BigIntegerLibCallR(false, IsPowerOfTwo)();
}

Bool BigInteger::IsProbablyPrime(maxon::UInt certainty) const
{
	BigIntegerLibCallR(false, IsProbablyPrime)(certainty);
}

maxon::Int BigInteger::Sign() const
{
	BigIntegerLibCallR(0, Sign)();
}

maxon::Int BigInteger::GetHighestNonSignBit() const
{
	BigIntegerLibCallR(0, GetHighestNonSignBit)();
}

maxon::Int BigInteger::GetLowestSetBit() const
{
	BigIntegerLibCallR(0, GetLowestSetBit)();
}

maxon::Int BigInteger::GetLowestClearedBit() const
{
	BigIntegerLibCallR(0, GetLowestClearedBit)();
}

Bool BigInteger::IsBitSet(maxon::Int bit) const
{
	BigIntegerLibCallR(false, IsBitSet)(bit);
}

maxon::UChar BigInteger::GetLowestBits8U() const
{
	BigIntegerLibCallR(0, GetLowestBits8U)();
}

maxon::Char BigInteger::GetLowestBits8S() const
{
	BigIntegerLibCallR(0, GetLowestBits8S)();
}

maxon::UInt32 BigInteger::GetLowestBits32U() const
{
	BigIntegerLibCallR(0, GetLowestBits32U)();
}

maxon::Int32 BigInteger::GetLowestBits32S() const
{
	BigIntegerLibCallR(0, GetLowestBits32S)();
}

maxon::UInt64 BigInteger::GetLowestBits64U() const
{
	BigIntegerLibCallR(0, GetLowestBits64U)();
}

maxon::Int64 BigInteger::GetLowestBits64S() const
{
	BigIntegerLibCallR(0, GetLowestBits64S)();
}

Bool BigInteger::GetDataCopy(maxon::BaseArray<maxon::UChar>& data) const
{
	BigIntegerLibCallR(false, GetDataCopy)(data);
}

void BigInteger::Add(const BigInteger* b)
{
	BigIntegerLibCall(Add)(b);
}

void BigInteger::Sub(const BigInteger* b)
{
	BigIntegerLibCall(Sub)(b);
}

void BigInteger::Inc()
{
	BigIntegerLibCall(Inc)();
}

void BigInteger::Dec()
{
	BigIntegerLibCall(Dec)();
}

void BigInteger::Mul(const BigInteger* b)
{
	BigIntegerLibCall(Mul)(b);
}

void BigInteger::Div(const BigInteger* b)
{
	BigIntegerLibCall(Div)(b);
}

void BigInteger::Mod(const BigInteger* b)
{
	BigIntegerLibCall(Mod)(b);
}

void BigInteger::DivMod(const BigInteger* b, BigInteger* r)
{
	BigIntegerLibCall(DivMod)(b, r);
}

void BigInteger::Pow(const BigInteger* b)
{
	BigIntegerLibCall(Pow)(b);
}

void BigInteger::PowMod(const BigInteger* b, const BigInteger* mod)
{
	BigIntegerLibCall(PowMod)(b, mod);
}

void BigInteger::GreatestCommonDivisor(const BigInteger* b)
{
	BigIntegerLibCall(GreatestCommonDivisor)(b);
}

Bool BigInteger::MultiplicativeInverse(const BigInteger* m)
{
	BigIntegerLibCallR(false, MultiplicativeInverse)(m);
}

void BigInteger::LeftShift(maxon::Int s)
{
	BigIntegerLibCall(LeftShift)(s);
}

void BigInteger::RightShift(maxon::Int s)
{
	BigIntegerLibCall(RightShift)(s);
}

void BigInteger::Negate()
{
	BigIntegerLibCall(Negate)();
}

void BigInteger::SetBit(maxon::Int bit)
{
	BigIntegerLibCall(SetBit)(bit);
}

void BigInteger::ClearBit(maxon::Int bit)
{
	BigIntegerLibCall(ClearBit)(bit);
}

void BigInteger::ToggleBit(maxon::Int bit)
{
	BigIntegerLibCall(ToggleBit)(bit);
}

maxon::COMPARERESULT BigInteger::Compare(const BigInteger* arg2) const
{
#ifdef USE_API_MAXON
	BigIntegerLibCallR(maxon::COMPARERESULT::EQUAL, Compare)(arg2);
#else
	BigIntegerLibCallR(maxon::COMPARERESULT_EQUAL, Compare)(arg2);
#endif
}

Bool BigInteger::CopyFrom(const BigInteger* src)
{
	BigIntegerLibCallR(false, CopyFrom)(src);
}
