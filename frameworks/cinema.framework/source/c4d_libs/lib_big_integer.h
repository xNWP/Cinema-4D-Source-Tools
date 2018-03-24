#ifndef LIB_BIG_INTEGER_H__
#define LIB_BIG_INTEGER_H__

#include "c4d_library.h"
#include "lib_secure_random.h"
#include "c4d_misc.h"

#ifdef __API_INTERN__
#include "c4d_library.h"
#include "intbaselist.h"
#endif

#undef Mod

/// @addtogroup group_bigintegerlibrary Big Integer
/// @ingroup group_library
/// @{

/// BigInteger library ID.
#define BIG_INTEGER_LIB			450000264

//----------------------------------------------------------------------------------------
/// Class to manipulate big integer values.
/// @addAllocFreeAutoAllocNote
//----------------------------------------------------------------------------------------
class BigInteger
{
private:
	BigInteger();
	~BigInteger();

public:

	/// @name Alloc/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// @allocatesA{big integer}
	/// @return												@allocReturn{big integer}
	//----------------------------------------------------------------------------------------
	static BigInteger* Alloc();

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{big integers}
	/// @param[in,out] p							@theToDestruct{big integer}
	//----------------------------------------------------------------------------------------
	static void Free(BigInteger *&p);

	/// @}

	/// @name Set Value
	/// @{

	//----------------------------------------------------------------------------------------
	/// Sets the value of the BigInteger.
	/// @param[in] c									The new value.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::Char c);

	//----------------------------------------------------------------------------------------
	/// Sets the value of the BigInteger.
	/// @param[in] c									The new value.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::UChar c);

	//----------------------------------------------------------------------------------------
	/// Sets the value of the BigInteger.
	/// @param[in] i									The new value.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::Int16 i);

	//----------------------------------------------------------------------------------------
	/// Sets the value of the BigInteger.
	/// @param[in] u									The new value.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::UInt16 u);

	//----------------------------------------------------------------------------------------
	/// Sets the value of the BigInteger.
	/// @param[in] i									The new value.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::Int32 i);

	//----------------------------------------------------------------------------------------
	/// Sets the value of the BigInteger.
	/// @param[in] u									The new value.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::UInt32 u);

	//----------------------------------------------------------------------------------------
	/// Sets the value of the BigInteger.
	/// @param[in] i									The new value.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::Int64 i);

	//----------------------------------------------------------------------------------------
	/// Sets the value of the BigInteger.
	/// @param[in] u									The new value.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::UInt64 u);

	/// @}

	/// @name Set Random
	/// @{

	//----------------------------------------------------------------------------------------
	/// Assigns a random value to the BigInteger. The number is always positive.
	/// @param[in] bitCount						The number of bits to set, must be greater than @em 0.
	/// @param[in] provider						A secure random provider that can be used with SecureRandom. If @formatConstant{nullptr} is passed an insecure default provider is chosen.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetRandom(maxon::Int bitCount, SecureRandomProvider provider = nullptr);

	//----------------------------------------------------------------------------------------
	/// Assigns a random prime number value to the BigInteger. The number is always positive, odd and the (@formatParam{bitCount} - @em 1) bit will be set.
	/// @param[in] bitCount						The number of bits to set, must be greater than @em 1.
	/// @param[in] certainty					The generated number is a prime number with a probability of @em 1 - @em 0.5 * @formatParam{certainty}. Must be greater than @em 0.\n
	///																The execution time of the function raises with the @formatParam{certainty}.
	/// @param[in] provider						A secure random provider that can be used with SecureRandom. If @formatConstant{nullptr} is passed an insecure default provider is chosen.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetRandomPrime(maxon::Int bitCount, maxon::UInt certainty, SecureRandomProvider provider = nullptr);

	/// @}

	/// @name Is Even/Odd/One/Zero/Negative/PowerOfTwo/ProbablyPrime
	/// @{

