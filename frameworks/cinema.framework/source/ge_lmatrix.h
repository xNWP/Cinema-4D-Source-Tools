#include "ge_math.h"	// Place before #ifdef

#ifndef GE_LMATRIX_H__
#define GE_LMATRIX_H__

#ifndef USE_API_MAXON

//----------------------------------------------------------------------------------------
/// Represents a double precision matrix.
/// @note @C4D uses a left-handed coordinate system.
//----------------------------------------------------------------------------------------
struct Matrix64
{

	/// @name Vector Components
	/// @{

	Vector64	off,			///< The translation vector.
						v1,				///< The X-axis coordinate of a left-handed coordinate system.
						v2,				///< The Y-axis coordinate of a left-handed coordinate system.
						v3;				///< The Z-axis coordinate of a left-handed coordinate system.

	/// @}

	/// @name Constructors
	/// @{

	//----------------------------------------------------------------------------------------
	/// Default constructor. Constructs a unit matrix.
	//----------------------------------------------------------------------------------------
	Matrix64()
	{
		off	= Vector64(0.0, 0.0, 0.0);
		v1	= Vector64(1.0, 0.0, 0.0);
		v2	= Vector64(0.0, 1.0, 0.0);
		v3	= Vector64(0.0, 0.0, 1.0);
	}

	//----------------------------------------------------------------------------------------
	/// Constructs a matrix from the given vectors.
	/// @param[in] off_in							Assigned to Matrix64::off.
	/// @param[in] v1_in							Assigned to Matrix64::v1.
	/// @param[in] v2_in							Assigned to Matrix64::v2.
	/// @param[in] v3_in							Assigned to Matrix64::v3.
	//----------------------------------------------------------------------------------------
	explicit Matrix64(const Vector64& off_in, const Vector64& v1_in, const Vector64& v2_in, const Vector64& v3_in)
	{
		off	= off_in;
		v1	= v1_in;
		v2	= v2_in;
		v3	= v3_in;
	}

	//----------------------------------------------------------------------------------------
	/// Constructs an uninitialized matrix.
	/// @param[in] v									Dummy argument. Pass @ref DC.
	//----------------------------------------------------------------------------------------
	explicit Matrix64(_DONTCONSTRUCT v) : off(v), v1(v), v2(v), v3(v){ }

	//----------------------------------------------------------------------------------------
	/// Constructs a double precision matrix from a single precision matrix.
	/// @param[in] m									A single precision matrix.
	//----------------------------------------------------------------------------------------
	explicit Matrix64(const Matrix32& m) : off((Vector64)m.off), v1((Vector64)m.v1), v2((Vector64)m.v2), v3((Vector64)m.v3) { }

	/// @}

	/// @name Get/Set Components
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets/sets a vector in the matrix at index @formatParam{i}.\n
	/// @param[in] i									The vector index in the matrix. @em 0 <= @formatParam{i} < 3.\n
	/// 															@em 0 returns @ref off, @em 1 returns @ref v1, @em 2 returns @ref v2, @em 3 returns @ref v3.\n
	/// 															Any other value must not be used and will crash.
	/// @return												The vector at index @formatParam{i}.
	//----------------------------------------------------------------------------------------
	Vector64& operator [] (Int32 i) const { return ((Vector64*)this)[i & 3]; }

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
	Matrix64 operator * (const Matrix64& m2) const
	{
		return Matrix64(off + v1 * m2.off.x + v2 * m2.off.y + v3 * m2.off.z,
						v1 * m2.v1.x + v2 * m2.v1.y + v3 * m2.v1.z,
						v1 * m2.v2.x + v2 * m2.v2.y + v3 * m2.v2.z,
						v1 * m2.v3.x + v2 * m2.v3.y + v3 * m2.v3.z);
	}

	//----------------------------------------------------------------------------------------
	/// Transforms the vector @formatParam{v} by the matrix.
	/// @param[in] v									The vector to transform.
	/// @return												The vector @formatParam{v} transformed by the matrix.
	//----------------------------------------------------------------------------------------
	Vector64 operator * (const Vector64& v) const
	{
		return Vector64(off.x + v1.x * v.x + v2.x * v.y + v3.x * v.z,
						off.y + v1.y * v.x + v2.y * v.y + v3.y * v.z,
						off.z + v1.z * v.x + v2.z * v.y + v3.z * v.z);
	}

	//----------------------------------------------------------------------------------------
	/// Scales each vector of matrix @formatParam{m} by scalar @formatParam{s}.
	/// @param[in] s									The scalar.
	/// @param[in] m									The matrix to multiply.
	/// @return												The result of the scalar multiplication.
	//----------------------------------------------------------------------------------------
	friend Matrix64 operator * (Float64 s, const Matrix64& m)
	{
		return Matrix64(s * m.off, s * m.v1, s * m.v2, s * m.v3);
	}

	//----------------------------------------------------------------------------------------
	/// Scales each vector of the matrix by scalar @formatParam{s}.
	/// @param[in] s									The scalar.
	/// @return												The result of the scalar multiplication.
	//----------------------------------------------------------------------------------------
	Matrix64 operator * (Float64 s) const
	{
		return Matrix64(off * s, v1 * s, v2 * s, v3 * s);
	}

