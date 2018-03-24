#ifdef __API_INTERN__
	#error "Not in the kernel"
#endif

#include "c4d_string.h"
#include "c4d_memory.h"

Char* String::GetCStringCopy(STRINGENCODING type) const
{
	Char* txt = nullptr;
	Int32 len = StCall(GetCStringLen) (type);
	if (len > 0)
	{
		iferr (txt = NewMemClear(Char, len + 2))
		{
			DebugStop();
		}
		else
		{
			StCall(GetCString) (txt, len + 2, type);
			txt[len] = 0;
		}
	}

	return txt;
}

#if (defined MAXON_TARGET_DEBUG) && (defined MAXON_TARGET_WINDOWS)
static Char array[1000];

Char* cstr(String& str)
{
	str.GetCString(array, 1000);
	return array;
}

Char* cstr(const String& str)
{
	str.GetCString(array, 1000);
	return array;
}

#include "c4d_baselist.h"

Char* cstr(GeListNode* node)
{
	if (node->IsInstanceOf(Tbaselist2d))
		((BaseList2D*)node)->GetName().GetCString(array, 1000);
	else
		strcpy(array, "no baselist");
	return array;
}

#include "c4d_file.h"

Char* cstr(Filename& fn)
{
	fn.GetString().GetCString(array, 1000);
	return array;
}

Char* cstr(const Filename& fn)
{
	fn.GetString().GetCString(array, 1000);
	return array;
}

#endif
