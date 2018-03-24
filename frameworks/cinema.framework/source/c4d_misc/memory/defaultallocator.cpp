#ifndef USE_API_MAXON

#include "c4d_memory.h"

namespace maxon
{

void* _DefaultAllocNC(Int size, Int32 line, const Char* file)
{
	if (size == 0)
		size = 1;
	return _GeAllocNC(size, line, file);
}

void* _DefaultAlloc(Int size, Int32 line, const Char* file)
{
	if (size == 0)
		size = 1;
	return _GeAlloc(size, line, file);
}

void*	_DefaultReallocNC(void* data, Int size, Int32 line, const Char* file)
{
	return _GeReallocNC(data, size, line, file);
}

void _DefaultFree(void** data_ptr)
{
	return _GeFree(data_ptr);
}

}

#endif
