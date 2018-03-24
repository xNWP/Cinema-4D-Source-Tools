#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(HASHCODE_H__)
#define HASHCODE_H__

#include "../general.h"

namespace maxon
{

/// @addtogroup group_maxondatastructures
/// @{


/// This class implements default hash functions. They are used by HashMap.
/// The class defines hash functions for the following cases:
///  - integral values
///  - pointers (where different pointers are assumed to be different keys, so only the address is considered, not the content)
///  - objects whose type has a GetHashCode member function and which can be compared with ==
///
/// For any other case you have to define your own hash function, see CStringHash for the case of C-strings.
class DefaultHash
{
public:
	/* from Sun's implementation of java.util.HashMap:
		 Applies a supplemental hash function to a given hashCode, which defends against poor quality hash functions.
		 This is critical because HashMap uses power-of-two length hash tables, that otherwise encounter collisions
		 for hashCodes that do not differ in lower bits. Note: Null keys always map to hash 0, thus index 0.
	 */
#ifdef MAXON_TARGET_64BIT
	static UInt GetHashCode(UInt32 i)
	{
		UInt h = i;
		h ^= (h >> 20) ^ (h >> 12);
		return h ^ (h >> 7) ^ (h >> 4);
	}

	static UInt GetHashCode(UInt64 h)
	{
		h ^= h >> 32;
		h ^= (h >> 20) ^ (h >> 12);
		return h ^ (h >> 7) ^ (h >> 4);
	}
#else
	static UInt GetHashCode(UInt32 h)
	{
		h ^= (h >> 20) ^ (h >> 12);
		return h ^ (h >> 7) ^ (h >> 4);
	}

	static UInt GetHashCode(UInt64 h)
	{
		return GetHashCode((UInt32) (h ^ (h >> 32)));
	}
#endif
	static UInt GetHashCode(Int32 h)
	{
		return GetHashCode((UInt32) h);
	}

	static UInt GetHashCode(Int64 h)
	{
		return GetHashCode((UInt64) h);
	}

	template <typename T> static UInt GetHashCode(const T* key)
	{
		return GetHashCode((UInt) key);
	}

	template <typename T> static UInt GetHashCode(T* key)
	{
		return GetHashCode((UInt) key);
	}

	template <typename K> static UInt GetHashCode(const K& key)
	{
		return key.GetHashCode();
	}

	template <typename K1, typename K2> static Bool IsEqual(const K1& a, const K2& b)
	{
		return a == b;
	}
};


/// This class can be used as template argument for a HashMap if the HashMap shall use C-string keys.
class CStringHash
{
public:
	static UInt GetHashCode(const Char* key)
	{
		UInt hash = 0;
		if (key)
		{
			while (*key)
			{
				hash = 31 * hash + *key;
				++key;
			}
		}
		return hash;
	}

	static Bool IsEqual(const Char* a, const Char* b)
	{
		return (a == b) || (a && b && (strcmp(a, b) == 0));
	}
};

/// @}

} // namespace maxon

#endif
