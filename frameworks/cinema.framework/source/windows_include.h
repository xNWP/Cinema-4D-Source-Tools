#ifndef WINDOWS_INCLUDE_H__
#define WINDOWS_INCLUDE_H__

// Rename Windows LONG/ULONG type as it collides with CINEMA 4D API's new definition
#define LONG	WinLONG
#define ULONG	WinULONG

// Prevent include of Windows dialog definitions that will collide with CINEMA 4D API's types
#define	WIN32_LEAN_AND_MEAN

#include <windows.h>

#undef LONG
#undef ULONG

#endif // WINDOWS_INCLUDE_H__
