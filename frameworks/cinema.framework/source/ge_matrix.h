#include "ge_math.h"	// Place before #ifdef

#ifndef GE_MATRIX_H__
#define GE_MATRIX_H__

#ifndef USE_API_MAXON

struct Matrix64;

//----------------------------------------------------------------------------------------
/// Represents a single precision matrix.
/// @note @C4D uses a left-handed coordinate system.
//----------------------------------------------------------------------------------------
struct Matrix32
{

	/// @name Vector Components
	/// @{

	Vector32	off,			///< The translation vector.
						v1,				///< The X-axis coordinate of a left-handed coordinate system.
						v2,				///< The Y-axis coordinate of a left-handed coordinate system.
						v3;				///< The Z-axis coordinate of a left-handed coordinate system.

	/// @}

	/// @name Constructors
	/// @{

	//----------------------------------------------------------------------------------------
	/// Default constructor. Constructs a unit matrix.
	//----------------------------------------------------------------------------------------
	Matrix32()
	{
		off	= Vector32(0.0f, 0.0f, 0.0f);
		v1	= Vector32(1.0f, 0.0f, 0.0f);
		v2	= Vector32(0.0f, 1.0f, 0.0f);
		v3	= Vector32(0.0f, 0.0f, 1.0f);
	}

	//----------------------------------------------------------------------------------------
	/// Constructs a matrix from the given vectors.
	/// @param[in] off_in							Assigned to Matrix64::off.
	/// @param[in] v1_in							Assigned to Matrix64::v1.
	/// @param[in] v2_in							Assigned to Matrix64::v2.
	/// @param[in] v3_in							Assigned to Matrix64::v3.
	//----------------------------------------------------------------------------------------
	explicit Matrix32(const Vector32& off_in, const Vector32& v1_in, const Vector32& v2_in, const Vector32& v3_in)
	{
		off	= off_in;
		v1	= v1_in;
		v2	= v2_in;
		v3	= v3_in;
	}

	//----------------------------------------------------------------------------------------
	/// Constructs an uninitialized matrix.
	/// @param[in] v									Dummy argument. Pass DC.
	//----------------------------------------------------------------------------------------
	explicit Matrix32(_DONTCONSTRUCT v) : off(v), v1(v), v2(v), v3(v) { }

	//----------------------------------------------------------------------------------------
	/// Constructs a single precision matrix from a double precision matrix.
	/// @param[in] m									A double precision matrix.
	//----------------------------------------------------------------------------------------
	explicit Matrix32(const Matrix64& m);

	/// @}

	/// @name Get/Set Vector Components
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets/sets a vector in the matrix at index @formatParam{i}.\n
	/// @param[in] i									The vector index in the matrix. @em 0 <= @formatParam{i} < 3.\n
	///																@em 0 returns @ref off, @em 1 returns @ref v1, @em 2 returns @ref v2, @em 3 returns @ref v3.\n
	///																Any other value must not be used and will crash.
	/// @return												The vector at index @formatParam{i}.
	//----------------------------------------------------------------------------------------
	Vector32& operator [] (Int32 i) const { return ((Vector32*)this)[i & 3]; }

	/// @}

	/// @name Operators
	/// @{

	//----------------------------------------------------------------------------------------
	/// Matrix product. Multiplies the matrix and matrix @formatParam{m2}.\n
	/// The rule is the matrix after @formatParam{m2}.
	/// @note If a point is transformed with the result matrix, this is identical to first transforming with @formatParam{m2} and then with the matrix.
	/// @param[in] m2									The matrix to multiply with.
	/// @return												The result of the matrix product.
	//----------------------------------------------------------------------------------------
	Matrix32 operator * (const Matrix32& m2) const
	{
		return Matrix32(off + v1 * m2.off.x + v2 * m2.off.y + v3 * m2.off.z,
							v1 * m2.v1.x + v2 * m2.v1.y + v3 * m2.v1.z,
							v1 * m2.v2.x + v2 * m2.v2.y + v3 * m2.v2.z,
							v1 * m2.v3.x + v2 * m2.v3.y + v3 * m2.v3.z);
	}

	//----------------------------------------------------------------------------------------
	/// Transforms the vector @formatParam{v} by the matrix.
	/// @param[in] v									The vector to transform.
	/// @return												The vector @formatParam{v} transformed by the matrix.
	//----------------------------------------------------------------------------------------
	Vector32 operator * (const Vector32& v) const
	{
		return Vector32(off.x + v1.x * v.x + v2.x * v.y + v3.x * v.z,
							off.y + v1.y * v.x + v2.y * v.y + v3.y * v.z,
							off.z + v1.z * v.x + v2.z * v.y + v3.z * v.z);
	}

