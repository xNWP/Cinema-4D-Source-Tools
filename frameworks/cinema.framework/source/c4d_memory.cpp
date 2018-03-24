#ifdef __API_INTERN__
	#error "Not in the kernel"
#endif

#include <string.h>
#include <stdlib.h>

#include "c4d_memory.h"
#include "operatingsystem.h"
#include "c4d_general.h"

void _GeFree(void** Daten)
{
	if (*Daten)
	{
		C4DOS.Ge->Free(*Daten);
	}
	*Daten = nullptr;
}

// only for debug purposes
void _GeCheckAllMemory()
{
	C4DOS.Ge->GeCheckMem((void*)(UInt)0xdeadbeef);
}

void _GeCheck(void* memptr)
{
	if (memptr)
	{
		C4DOS.Ge->GeCheckMem(memptr);
	}
}

Bool GeGetAllocSize(void* p, Int* out_size)
{
	return C4DOS.Ge->GetAllocSize(p, out_size);
}

// allocator is either nullptr (current thread's allocator as used by NewMem, NewObj etc.) or a pool created via GeAllocPool
Bool GeGetAllocatorStatistics(BaseContainer& stat, void* allocator)
{
	return C4DOS.Ge->GeGetAllocatorStatistics(stat, allocator);
}

// try to estimate how much physical memory is still unused
UInt GeMemGetFreePhysicalMemoryEstimate(void)
{
	return C4DOS.Ge->GeMemGetFreePhysicalMemoryEstimate();
}

