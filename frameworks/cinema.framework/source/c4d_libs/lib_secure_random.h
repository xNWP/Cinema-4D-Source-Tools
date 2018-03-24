/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef LIB_SECURE_RANDOM_H__
#define LIB_SECURE_RANDOM_H__

#include "c4d_library.h"

#ifdef __API_INTERN__
#include "c4d_library.h"
#include "intbaselist.h"
#endif

/// @addtogroup group_securerandomlibrary Secure Random
/// @ingroup group_library
/// @{

/// Secure random library ID.
#define SECURE_RANDOM_LIB			450000265

struct _SecureRandomProvider;
typedef _SecureRandomProvider* SecureRandomProvider;

class SecureRandom
{
public:
	//----------------------------------------------------------------------------------------
	/// Gets the default secure random provider.
	/// @return												The default secure random provider. @cinemaOwnsPointed{SecureRandomProvider}
	//----------------------------------------------------------------------------------------
	static SecureRandomProvider GetDefaultProvider();

	//----------------------------------------------------------------------------------------
	/// Gets a secure random number.
	/// @param[in] provider						The secure random provider. @callerOwnsPointed{SecureRandomProvider}
	/// @param[in] buffer							A pointer to a buffer that is to be filled. @callerOwnsPointed{buffer}
	/// @param[in] size								The size of the buffer.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	static Bool GetRandomNumber(SecureRandomProvider provider, void* buffer, Int size);
};

/// @}

/// @cond IGNORE

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

struct SecureRandomLib : public C4DLibrary
{
	SecureRandomProvider (*SecureRandom_GetDefaultProvider)();
	Int (*SecureRandom_GetRandomNumber)(SecureRandomProvider provider, void* buffer, Int size); // lBlockLength in bits, lDataLength in bytes
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

/// @endcond

#endif // LIB_SECURE_RANDOM_H__