	//----------------------------------------------------------------------------------------
	/// Scales each vector of matrix @formatParam{m} by scalar @formatParam{s}.
	/// @param[in] s									The scalar.
	/// @param[in] m									The matrix to multiply.
	/// @return												The result of the scalar multiplication.
	//----------------------------------------------------------------------------------------
	friend Matrix32 operator * (Float32 s, const Matrix32& m)
	{
		return Matrix32(s * m.off, s * m.v1, s * m.v2, s * m.v3);
	}

	//----------------------------------------------------------------------------------------
	/// Scales each vector of the matrix by scalar @formatParam{s}.
	/// @param[in] s									The scalar.
	/// @return												The result of the scalar multiplication.
	//----------------------------------------------------------------------------------------
	Matrix32 operator * (Float32 s) const
	{
		return Matrix32(off * s, v1 * s, v2 * s, v3 * s);
	}

	//----------------------------------------------------------------------------------------
	/// Divides each vector in matrix @formatParam{m} by scalar @formatParam{s}.
	/// @param[in] m									The matrix to divide.
	/// @param[in] s									The scalar.
	/// @return												The result of the scalar division.
	//----------------------------------------------------------------------------------------
	friend const Matrix32 operator / (const Matrix32& m, const Float32 s)
	{
		return Matrix32(m.off / s, m.v1 / s, m.v2 / s, m.v3 / s);
	}

	//----------------------------------------------------------------------------------------
	/// Adds matrices @formatParam{m1} and @formatParam{m2}.
	/// @param[in] m1									The first matrix.
	/// @param[in] m2									The second matrix.
	/// @return												The result of the addition.
	//----------------------------------------------------------------------------------------
	friend const Matrix32 operator + (const Matrix32& m1, const Matrix32& m2)
	{
		return Matrix32(m1.off + m2.off, m1.v1 + m2.v1, m1.v2 + m2.v2, m1.v3 + m2.v3);
	}

	//----------------------------------------------------------------------------------------
	/// Subtracts matrices @formatParam{m1} and @formatParam{m2}.
	/// @param[in] m1									The first matrix.
	/// @param[in] m2									The second matrix.
	/// @return												The result of the subtraction.
	//----------------------------------------------------------------------------------------
	friend const Matrix32 operator - (const Matrix32& m1, const Matrix32& m2)
	{
		return Matrix32(m1.off - m2.off, m1.v1 - m2.v1, m1.v2 - m2.v2, m1.v3 - m2.v3);
	}

	//----------------------------------------------------------------------------------------
	/// Equality operator. Checks if vectors in matrix @formatParam{m1} are identical to vectors in matrix @formatParam{m2}.
	/// @param[in] m1									The first matrix.
	/// @param[in] m2									The second matrix.
	/// @return												@trueIfOtherwiseFalse{matrix @formatParam{m1} and matrix @formatParam{m2} are equal}
	//----------------------------------------------------------------------------------------
	friend Bool operator == (const Matrix32& m1, const Matrix32& m2)
	{
		return (m1.off == m2.off) && (m1.v1 == m2.v1) && (m1.v2 == m2.v2) && (m1.v3 == m2.v3);
	}

	//----------------------------------------------------------------------------------------
	/// Equality operator. Checks if any vector in matrix @formatParam{m1} is different to any vector in matrix @formatParam{m2}.
	/// @param[in] m1									The first matrix.
	/// @param[in] m2									The second matrix.
	/// @return												@trueIfOtherwiseFalse{matrix @formatParam{m1} and matrix @formatParam{m2} are not equal}
	//----------------------------------------------------------------------------------------
	friend Bool operator != (const Matrix32& m1, const Matrix32& m2)
	{
		return !(m1 == m2);
	}

