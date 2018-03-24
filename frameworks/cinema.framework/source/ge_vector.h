#include "ge_math.h"	// Place before #ifdef

#ifndef GE_VECTOR_H__
#define GE_VECTOR_H__

#ifndef USE_API_MAXON

struct Vector64;

//----------------------------------------------------------------------------------------
/// Represents a single precision vector.
//----------------------------------------------------------------------------------------
struct Vector32
{

	/// @name Components
	/// @{

	Float32	x,			///< X component.
					y,			///< Y component.
					z;			///< Z component.

	/// @}

	/// @name Constructors
	/// @{

	//----------------------------------------------------------------------------------------
	/// Default constructor. Sets components to zero.
	//----------------------------------------------------------------------------------------
	Vector32() : x(0.0f), y(0.0f), z(0.0f) { }

	//----------------------------------------------------------------------------------------
	/// Constructs a vector with the given coordinates.
	/// @param[in] ix									Assigned to @ref x.
	/// @param[in] iy									Assigned to @ref y.
	/// @param[in] iz									Assigned to @ref z.
	//----------------------------------------------------------------------------------------
	explicit Vector32(Float32 ix, Float32 iy, Float32 iz) : x(ix), y(iy), z(iz) { }

	//----------------------------------------------------------------------------------------
	/// Constructs an uninitialized vector.
	/// @param[in] v									Dummy argument. Pass @ref DC.
	//----------------------------------------------------------------------------------------
	explicit Vector32(_DONTCONSTRUCT v){ }

	//----------------------------------------------------------------------------------------
	/// Constructs a single precision vector from a double precision vector.
	/// @param[in] v									A double precision vector.
	//----------------------------------------------------------------------------------------
	explicit Vector32(const Vector64& v);

	/// @}

	/// @name Constructors
	/// @{

	//----------------------------------------------------------------------------------------
	/// Constructs a vector setting each component to the same @formatParam{in} value.
	/// @param[in] in									Assigned to @ref x, @ref y and @ref z.
	//----------------------------------------------------------------------------------------
	explicit Vector32(Float32 in) : x(in), y(in), z(in) { }

	/// @}

	/// @name Get/Set Components
	/// @{

	//----------------------------------------------------------------------------------------
	/// Sets a vector component.
	/// @param[in] l									The component index in the vector. @em 0 <= @formatParam{l} < 2.\n
	///																@em 0 returns @ref x, @em 1 returns @ref y and @em 2 returns @ref z.\n
	///																Any other value must not be used and will crash.
	/// @return												The vector component to set.
	//----------------------------------------------------------------------------------------
	Float32& operator [](Int l)
	{
		return (&x)[l];
	}

	//----------------------------------------------------------------------------------------
	/// Gets a vector component.
	/// @param[in] l									The component index in the vector. @em 0 <= @formatParam{l} < 2.\n
	///																@em 0 returns @ref x, @em 1 returns @ref y and @em 2 returns @ref z.\n
	///																Any other value must not be used and will crash.
	/// @return												The vector component to get.
	//----------------------------------------------------------------------------------------
	const Float32& operator [](Int l) const
	{
		return (&x)[l];
	}

	/// @}

	/// @name Math Operations
	/// @{

	//----------------------------------------------------------------------------------------
	/// Checks if each component is zero.
	/// @return												@trueIfOtherwiseFalse{each component is zero}
	//----------------------------------------------------------------------------------------
	Bool IsZero() const
	{
		return (x == 0.0f) && (y == 0.0f) && (z == 0.0f);
	}

	//----------------------------------------------------------------------------------------
	/// Checks if one of the components is not zero.
	/// @return												@trueIfOtherwiseFalse{one of the components is not zero}
	//----------------------------------------------------------------------------------------
	Bool IsNotZero() const
	{
		return (x != 0.0f) || (y != 0.0f) || (z != 0.0f);
	}