	//----------------------------------------------------------------------------------------
	/// Checks if the value is even.
	/// @return												@trueIfOtherwiseFalse{the value is even}
	//----------------------------------------------------------------------------------------
	Bool IsEven() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is odd.
	/// @return												@trueIfOtherwiseFalse{the value is odd}
	//----------------------------------------------------------------------------------------
	Bool IsOdd() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is one.
	/// @return												@trueIfOtherwiseFalse{the value is one}
	//----------------------------------------------------------------------------------------
	Bool IsOne() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is zero.
	/// @return												@trueIfOtherwiseFalse{the value is zero}
	//----------------------------------------------------------------------------------------
	Bool IsZero() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is negative.
	/// @return												@trueIfOtherwiseFalse{the value is negative}
	//----------------------------------------------------------------------------------------
	Bool IsNegative() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is a power of @em 2.
	/// @return												@trueIfOtherwiseFalse{the value is a power of @em 2}
	//----------------------------------------------------------------------------------------
	Bool IsPowerOfTwo() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is probably prime. The result will be @formatConstant{false} if it is smaller than @em 1.
	/// @param[in] certainty					The generated number is a prime number with a probability of @em 1 - @em 0.5 * @formatParam{certainty}. Must be greater than @em 0.
	/// @return												@trueIfOtherwiseFalse{the value is greater than @em 0 and prime with a probability of @em 1 - @em 0.5 * @formatParam{certainty}}.
	//----------------------------------------------------------------------------------------
	Bool IsProbablyPrime(maxon::UInt certainty) const;

	/// @}

	/// @name Sign
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the sign.
	/// @return												@em -1 if the number is negative, @em 0 if it is zero, @em 1 if it is positive.
	//----------------------------------------------------------------------------------------
	maxon::Int Sign() const;

	//----------------------------------------------------------------------------------------
	/// Gets the highest bit position that is different than the sign bit. This is the position incremented by one for negative numbers.
	/// @return												The bit position. The return value is @em -1 if the number is @em 0.
	//----------------------------------------------------------------------------------------
	maxon::Int GetHighestNonSignBit() const;

	/// @}

	/// @name Bit
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the lowest bit position that is zero.
	/// @return												The bit position. The return value is @em -1 if the number is zero.
	//----------------------------------------------------------------------------------------
	maxon::Int GetLowestSetBit() const;

	//----------------------------------------------------------------------------------------
	/// Gets the lowest bit position that is zero.
	/// @return												The bit position. The return value is @em -1 if the number is @em -1.
	//----------------------------------------------------------------------------------------
	maxon::Int GetLowestClearedBit() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the bit at a certain position is set.
	/// @param[in] bit								The bit to check.
	/// @return												@trueIfOtherwiseFalse{the @formatParam{bit} is set}
	//----------------------------------------------------------------------------------------
	Bool IsBitSet(maxon::Int bit) const;

	//----------------------------------------------------------------------------------------
	/// Sets a bit in the integer.
	/// @param[in] bit								The position of the bit to set.
	//----------------------------------------------------------------------------------------
	void SetBit(maxon::Int bit);

	//----------------------------------------------------------------------------------------
	/// Clears a bit in the integer.
	/// @param[in] bit								The position of the bit to clear.
	//----------------------------------------------------------------------------------------
	void ClearBit(maxon::Int bit);

	//----------------------------------------------------------------------------------------
	/// Toggles a bit in the integer.
	/// @param[in] bit								The position of the bit to toggle.
	//----------------------------------------------------------------------------------------
	void ToggleBit(maxon::Int bit);

	/// @}

	/// @name Bits
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the lowest @em 8 bits.
	/// @return												The lowest @em 8 bits as an unsigned 8-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::UChar GetLowestBits8U() const;

	//----------------------------------------------------------------------------------------
	/// Gets the lowest @em 8 bits.
	/// @return												The lowest @em 8 bits as a signed 8-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::Char GetLowestBits8S() const;

	//----------------------------------------------------------------------------------------
	/// Gets the lowest @em 32 bits.
	/// @return												The lowest @em 32 bits as an unsigned 32-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::UInt32 GetLowestBits32U() const;

	//----------------------------------------------------------------------------------------
	/// Gets the lowest @em 32 bits.
	/// @return												The lowest @em 32 bits as a signed 32-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::Int32 GetLowestBits32S() const;

	//----------------------------------------------------------------------------------------
	/// Gets the lowest @em 64 bits.
	/// @return												The lowest @em 64 bits as an unsigned 64-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::UInt64 GetLowestBits64U() const;

	//----------------------------------------------------------------------------------------
	/// Gets the lowest @em 64 bits.
	/// @return												The lowest @em 64 bits as a signed 64-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::Int64 GetLowestBits64S() const;

	/// @}