	//----------------------------------------------------------------------------------------
	/// Inverts matrix @formatParam{m}.
	/// @param[in] m									A matrix.
	/// @return												The matrix @formatParam{m} inverted.
	//----------------------------------------------------------------------------------------
	friend const Matrix32 operator ~ (const Matrix32& m)
	{
		Matrix32 mi(DC);

		Float32 det = (m.v1.x * (m.v2.y * m.v3.z - m.v3.y * m.v2.z) +
									 m.v2.x * (m.v3.y * m.v1.z - m.v1.y * m.v3.z) +
									 m.v3.x * (m.v1.y * m.v2.z - m.v2.y * m.v1.z));

		if (det == 0.0f)
			return Matrix32();

		det = 1.0f / det;
		mi.off.x = (m.v2.x * (m.off.y * m.v3.z - m.v3.y * m.off.z) +
								m.v3.x * (m.off.z * m.v2.y - m.off.y * m.v2.z) +
								m.off.x * (m.v3.y * m.v2.z - m.v2.y * m.v3.z)) * det;
		mi.off.y = (m.v3.x * (m.off.y * m.v1.z - m.v1.y * m.off.z) +
								m.off.x * (m.v1.y * m.v3.z - m.v3.y * m.v1.z) +
								m.v1.x * (m.v3.y * m.off.z - m.off.y * m.v3.z)) * det;
		mi.off.z = (m.off.x * (m.v2.y * m.v1.z - m.v1.y * m.v2.z) +
								m.v1.x * (m.v2.z * m.off.y - m.v2.y * m.off.z) +
								m.v2.x * (m.off.z * m.v1.y - m.off.y * m.v1.z)) * det;

		mi.v1.x = (m.v2.y * m.v3.z - m.v3.y * m.v2.z) * det;
		mi.v1.y = (m.v3.y * m.v1.z - m.v1.y * m.v3.z) * det;
		mi.v1.z = (m.v1.y * m.v2.z - m.v2.y * m.v1.z) * det;

		mi.v2.x = (m.v2.z * m.v3.x - m.v3.z * m.v2.x) * det;
		mi.v2.y = (m.v3.z * m.v1.x - m.v1.z * m.v3.x) * det;
		mi.v2.z = (m.v1.z * m.v2.x - m.v2.z * m.v1.x) * det;

		mi.v3.x = (m.v2.x * m.v3.y - m.v3.x * m.v2.y) * det;
		mi.v3.y = (m.v3.x * m.v1.y - m.v1.x * m.v3.y) * det;
		mi.v3.z = (m.v1.x * m.v2.y - m.v2.x * m.v1.y) * det;

		return mi;
	}

	/// @}

	/// @name Math Operations
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the matrix's tensor.
	/// @return												The tensor matrix.
	//----------------------------------------------------------------------------------------
	Matrix32 GetTensorMatrix(void) const
	{
		return Matrix32(Vector32(0.0f), Vector32(v3.z * v2.y - v3.y * v2.z, v3.x * v2.z - v3.z * v2.x, v3.y * v2.x - v3.x * v2.y), Vector32(v3.y * v1.z - v1.y * v3.z, v3.z * v1.x - v3.x * v1.z, v1.y * v3.x - v3.y * v1.x), Vector32(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x));
	}

	//----------------------------------------------------------------------------------------
	/// Normalizes the matrix.
	//----------------------------------------------------------------------------------------
	void Normalize(void)
	{
		v1.Normalize();
		v2.Normalize();
		v3.Normalize();
	}

	//----------------------------------------------------------------------------------------
	/// Non-uniform matrix scaling.
	/// @param[in] v									The scaling vector.
	//----------------------------------------------------------------------------------------
	void Scale(const Vector32& v)
	{
		v1 *= v.x;
		v2 *= v.y;
		v3 *= v.z;
	}

	//----------------------------------------------------------------------------------------
	/// Uniform matrix scaling.
	/// @param[in] r									The scaling scalar.
	//----------------------------------------------------------------------------------------
	void Scale(Float32 r)
	{
		v1 *= r;
		v2 *= r;
		v3 *= r;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the scaling vector.
	/// @return												The scaling vector.
	//----------------------------------------------------------------------------------------
	Vector32 GetScale() const { return Vector32(Len(v1), Len(v2), Len(v3)); }
	Vector32 Scale() const { return GetScale(); }

	//----------------------------------------------------------------------------------------
	/// Transforms vector @formatParam{v} by the matrix.
	/// @param[in] v									The vector to transform.
	/// @return												The vector @formatParam{v} transformed by the matrix.
	//----------------------------------------------------------------------------------------
	Vector32 TransformVector(const Vector32& v) const
	{
		return Vector32(v1.x * v.x + v2.x * v.y + v3.x * v.z, v1.y * v.x + v2.y * v.y + v3.y * v.z, v1.z * v.x + v2.z * v.y + v3.z * v.z);
	}

/// @}
};

#endif // USE_API_MAXON

#endif // GE_MATRIX_H__
