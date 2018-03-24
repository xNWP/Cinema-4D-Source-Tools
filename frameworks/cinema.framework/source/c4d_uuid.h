/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_UUID_H__
#define C4D_UUID_H__

#ifdef __API_INTERN__
abc def xyz
#endif

#ifdef USE_API_MAXON
	#include "maxon/error.h"
#endif

#include "ge_math.h"
#include "c4d_misc.h"

#define UuidCall(fnc) (this->*C4DOS.Gu->fnc)

class C4DUuid
{
public:
	//----------------------------------------------------------------------------------------
	/// Default constructor.
	//----------------------------------------------------------------------------------------
	C4DUuid()
	{
		C4DOS.Gu->Init(this);
	}

	//----------------------------------------------------------------------------------------
	/// Creates an uninitialized uuid.
	/// @param[in] n									Dummy argument. Pass @ref DC.
	//----------------------------------------------------------------------------------------
	explicit C4DUuid(_DONTCONSTRUCT n)
	{
	}

	//----------------------------------------------------------------------------------------
	/// Creates an empty uuid.
	/// @param[in] n									Dummy argument. Pass @ref EC.
	//----------------------------------------------------------------------------------------
	explicit C4DUuid(_EMPTYCONSTRUCT n)
	{
		ClearMem(dummy, C4DUUID_SIZE);
	}

	//----------------------------------------------------------------------------------------
	/// Copy constructor.
	/// @param[in] uid								Another C4DUuid to copy.
	//----------------------------------------------------------------------------------------
	C4DUuid(const C4DUuid& uid)
	{
		UuidCall(CopyFromUuid) (uid);
	}

	//----------------------------------------------------------------------------------------
	/// Gets the hash code for the uuid.
	/// @return												The uuid's hash code.
	//----------------------------------------------------------------------------------------
	UInt32 GetHashCode() const
	{
		return UuidCall(GetHashCode) ();
	}

	//----------------------------------------------------------------------------------------
	/// Resets the uuid.
	/// @param[in] clear							@trueIfOtherwiseFalse{true} to clear the uuid or @trueIfOtherwiseFalse{false} to reinitialize it.
	//----------------------------------------------------------------------------------------
	void Reset(Bool clear)
	{
		if (clear)
			ClearMem(dummy, C4DUUID_SIZE);
		else
			C4DOS.Gu->Init(this);
	}

	//----------------------------------------------------------------------------------------
	/// Gets the string for the uuid.
	/// @return												The uuid's string.
	//----------------------------------------------------------------------------------------
	String GetString() const
	{
		return UuidCall(GetString)();
	}

	//----------------------------------------------------------------------------------------
	/// Checks if the uuid has content.
	/// @return												@trueIfOtherwiseFalse{the uuid has content}
	//----------------------------------------------------------------------------------------
	Bool Content() const
	{
		return *this != C4DUuid(EC);
	}

	//----------------------------------------------------------------------------------------
	/// Copies the uuid to a ::UChar buffer.
	/// @param[in] buf								The destination buffer.
	//----------------------------------------------------------------------------------------
	void CopyTo(UChar* buf) const
	{
		UuidCall(CopyTo) (buf);
	}

#ifdef USE_API_MAXON
	maxon::Result<void> CopyFrom(UChar* buf)
	{
		UuidCall(CopyFrom) (buf);
		return maxon::OK;
	}

	maxon::Result<void> CopyFrom(const String& uuid)
	{
		if (UuidCall(CopyFromString) (uuid))
			return maxon::OK;

		return maxon::OutOfMemoryError(CREATE);
	}
#else
	//----------------------------------------------------------------------------------------
	/// Copies the uuid from a ::UChar buffer.
	/// @param[in] buf								The source buffer.
	//----------------------------------------------------------------------------------------
	void CopyFrom(UChar* buf)
	{
		UuidCall(CopyFrom) (buf);
	}

	//----------------------------------------------------------------------------------------
	/// Copies the uuid from a string.
	/// @param[in] uuid								The source string.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool CopyFrom(const String& uuid)
	{
		return UuidCall(CopyFromString) (uuid);
	}
#endif

	//----------------------------------------------------------------------------------------
	/// Copies the uuid to another uuid.
	/// @param[in] dst								The destination uuid.
	//----------------------------------------------------------------------------------------
	void CopyTo(const C4DUuid& dst) const
	{
		UuidCall(CopyToUuid) (dst);
	}

	//----------------------------------------------------------------------------------------
	/// Equality operator. Checks if the uuids are equal.
	/// @param[in] k									A uuid to compare with.
	/// @return												@trueIfOtherwiseFalse{the uuids are equal}
	//----------------------------------------------------------------------------------------
	Bool operator == (const C4DUuid& k) const
	{
		return UuidCall(Compare) (k);
	}

	//----------------------------------------------------------------------------------------
	/// Inequality operator. Checks if the uuids are different.
	/// @param[in] k									A uuid to compare with.
	/// @return												@trueIfOtherwiseFalse{the uuids are different}
	//----------------------------------------------------------------------------------------
	Bool operator != (const C4DUuid& k) const
	{
		return !UuidCall(Compare) (k);
	}

private:
	C4D_RESERVE_PRIVATE_TYPE(UChar, dummy[C4DUUID_SIZE]);
};

#endif // C4D_UUID_H__
