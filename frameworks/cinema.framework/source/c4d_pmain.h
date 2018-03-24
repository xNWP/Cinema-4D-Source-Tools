#ifndef C4D_PMAIN_H__
#define C4D_PMAIN_H__

#ifdef MAXON_TARGET_OSX

extern "C"
{
	#define C4D_MAIN Int32 __attribute__((visibility("default"))) c4d_main(Int32 action, void* p1, void* p2, void* p3)
	C4D_MAIN;
}

#elif defined MAXON_TARGET_WINDOWS

extern "C"
{
	#define C4D_MAIN Int32 __declspec(dllexport) c4d_main(Int32 action, void* p1, void* p2, void* p3)
	C4D_MAIN;

#ifdef __WINCRTINIT
	extern BOOL APIENTRY _CRT_INIT(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved);
#endif
}

#else

extern "C"
{
	#define C4D_MAIN __attribute__ ((visibility("default"))) Int32 c4d_main(Int32 action, void* p1, void* p2, void* p3)
	C4D_MAIN;
}

#endif

#endif // C4D_PMAIN_H__
