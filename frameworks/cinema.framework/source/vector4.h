/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef VECTOR4_H__
#define VECTOR4_H__

#include "ge_math.h"

//----------------------------------------------------------------------------------------
/// Generic four-element vector mathematics. Can be used with the four-by-four matrix class _Matrix4.
/// @see Vector for the regular vector class.
//----------------------------------------------------------------------------------------
template <class TYPE> class _Vector4
{
public:
	//----------------------------------------------------------------------------------------
	/// Creates an uninitialized vector.
	/// @param[in] dc									Dummy argument. Pass @ref DC.
	//----------------------------------------------------------------------------------------
	explicit _Vector4(_DONTCONSTRUCT dc)
	{
	}

	//----------------------------------------------------------------------------------------
	/// Default constructor. Creates a <i>(0, 0, 0, 1)</i> vector.
	//----------------------------------------------------------------------------------------
	_Vector4()
	{
		m_prElements[0] = (TYPE)0.0; m_prElements[1] = (TYPE)0.0; m_prElements[2] = (TYPE)0.0; m_prElements[3] = (TYPE)1.0;
	}

	//----------------------------------------------------------------------------------------
	/// Creates a <i>(x, y, z, w)</i> vector.
	/// @param[in] xIn								The X component of the vector.
	/// @param[in] yIn								The Y component of the vector.
	/// @param[in] zIn								The Z component of the vector.
	/// @param[in] wIn								The W component of the vector.
	//----------------------------------------------------------------------------------------
	_Vector4(TYPE xIn, TYPE yIn, TYPE zIn, TYPE wIn)
	{
		m_prElements[0] = xIn;
		m_prElements[1] = yIn;
		m_prElements[2] = zIn;
		m_prElements[3] = wIn;
	}

	//----------------------------------------------------------------------------------------
	/// Creates a <i>(v, v, v, v)</i> vector.
	/// @param[in] v									The scalar value.
	//----------------------------------------------------------------------------------------
	explicit _Vector4(TYPE v)
	{
		// Sets all (including w) elements to v
		m_prElements[0] = m_prElements[1] = m_prElements[2] = m_prElements[3] = v;
	}

	//----------------------------------------------------------------------------------------
	/// Creates a <i>(v.x, v.y, v.z, 1.0)</i> vector.
	/// @param[in] v									The ::Vector32 value.
	//----------------------------------------------------------------------------------------
	explicit _Vector4(const Vector32& v)
	{
		m_prElements[0] = (TYPE)v.x; m_prElements[1] = (TYPE)v.y; m_prElements[2] = (TYPE)v.z; m_prElements[3] = (TYPE)1.0;
	}

	//----------------------------------------------------------------------------------------
	/// Creates a <i>(v.x, v.y, v.z, r)</i> vector.
	/// @param[in] v									The ::Vector32 value.
	/// @param[in] r									The ::Float32 value.
	//----------------------------------------------------------------------------------------
	explicit _Vector4(const Vector32& v, Float32 r)
	{
		m_prElements[0] = (TYPE)v.x; m_prElements[1] = (TYPE)v.y; m_prElements[2] = (TYPE)v.z; m_prElements[3] = (TYPE)r;
	}

	//----------------------------------------------------------------------------------------
	/// Creates a <i>(v.x, v.y, v.z, 1.0)</i> vector.
	/// @param[in] v									The ::Vector64 value.
	//----------------------------------------------------------------------------------------
	explicit _Vector4(const Vector64& v)
	{
		m_prElements[0] = (TYPE)v.x; m_prElements[1] = (TYPE)v.y; m_prElements[2] = (TYPE)v.z; m_prElements[3] = (TYPE)1.0;
	}

	//----------------------------------------------------------------------------------------
	/// Creates a <i>(v.x, v.y, v.z, r)</i> vector.
	/// @param[in] v									The ::Vector64 value.
	/// @param[in] r									The ::Float64 value.
	//----------------------------------------------------------------------------------------
	explicit _Vector4(const Vector64& v, Float64 r)
	{
		m_prElements[0] = (TYPE)v.x; m_prElements[1] = (TYPE)v.y; m_prElements[2] = (TYPE)v.z; m_prElements[3] = (TYPE)r;
	}

	//----------------------------------------------------------------------------------------
	/// Sets all vector components to zero.
	//----------------------------------------------------------------------------------------
	void SetZero()
	{
		m_prElements[0] = m_prElements[1] = m_prElements[2] = m_prElements[3] = (TYPE)0.0;
	}

	// dot product: this . b
	//----------------------------------------------------------------------------------------
	/// Calculates the dot product of the vector and vector @formatParam{b}.
	/// @param[in] b									The other vector.
	/// @return												The dot product.
	//----------------------------------------------------------------------------------------
	const TYPE Dot(const _Vector4& b)
	{
		return x * b.x + y * b.y + z * b.z + w * b.w;
	}

	//----------------------------------------------------------------------------------------
	/// Normalizes the vector so that @c w is @em 1.
	/// @note @formatParam{w} must not be @em 0.
	//----------------------------------------------------------------------------------------
	void MakeVector3()
	{
		if (m_prElements[3] == (TYPE)0.0)
		{
			m_prElements[0] = MAXVALUE_FLOAT32;
			m_prElements[1] = MAXVALUE_FLOAT32;
			m_prElements[2] = MAXVALUE_FLOAT32;
		}
		else
		{
			m_prElements[0] /= m_prElements[3];
			m_prElements[1] /= m_prElements[3];
			m_prElements[2] /= m_prElements[3];
		}
		m_prElements[3] = (TYPE)1.0;
	}

	//----------------------------------------------------------------------------------------
	/// Subtracts two vectors.
	/// @param[in] a									The first vector.
	/// @param[in] b									The second vector.
	/// @return												The result of the vector subtraction.
	//----------------------------------------------------------------------------------------
	friend const _Vector4 operator - (const _Vector4& a, const _Vector4& b)
	{
		return _Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	//----------------------------------------------------------------------------------------
	/// Adds two vectors.
	/// @param[in] a									The first vector.
	/// @param[in] b									The second vector.
	/// @return												The result of the vector addition.
	//----------------------------------------------------------------------------------------
	friend const _Vector4 operator + (const _Vector4& a, const _Vector4& b)
	{
		return _Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	//----------------------------------------------------------------------------------------
	/// Adds two vectors together and sets the left-hand vector to the result.
	/// @param[in] a									The right-hand vector.
	/// @return												The result of the vector addition assigned to the left-hand vector.
	//----------------------------------------------------------------------------------------
	const _Vector4& operator += (const _Vector4& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;
		return *this;
	}

/// @cond IGNORE
#ifdef MAXON_TARGET_WINDOWS
	__forceinline
#else
	__attribute((always_inline))
#endif
/// @endcond
	//----------------------------------------------------------------------------------------
	/// Multiplies each vector components by a scalar and set the vector to the result.
	/// @param[in] a									The right-hand scalar.
	/// @return												The result of the multiplication assigned to the left-hand vector.
	//----------------------------------------------------------------------------------------
	const _Vector4 &operator *= (const Float a)
	{
		x *= (TYPE)a;
		y *= (TYPE)a;
		z *= (TYPE)a;
		w *= (TYPE)a;
		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// Multiplies each vector component in the left-hand vector by its counterpart in the right-hand vector.
	/// @param[in] a									The first vector.
	/// @param[in] b									The second vector.
	/// @return												The result of the multiplication.
	//----------------------------------------------------------------------------------------
	friend const _Vector4 operator ^ (const _Vector4& a, const _Vector4& b)
	{
		return _Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	//----------------------------------------------------------------------------------------
	/// Calculates the dot product of two vectors.
	/// @param[in] a									The first vector.
	/// @param[in] b									The second vector.
	/// @return												The result of the dot product.
	//----------------------------------------------------------------------------------------
	friend const TYPE Dot(const _Vector4& a, const _Vector4& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	//----------------------------------------------------------------------------------------
	/// Multiplies the vector by a scalar.
	/// @param[in] a									The vector.
	/// @param[in] b									The scalar.
	/// @return												The result of the multiplication.
	//----------------------------------------------------------------------------------------
	friend const _Vector4 operator * (const _Vector4& a, TYPE b)
	{
		return _Vector4(a.x * b, a.y * b, a.z * b, a.w * b);
	}

	//----------------------------------------------------------------------------------------
	/// Casts the _Vector4 to a Vector.
	/// @param[in] v									The vector to cast.
	/// @return												The _Vector4 casted to a ::Vector.
	//----------------------------------------------------------------------------------------
	friend const Vector& GetVector3(const _Vector4& v)
	{
		return *((Vector*)(v.m_prElements));
	}

	//----------------------------------------------------------------------------------------
	/// Equality operator. Checks if the two vectors are equal.
	/// @param[in] a									The first vector.
	/// @param[in] b									The second vector.
	/// @return												@trueIfOtherwiseFalse{the 2 vectors are equal}
	//----------------------------------------------------------------------------------------
	friend Bool operator == (const _Vector4& a, const _Vector4& b)
	{
		return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
	}

#ifdef MAXON_TARGET_WINDOWS
	#pragma warning(push)
	#pragma warning(disable: 4201) // nonstandard extension used : nameless struct/union
#endif

	union
	{
		struct
		{
			TYPE	x,												///< X component of the vector.
						y,												///< Y component of the vector.
						z,												///< Z component of the vector.
						w;												///< W component of the vector.
		};
		TYPE m_prElements[4];						///< An array storing the @ref x, @ref y, @ref z and @ref w components.
	};
#ifdef MAXON_TARGET_WINDOWS
	#pragma warning(pop)
#endif
};

typedef _Vector4<Float32> Vector4d32;			///< Single-precision Vector4.
typedef _Vector4<Float64> Vector4d64;			///< Double-precision Vector4.

#ifdef MAXON_TARGET_SINGLEPRECISION
	#define Vector4d Vector4d32			///< Vector4 for single-precision @C4D versions.
	#define RVtoSV4(x) (x)					///< Converts from double-precision ::Vector4d64 to single-precision ::Vector4d32. Does nothing on single-precision @C4D versions.
#else
	#define Vector4d Vector4d64			///< Vector4 for double-precision @C4D versions.
	#define RVtoSV4(_x_) Vector4d32((Float32)_x_.x, (Float32)_x_.y, (Float32)_x_.z, (Float32)_x_.w)			///< Converts from double-precision ::Vector4d64 to single-precision ::Vector4d32.
#endif

#endif // VECTOR4_H__