	//----------------------------------------------------------------------------------------
	/// Divides each vector in matrix @formatParam{m} by scalar @formatParam{s}.
	/// @param[in] m									The matrix to divide.
	/// @param[in] s									The scalar.
	/// @return												The result of the scalar division.
	//----------------------------------------------------------------------------------------
	friend const Matrix64 operator / (const Matrix64& m, const Float64 s)
	{
		return Matrix64(m.off / s, m.v1 / s, m.v2 / s, m.v3 / s);
	}

	//----------------------------------------------------------------------------------------
	/// Adds matrices @formatParam{m1} and @formatParam{m2}.
	/// @param[in] m1									The first matrix.
	/// @param[in] m2									The second matrix.
	/// @return												The result of the addition.
	//----------------------------------------------------------------------------------------
	friend const Matrix64 operator + (const Matrix64& m1, const Matrix64& m2)
	{
		return Matrix64(m1.off + m2.off, m1.v1 + m2.v1, m1.v2 + m2.v2, m1.v3 + m2.v3);
	}

	//----------------------------------------------------------------------------------------
	/// Subtracts matrices @formatParam{m1} and @formatParam{m2}.
	/// @param[in] m1									The first matrix.
	/// @param[in] m2									The second matrix.
	/// @return												The result of the subtraction.
	//----------------------------------------------------------------------------------------
	friend const Matrix64 operator - (const Matrix64& m1, const Matrix64& m2)
	{
		return Matrix64(m1.off - m2.off, m1.v1 - m2.v1, m1.v2 - m2.v2, m1.v3 - m2.v3);
	}

	//----------------------------------------------------------------------------------------
	/// Equality operator. Checks if matrix @formatParam{m1} and matrix @formatParam{m2} are equal.
	/// @param[in] m1									The first matrix.
	/// @param[in] m2									The second matrix.
	/// @return												@trueIfOtherwiseFalse{matrix @formatParam{m1} and matrix @formatParam{m2} are equal}
	//----------------------------------------------------------------------------------------
	friend Bool operator == (const Matrix64& m1, const Matrix64& m2)
	{
		return (m1.off == m2.off) && (m1.v1 == m2.v1) && (m1.v2 == m2.v2) && (m1.v3 == m2.v3);
	}

	//----------------------------------------------------------------------------------------
	/// Equality operator. Checks if matrix @formatParam{m1} and matrix @formatParam{m2} are different.
	/// @param[in] m1									The first matrix.
	/// @param[in] m2									The second matrix.
	/// @return												@trueIfOtherwiseFalse{matrix @formatParam{m1} and matrix @formatParam{m2} are not equal}
	//----------------------------------------------------------------------------------------
	friend Bool operator != (const Matrix64& m1, const Matrix64& m2)
	{
		return !(m1 == m2);
	}

	//----------------------------------------------------------------------------------------
	/// Inverts matrix @formatParam{m}.
	/// @param[in] m									A matrix.
	/// @return												The matrix @formatParam{m} inverted.
	//----------------------------------------------------------------------------------------
	friend const Matrix64 operator ~ (const Matrix64& m)
	{
		Matrix64 mi(DC);

		Float64 det = (m.v1.x * (m.v2.y * m.v3.z - m.v3.y * m.v2.z) +
									 m.v2.x * (m.v3.y * m.v1.z - m.v1.y * m.v3.z) +
									 m.v3.x * (m.v1.y * m.v2.z - m.v2.y * m.v1.z));
		if (det == 0.0)
			return Matrix64();

		det = 1.0 / det;
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
	Matrix64 GetTensorMatrix(void) const
	{
		return Matrix64(Vector64(0.0), Vector64(v3.z * v2.y - v3.y * v2.z, v3.x * v2.z - v3.z * v2.x, v3.y * v2.x - v3.x * v2.y), Vector64(v3.y * v1.z - v1.y * v3.z, v3.z * v1.x - v3.x * v1.z, v1.y * v3.x - v3.y * v1.x), Vector64(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x));
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
	void Scale(const Vector64& v)
	{
		v1 *= v.x;
		v2 *= v.y;
		v3 *= v.z;
	}

	//----------------------------------------------------------------------------------------
	/// Uniform matrix scaling.
	/// @param[in] r									The scaling scalar.
	//----------------------------------------------------------------------------------------
	void Scale(Float64 r)
	{
		v1 *= r;
		v2 *= r;
		v3 *= r;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the scaling vector.
	/// @return												The scaling vector.
	//----------------------------------------------------------------------------------------
	Vector64 GetScale() const { return Vector64(Len(v1), Len(v2), Len(v3)); }
	Vector64 Scale() const { return GetScale(); }

	//----------------------------------------------------------------------------------------
	/// Transforms vector @formatParam{v} by the matrix.
	/// @param[in] v									The vector to transform.
	/// @return												The vector @formatParam{v} transformed by the matrix.
	//----------------------------------------------------------------------------------------
	Vector64 TransformVector(const Vector64& v) const
	{
		return Vector64(v1.x * v.x + v2.x * v.y + v3.x * v.z, v1.y * v.x + v2.y * v.y + v3.y * v.z, v1.z * v.x + v2.z * v.y + v3.z * v.z);
	}

/// @}
};

#endif // USE_API_MAXON

#endif // GE_LMATRIX_H__
