#ifndef GE_MAC_FLAGS_H__
#define GE_MAC_FLAGS_H__

#define MAXON_TARGET_OSX
#define __DEBUGGING__			// Avoid conflicts with DebugAssert() definition for the Mac

#if __LP64__
	#define MAXON_TARGET_64BIT
#endif

#endif // GE_MAC_FLAGS_H__
