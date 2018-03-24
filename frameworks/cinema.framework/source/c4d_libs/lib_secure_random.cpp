#ifdef __API_INTERN__
	#error "Not in kernel"
#endif

#include "c4d_library.h"
#include "lib_secure_random.h"

SecureRandomLib* lib_secureRandom = nullptr;

static SecureRandomLib *CheckLibSecureRandom(Int32 offset)
{
	return (SecureRandomLib*)CheckLib(SECURE_RANDOM_LIB, offset, (C4DLibrary**)&lib_secureRandom);
}

SecureRandomProvider SecureRandom::GetDefaultProvider()
{
	SecureRandomLib *lib = CheckLibSecureRandom(LIBOFFSET(SecureRandomLib, SecureRandom_GetDefaultProvider)); if (!lib) return nullptr;
	return lib->SecureRandom_GetDefaultProvider();
}

Bool SecureRandom::GetRandomNumber(SecureRandomProvider provider, void* buffer, Int size)
{
	SecureRandomLib *lib = CheckLibSecureRandom(LIBOFFSET(SecureRandomLib, SecureRandom_GetRandomNumber)); if (!lib) return false;
	return lib->SecureRandom_GetRandomNumber(provider, buffer, size) != 0;
}

