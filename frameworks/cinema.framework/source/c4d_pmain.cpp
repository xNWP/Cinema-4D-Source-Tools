// this is the "glue" to C4D...
// please modify only if you know exactly what you are doing...

#ifdef MAXON_TARGET_WINDOWS
	#include "windows_include.h"
#endif

#include "c4d_plugin.h"
#include "c4d_file.h"
#include "c4d_resource.h"
#include "operatingsystem.h"
#include "c4d_pmain.h"
#include "c4d_help.h"

#if defined MAXON_TARGET_WINDOWS
	HINSTANCE g_hinstDLL;
	LPVOID g_lpReserved;

	#ifndef __WINCRTINIT
		BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
		{
			switch (ul_reason_for_call)
			{
				case DLL_PROCESS_ATTACH:
					g_hinstDLL = (HINSTANCE)hModule;
					g_lpReserved = lpReserved;
				// case DLL_THREAD_ATTACH:
				// case DLL_THREAD_DETACH:
				// case DLL_PROCESS_DETACH:
					break;
			}
			return true;
		}
	#else
		BOOL APIENTRY DllMainCRTStartup(HINSTANCE hinst, DWORD reason, LPVOID reserved)
		{
			g_hinstDLL = hinst;
			g_lpReserved = reserved;
			return true;
		}
	#endif
#endif

Filename* path_storage;

C4D_MAIN	// (Int32 action, void* p1, void* p2, void* p3)
{
	static Int32 init_count = 0;

	switch (action)
	{
		case C4DPL_INIT_VERSION:
		{
#ifdef MAXON_TARGET_SINGLEPRECISION
			return C4DPL_VERSION | C4DPL_SINGLEPRECISION_PLUGIN;
#else
			return C4DPL_VERSION;
#endif
		}

		case C4DPL_INIT_SYS:
			init_count += 1;
			if (init_count == 1)
			{
				if (InitOS(p1) < API_VERSION)
					return C4DPL_ERROR_VERSION;
				#ifdef MAXON_TARGET_WINDOWS
					#ifdef __WINCRTINIT
						_CRT_INIT(g_hinstDLL, DLL_PROCESS_ATTACH, g_lpReserved);
					#endif
				#elif defined MAXON_TARGET_OSX
					// static initializers are called by __dyld_dlopen, nothing to do here
				#endif
				if (!p3)
					return C4DPL_ERROR_VERSION;

				path_storage = NewObjClear(Filename);
				if (path_storage)
					*path_storage = *(Filename*)p3;
			}
			return 1;

		case C4DPL_MESSAGE:
			if (!PluginMessage((Int32)Int(p1), p2))
				return C4DPL_ERROR;
			return 1;

		case C4DPL_INIT:
			return PluginStart();

		case C4DPL_END:
			init_count -= 1;
			if (init_count == 0)
			{
				PluginEnd();
				FreeResource();
				DeleteObj(path_storage);
				#ifdef MAXON_TARGET_WINDOWS
					#ifdef __WINCRTINIT
						_CRT_INIT(g_hinstDLL, DLL_PROCESS_DETACH, g_lpReserved);
					#endif
				#elif defined MAXON_TARGET_OSX
					// static destructors are called by __dyld_dlclose, nothing to do here
				#endif
			}
			return 1;

		default:
			break;
	}

	return C4DPL_ERROR;
}