	/// @name Get Internal Data
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets a copy of the internal data.
	/// @param[out] data							Assigned the internal data copy.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GetDataCopy(maxon::BaseArray<maxon::UChar>& data) const;

	/// @}

	/// @name Operations
	/// @{

	//----------------------------------------------------------------------------------------
	/// Performs the add operation.
	/// @param[in] b									A value.
	//----------------------------------------------------------------------------------------
	void Add(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Performs the subtract operation.
	/// @param[in] b									A value.
	//----------------------------------------------------------------------------------------
	void Sub(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Increments the value by one.
	//----------------------------------------------------------------------------------------
	void Inc();

	//----------------------------------------------------------------------------------------
	/// Decrements the value by one.
	//----------------------------------------------------------------------------------------
	void Dec();

	//----------------------------------------------------------------------------------------
	/// Performs the multiply operation.
	/// @param[in] b									A value.
	//----------------------------------------------------------------------------------------
	void Mul(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Performs the divide operation.
	/// @param[in] b									A value. The result is @em 0, if @formatParam{b} is @em 0 or if its absolute value is bigger than the absolute value of the BigInteger.
	//----------------------------------------------------------------------------------------
	void Div(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Performs the modulo operation.
	/// @param[in] b									A value. The result is @em 0, if @formatParam{b} is @em 0 or if its absolute value is bigger than the absolute value of the BigInteger.
	//----------------------------------------------------------------------------------------
	void Mod(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Performs the divide and modulo operation.
	/// @param[in] b									A value. The result is @em 0, if @formatParam{b} is @em 0 or if its absolute value is bigger than the absolute value of the BigInteger.
	/// @param[out] r									Assigned the remainder of the division.
	//----------------------------------------------------------------------------------------
	void DivMod(const BigInteger* b, BigInteger* r);

	//----------------------------------------------------------------------------------------
	/// Performs the power operation.
	/// @param[in] b									Raises the BigInteger to the power of @formatParam{b}. The result will be @em 0 if @formatParam{b} is negative.
	//----------------------------------------------------------------------------------------
	void Pow(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Performs the power operation and takes the result modulo mod.
	/// @param[in] b									Raises the BigInteger to the power of @formatParam{b}. The result will be @em 0 if @formatParam{b} is negative.
	/// @param[out] mod								Assigned the modulo value.
	//----------------------------------------------------------------------------------------
	void PowMod(const BigInteger* b, const BigInteger* mod);

	//----------------------------------------------------------------------------------------
	/// Calculates the greatest common divisor of the BigInteger and @formatParam{b}. Both values must be greater than @em 0, otherwise the value will remain unchanged.
	/// @param[in] b									Another BigInteger.
	//----------------------------------------------------------------------------------------
	void GreatestCommonDivisor(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Calculates the multiplicative inverse of the BigInteger modulo @formatParam{m}.\n
	/// The new value of the BigInteger will be greater or equal to @em 0 and smaller than @formatParam{m}.
	/// @param[in] m									A value, must be greater than @em 0 and smaller than the BigInteger.
	/// @return												@trueIfOtherwiseFalse{if there is a multiplicative inverse}\n
	///																The value of the BigInteger is unchanged if there is no multiplicative inverse.
	//----------------------------------------------------------------------------------------
	Bool MultiplicativeInverse(const BigInteger* m);

	//----------------------------------------------------------------------------------------
	/// Performs the Left shift operation. If the number of bits to shift is less than @em 0 the bits are shifted right.
	/// @param[in] s									The number of bits to shift.
	//----------------------------------------------------------------------------------------
	void LeftShift(maxon::Int s);

	//----------------------------------------------------------------------------------------
	/// Performs the Right shift operation. If the number of bits to shift is less than @em 0 the bits are shifted left.
	/// @param[in] s									The number of bits to shift.
	//----------------------------------------------------------------------------------------
	void RightShift(maxon::Int s);

	//----------------------------------------------------------------------------------------
	/// Negates the value.
	//----------------------------------------------------------------------------------------
	void Negate();

	/// @}

	/// @name Miscellaneous
	/// @{

	//----------------------------------------------------------------------------------------
	/// Compares two BigInteger values.
	/// @param[in] arg2								A value.
	/// @return												The comparison result.
	//----------------------------------------------------------------------------------------
	maxon::COMPARERESULT Compare(const BigInteger* arg2) const;

	//----------------------------------------------------------------------------------------
	/// Copies the data from another BigInteger.
	/// @param[in] src								The source BigInteger.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool CopyFrom(const BigInteger* src);

	/// @}
};

/// @}

/// @cond IGNORE

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

class iBigInteger;

struct BigIntegerLib : public C4DLibrary
{
	BigInteger*		(*BigInteger_Alloc)();
	void					(*BigInteger_Free)(BigInteger *&pBigInteger);

	Bool					(iBigInteger::*Set1)(maxon::Char c);
	Bool					(iBigInteger::*Set2)(maxon::UChar c);
	Bool					(iBigInteger::*Set3)(maxon::Int16 i);
	Bool					(iBigInteger::*Set4)(maxon::UInt16 u);
	Bool					(iBigInteger::*Set5)(maxon::Int32 i);
	Bool					(iBigInteger::*Set6)(maxon::UInt32 u);
	Bool					(iBigInteger::*Set7)(maxon::Int64 i);
	Bool					(iBigInteger::*Set8)(maxon::UInt64 u);
	Bool					(iBigInteger::*SetRandom)(maxon::Int bitCount, SecureRandomProvider provider);
	Bool					(iBigInteger::*SetRandomPrime)(maxon::Int bitCount, maxon::UInt certainty, SecureRandomProvider provider);
	Bool					(iBigInteger::*IsEven)() const;
	Bool					(iBigInteger::*IsOdd)() const;
	Bool					(iBigInteger::*IsOne)() const;
	Bool					(iBigInteger::*IsZero)() const;
	Bool					(iBigInteger::*IsNegative)() const;
	Bool					(iBigInteger::*IsPowerOfTwo)() const;
	Bool					(iBigInteger::*IsProbablyPrime)(maxon::UInt certainty) const;
	maxon::Int		(iBigInteger::*Sign)() const;
	maxon::Int		(iBigInteger::*GetHighestNonSignBit)() const;
	maxon::Int		(iBigInteger::*GetLowestSetBit)() const;
	maxon::Int		(iBigInteger::*GetLowestClearedBit)() const;
	Bool					(iBigInteger::*IsBitSet)(maxon::Int bit) const;
	maxon::UChar	(iBigInteger::*GetLowestBits8U)() const;
	maxon::Char		(iBigInteger::*GetLowestBits8S)() const;
	maxon::UInt32	(iBigInteger::*GetLowestBits32U)() const;
	maxon::Int32	(iBigInteger::*GetLowestBits32S)() const;
	maxon::UInt64	(iBigInteger::*GetLowestBits64U)() const;
	maxon::Int64	(iBigInteger::*GetLowestBits64S)() const;
	Bool					(iBigInteger::*GetDataCopy)(maxon::BaseArray<maxon::UChar>& data) const;
	void					(iBigInteger::*Add)(const BigInteger* b);
	void					(iBigInteger::*Sub)(const BigInteger* b);
	void					(iBigInteger::*Inc)();
	void					(iBigInteger::*Dec)();
	void					(iBigInteger::*Mul)(const BigInteger* b);
	void					(iBigInteger::*Div)(const BigInteger* b);
	void					(iBigInteger::*Mod)(const BigInteger* b);
	void					(iBigInteger::*DivMod)(const BigInteger* b, BigInteger* r);
	void					(iBigInteger::*Pow)(const BigInteger* b);
	void					(iBigInteger::*PowMod)(const BigInteger* b, const BigInteger* mod);
	void					(iBigInteger::*GreatestCommonDivisor)(const BigInteger* b);
	Bool					(iBigInteger::*MultiplicativeInverse)(const BigInteger* m);
	void					(iBigInteger::*LeftShift)(maxon::Int s);
	void					(iBigInteger::*RightShift)(maxon::Int s);
	void					(iBigInteger::*Negate)();
	void					(iBigInteger::*SetBit)(maxon::Int bit);
	void					(iBigInteger::*ClearBit)(maxon::Int bit);
	void					(iBigInteger::*ToggleBit)(maxon::Int bit);
	maxon::COMPARERESULT	(iBigInteger::*Compare)(const BigInteger* arg2) const;
	Bool					(iBigInteger::*CopyFrom)(const BigInteger* src);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

/// @endcond

#endif // LIB_BIG_INTEGER_H__