	//----------------------------------------------------------------------------------------
	/// Sets all components to zero.
	//----------------------------------------------------------------------------------------
	void SetZero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	//----------------------------------------------------------------------------------------
	/// Checks component-wise if the difference between the vector and vector @formatParam{v2} is no bigger than @formatParam{epsilon}.
	/// @param[in] v2									The other vector to compare against.
	/// @param[in] epsilon						The epsilon value.
	/// @return												@trueIfOtherwiseFalse{the difference is no bigger than @formatParam{epsilon}}
	//----------------------------------------------------------------------------------------
	Bool IsEqual(const Vector32& v2, const Float32& epsilon = 0.01f) const
	{
		return Abs(x - v2.x) < epsilon && Abs(y - v2.y) < epsilon && Abs(z - v2.z) < epsilon;
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the average value of @ref x, @ref y and @ref z components.
	/// @return												The average value of the vector components.
	//----------------------------------------------------------------------------------------
	Float32 GetAverage() const
	{
		return (x + y + z) * Float32(1.0 / 3.0);
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the sum of @ref x, @ref y and @ref z components.
	/// @return												The sum of the vector components.
	//----------------------------------------------------------------------------------------
	Float32 GetSum() const
	{
		return x + y + z;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the minimum of @ref x, @ref y and @ref z components.
	/// @return												The minimum of the vector components.
	//----------------------------------------------------------------------------------------
	Float32 GetMin() const
	{
		if (x < y)
		{
			return (z < x) ? z : x;
		}
		else
		{
			return (z < y) ? z : y;
		}
	}

	//----------------------------------------------------------------------------------------
	/// Gets the maximum of @ref x, @ref y and @ref z components.
	/// @return												The maximum of the vector components.
	//----------------------------------------------------------------------------------------
	Float32 GetMax() const
	{
		if (x > y)
		{
			return (z > x) ? z : x;
		}
		else
		{
			return (z > y) ? z : y;
		}
	}

	//----------------------------------------------------------------------------------------
	/// Gets the vector clamped to the range <i>[0.0 .. 1.0]</i>.
	/// @return												The vector clamped to the range <i>[0.0 .. 1.0]</i>.
	//----------------------------------------------------------------------------------------
	Vector32 Clamp01() const
	{
		return Vector32(::Clamp01(x), ::Clamp01(y), ::Clamp01(z));
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the angle (in radians) between @formatParam{v1} and @formatParam{v2}.
	/// @param[in] v1									The first vector.
	/// @param[in] v2									The second vector.
	/// @return												The angle between @formatParam{v1} and @formatParam{v2}.
	//----------------------------------------------------------------------------------------
	friend Float32 GetAngle(const Vector32& v1, const Vector32& v2)
	{
		Float32 il = Inverse(v1.GetSquaredLength() * v2.GetSquaredLength());
		return ACos((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) * Sqrt(il));
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the dot product of vectors @formatParam{v1} and @formatParam{v2}.
	/// @param[in] v1									The first vector.
	/// @param[in] v2									The second vector.
	/// @return												The dot product of @formatParam{v1} and @formatParam{v2}.
	//----------------------------------------------------------------------------------------
	friend Float32 Dot(const Vector32& v1, const Vector32& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the cross product of vectors @formatParam{v1} and @formatParam{v2}.
	/// @param[in] v1									The first vector.
	/// @param[in] v2									The second vector.
	/// @return												The cross product of @formatParam{v1} and @formatParam{v2}.
	//----------------------------------------------------------------------------------------
	friend Vector32 Cross(const Vector32& v1, const Vector32& v2)
	{
		return Vector32(v1.y * v2.z - v1.z * v2.y,
							v1.z * v2.x - v1.x * v2.z,
							v1.x * v2.y - v1.y * v2.x);
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the length of the vector.
	/// @see Len()
	/// @return												The length of the vector.
	//----------------------------------------------------------------------------------------
	Float32 GetLength(void) const
	{
		return Sqrt(x * x + y * y + z * z);
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the squared length of the vector.
	/// @return												The squared length of the vector.
	//----------------------------------------------------------------------------------------
	Float32 GetSquaredLength(void) const
	{
		return x * x + y * y + z * z;
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the length of vector @formatParam{v}.
	/// @see GetLength()
	/// @param[in] v									The vector.
	/// @return												The length of the vector.
	//----------------------------------------------------------------------------------------
	friend Float32 Len(const Vector32& v)
	{
		return Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the normalized vector, so that GetLength()==@em 1.0.
	/// @see operator!()
	/// @return												The normalized vector.
	//----------------------------------------------------------------------------------------
	Vector32 GetNormalized(void) const
	{
		Float32 l = GetLength();

		if (l == 0.0f)
			return Vector32(0.0f, 0.0f, 0.0f);

		l = 1.0f / l;
		return Vector32(x * l, y * l, z * l);
	}

	//----------------------------------------------------------------------------------------
	/// Normalizes the vector, so that GetLength()==@em 1.0.
	//----------------------------------------------------------------------------------------
	void Normalize(void)
	{
		Float32 l = Sqrt(x * x + y * y + z * z);
		if (l != 0.0f)
		{
			l = 1.0f / l;
			x *= l;
			y *= l;
			z *= l;
		}
	}

	/// @}

	/// @name Operators
	/// @{

	//----------------------------------------------------------------------------------------
	/// Adds scalar @formatParam{s} to each vector component.
	/// @param[in] s									The scalar to add.
	/// @return												This vector.
	//----------------------------------------------------------------------------------------
	const Vector32& operator += (Float32 s)
	{
		x += s;
		y += s;
		z += s;
		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// Adds the vector and vector @formatParam{v}.
	/// @param[in] v									The vector to add.
	/// @return												This vector.
	//----------------------------------------------------------------------------------------
	const Vector32& operator += (const Vector32& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// Subtracts scalar @formatParam{s} from each vector component.
	/// @param[in] s									The scalar to subtract.
	/// @return												This vector.
	//----------------------------------------------------------------------------------------
	const Vector32& operator -= (Float32 s)
	{
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// Subtracts vector @formatParam{v} from the vector.
	/// @param[in] v									The vector to subtract.
	/// @return												This vector.
	//----------------------------------------------------------------------------------------
	const Vector32& operator -= (const Vector32& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// Multiplies each vector component by scalar @formatParam{s}.
	/// @param[in] s									The scalar to multiply.
	/// @return												This vector.
	//----------------------------------------------------------------------------------------
	const Vector32& operator *= (Float32 s)
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// Divides each vector component by scalar @formatParam{s}.
	/// @param[in] s									The dividing scalar.
	/// @return												This vector.
	//----------------------------------------------------------------------------------------
	const Vector32& operator /= (Float32 s)
	{
		if (s != 0.0f)
		{
			s = 1.0f / s;
			x *= s;
			y *= s;
			z *= s;
		}
		else
		{
			x = y = z = 0.0f;
		}

		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// Multiplies the vector component-wise by vector @formatParam{v}.
	/// @param[in] v									The vector to multiply.
	/// @return												This vector.
	//----------------------------------------------------------------------------------------
	const Vector32& operator *= (const Vector32& v)
	{
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the normalized vector @formatParam{v}.
	/// @see GetNormalized()
	/// @param[in] v									The vector.
	/// @return												The normalized vector.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator ! (const Vector32& v)
	{
		Float32 l = Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		if (l == 0.0f)
			return Vector32(0.0f);
		l = 1.0f / l;
		return Vector32(v.x * l, v.y * l, v.z * l);
	}

	//----------------------------------------------------------------------------------------
	/// Multiplies each component of vector @formatParam{v} by scalar @formatParam{s}.
	/// @param[in] s									The scalar.
	/// @param[in] v									The vector.
	/// @return												The scaled vector.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator * (Float32 s, const Vector32& v)
	{
		return Vector32(v.x * s, v.y * s, v.z * s);
	}

	//----------------------------------------------------------------------------------------
	/// Multiplies each component of vector @formatParam{v} by scalar @formatParam{s}.
	/// @param[in] v									The vector.
	/// @param[in] s									The scalar.
	/// @return												The scaled vector.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator * (const Vector32& v, Float32 s)
	{
		return Vector32(v.x * s, v.y * s, v.z * s);
	}

	//----------------------------------------------------------------------------------------
	/// Divides each component of vector @formatParam{v} by scalar @formatParam{s}.
	/// @param[in] v									The vector.
	/// @param[in] s									The scalar.
	/// @return												The scaled vector.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator / (const Vector32& v, Float32 s)
	{
		if (s != 0.0f)
		{
			s = 1.0f / s;
			return Vector32(v.x * s, v.y * s, v.z * s);
		}
		return Vector32(0.0f);
	}

	//----------------------------------------------------------------------------------------
	/// Multiplies vectors @formatParam{v1} and @formatParam{v2} component-wise.
	/// @param[in] v1									The first vector.
	/// @param[in] v2									The second vector.
	/// @return												The result of the vectors multiplication.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator * (const Vector32& v1, const Vector32& v2)
	{
		return Vector32(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}

	//----------------------------------------------------------------------------------------
	/// Adds scalar @formatParam{s} to each component of vector @formatParam{v}.
	/// @param[in] s									The scalar.
	/// @param[in] v									The vector.
	/// @return												The result vector.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator + (Float32 s, const Vector32& v)
	{
		return Vector32(v.x + s, v.y + s, v.z + s);
	}

	//----------------------------------------------------------------------------------------
	/// Adds scalar @formatParam{s} to each component of vector @formatParam{v}.
	/// @param[in] v									The vector.
	/// @param[in] s									The scalar.
	/// @return												The result vector.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator + (const Vector32& v, Float32 s)
	{
		return Vector32(v.x + s, v.y + s, v.z + s);
	}

	//----------------------------------------------------------------------------------------
	/// Adds vectors @formatParam{v1} and @formatParam{v2} component-wise.
	/// @param[in] v1									The first vector.
	/// @param[in] v2									The second vector.
	/// @return												The result of the vectors sum.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator + (const Vector32& v1, const Vector32& v2)
	{
		return Vector32(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	//----------------------------------------------------------------------------------------
	/// Subtracts each component of vector @formatParam{v} from scalar @formatParam{s}.
	/// @param[in] s									The scalar.
	/// @param[in] v									The vector.
	/// @return												The result vector.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator - (Float32 s, const Vector32& v)
	{
		return Vector32(s - v.x, s - v.y, s - v.z);
	}

	//----------------------------------------------------------------------------------------
	/// Subtracts scalar @formatParam{s} from each component of vector @formatParam{v}.
	/// @param[in] v									The vector.
	/// @param[in] s									The scalar.
	/// @return												The result vector.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator - (const Vector32& v, Float32 s)
	{
		return Vector32(v.x - s, v.y - s, v.z - s);
	}

	//----------------------------------------------------------------------------------------
	/// Subtracts vector @formatParam{v1} and @formatParam{v2} component-wise.
	/// @param[in] v1									The first vector.
	/// @param[in] v2									The second vector.
	/// @return												The result of the vectors subtraction.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator - (const Vector32& v1, const Vector32& v2)
	{
		return Vector32(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	//----------------------------------------------------------------------------------------
	/// Gets the negative of vector @formatParam{v}.
	/// @param[in] v									The vector.
	/// @return												The negative vector.
	//----------------------------------------------------------------------------------------
	friend const Vector32 operator - (const Vector32& v)
	{
		return Vector32(-v.x, -v.y, -v.z);
	}

	//----------------------------------------------------------------------------------------
	/// Checks if vectors @formatParam{v1} and @formatParam{v2} are equal component-wise.
	/// @param[in] v1									The first vector.
	/// @param[in] v2									The second vector.
	/// @return												@trueIfOtherwiseFalse{the vectors are equal}
	//----------------------------------------------------------------------------------------
	friend Bool operator == (const Vector32& v1, const Vector32& v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
	}

	//----------------------------------------------------------------------------------------
	/// Checks if each component of vector @formatParam{v1} is equal to scalar @formatParam{r}.
	/// @param[in] v1									The vector.
	/// @param[in] r									The scalar.
	/// @return												@trueIfOtherwiseFalse{the components are all equal to the scalar}
	//----------------------------------------------------------------------------------------
	friend Bool operator == (const Vector32& v1, Float32 r)
	{
		return (v1.x == r) && (v1.y == r) && (v1.z == r);
	}

	//----------------------------------------------------------------------------------------
	/// Checks if any component of vector @formatParam{v1} is different to scalar @formatParam{r}.
	/// @param[in] v1									The vector.
	/// @param[in] r									The scalar.
	/// @return												@trueIfOtherwiseFalse{any component is different to the scalar}
	//----------------------------------------------------------------------------------------
	friend Bool operator != (const Vector32& v1, Float32 r)
	{
		return (v1.x != r) || (v1.y != r) || (v1.z != r);
	}

	//----------------------------------------------------------------------------------------
	/// Checks if vectors @formatParam{v1} and @formatParam{v2} are not equal component-wise.
	/// @param[in] v1									The first vector.
	/// @param[in] v2									The second vector.
	/// @return												@trueIfOtherwiseFalse{the vectors are not equal}
	//----------------------------------------------------------------------------------------
	friend Bool operator != (const Vector32& v1, const Vector32& v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
	}

	/// @}
};

#endif // USE_API_MAXON

#endif // GE_VECTOR_H__
