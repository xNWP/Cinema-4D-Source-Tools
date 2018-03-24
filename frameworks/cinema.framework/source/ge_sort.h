#ifndef GE_SORT_H__
#define GE_SORT_H__

#include "ge_math.h"
#include "c4d_misc.h"

//----------------------------------------------------------------------------------------
/// @markDeprecated Use maxon::BaseSort instead.
//----------------------------------------------------------------------------------------
class GeSortAndSearchEx
{
private:
	void Bsort(void* start, Int32 count, Int32 msize);
	void Wsort(void* start, Int32 count, Int32 msize);
	void Lsort(void* start, Int32 count, Int32 msize);

	inline void Bswap(Char* a, Char* b, Int32 i);
	inline void Wswap(Int16* a, Int16* b, Int32 i);
	inline void Lswap(Int32* a, Int32* b, Int32 i);

protected:
	virtual Int32 Compare(void* a, void* b) = 0;
	// if (a==b) return 0;
	// if (a<b) return -1;
	// if (a>b) return 1;

public:
	void Sort(void* start, Int32 count, Int32 msize);
	void* Search(void* Key, void* Start, Int32 count, Int32 msize);
	void* SearchOrInsert(void* Key, void* Start, Int32 count, Int32 msize, Int32& insertidx);
};

#endif // GE_SORT_H__
