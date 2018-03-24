#ifndef ENUMFLAGS_H__
#define ENUMFLAGS_H__

#ifndef C4DMISC_APIBASE_H__
	#error "Do not include this file directly"
#endif

// forward declarations for GetTypeInfo in ENUM_xxx defines
class DataTypeInfo;
template <typename T> const DataTypeInfo* GetTypeInfo();
template <> const DataTypeInfo* GetTypeInfo<Int32>();

class IllegalEnumAccess
{
public:
	IllegalEnumAccess() {}
};

class IllegalFlagAccess
{
public:
	IllegalFlagAccess() {}
};

#ifndef ENUM_FLAGS
#define ENUM_FLAGS(X) ; \
	template<> inline const DataTypeInfo* GetTypeInfo<X>() { return GetTypeInfo<Int32>(); } \
	inline X operator |(X a, X b) { return X(UInt32(a)|UInt32(b)); } \
	inline X operator &(X a, X b) { return X(UInt32(a)&UInt32(b)); } \
	inline X operator >>(X a, X b) { return X(UInt32(a) << UInt32(b)); } \
	inline X operator <<(X a, X b) { return X(UInt32(a) >> UInt32(b)); } \
	inline X operator ~(X a) { return X(~UInt32(a)); } \
	inline X& operator |=(X& a, X b) { a = X(UInt32(a)|UInt32(b)); return a; } \
	inline X& operator &=(X& a, X b) { a = X(UInt32(a)&UInt32(b)); return a; } \
	inline IllegalFlagAccess operator ++(X a) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator ++(X a, int) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator --(X a) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator --(X a, int) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator !=(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator !=(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator ==(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator ==(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator <(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator <(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator <(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator <=(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator <=(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator <=(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator >(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator >(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator >(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator >=(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator >=(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator >=(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator +(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator +(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator +(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator -(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator -(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator -(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator *(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator *(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator *(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator /(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator /(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator /(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator %(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator %(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator %(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator ^(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator ^(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator ^(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator |(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator |(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator &(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator &(Int32 s1, X s2) { return IllegalFlagAccess(); }
#endif

#define CLASS_ENUM_FLAGS(X) ; \
	inline friend X operator |(X a, X b) { return X(UInt32(a)|UInt32(b)); } \
	inline friend X operator &(X a, X b) { return X(UInt32(a)&UInt32(b)); } \
	inline friend X operator >>(X a, X b) { return X(UInt32(a) << UInt32(b)); } \
	inline friend X operator <<(X a, X b) { return X(UInt32(a) >> UInt32(b)); } \
	inline friend X operator ~(X a) { return X(~UInt32(a)); } \
	inline friend X operator |=(X& a, X b) { a = X(UInt32(a)|UInt32(b)); return a; } \
	inline friend X operator &=(X& a, X b) { a = X(UInt32(a)&UInt32(b)); return a; } \
	inline friend IllegalFlagAccess operator ++(X a) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator ++(X a, int) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator --(X a) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator --(X a, int) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator !=(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator !=(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator ==(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator ==(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator <(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator <(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator <(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator <=(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator <=(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator <=(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator >(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator >(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator >(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator >=(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator >=(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator >=(Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator +(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator +(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator +(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator -(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator -(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator -(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator *(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator *(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator *(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator /(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator /(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator /(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator %(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator %(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator %(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator ^(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator ^(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator ^(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator |(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator |(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator &(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator &(Int32 s1, X s2) { return IllegalFlagAccess(); }

#ifndef ENUM_LIST
#define ENUM_LIST(X) ; \
	template<> inline const DataTypeInfo* GetTypeInfo<X>() { return GetTypeInfo<Int32>(); } \
	inline IllegalEnumAccess operator |(X a, X b) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator &(X a, X b) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ~(X a) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ++(X a) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ++(X a, int) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator --(X a) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator --(X a, int) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ==(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ==(Int32 s2, X s1) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator !=(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator !=(Int32 s2, X s1) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator !(X a) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator +(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator +(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator -(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator -(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator *(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator *(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator /(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator /(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator %(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator %(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator <(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator <(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator >(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator >(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator <=(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator <=(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator >=(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator >=(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator <<(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator <<(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator >>(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator >>(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ^(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ^(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ||(X s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ||(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ||(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator &&(X s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator &&(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator &&(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalFlagAccess operator |(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator |(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator &(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator &(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator <(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator <=(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator >(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator >=(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator +(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator -(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator *(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator /(X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator ^(X s1, X s2) { return IllegalFlagAccess(); }
#endif

#define CLASS_ENUM_LIST(X) ; \
	inline friend IllegalEnumAccess operator |(X a, X b) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator &(X a, X b) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator ~(X a) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator ++(X a) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator ++(X a, int) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator --(X a) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator --(X a, int) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator ==(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator ==(Int32 s2, X s1) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator !=(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator !=(Int32 s2, X s1) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator !(X a) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator +(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator +(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator -(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator -(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator *(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator *(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator /(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator /(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator %(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator %(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator <(X s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator <(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator <(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator >(X s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator >(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator >(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator <=(X s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator <=(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator <=(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator >=(X s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator >=(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator >=(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator <<(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator <<(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator >>(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator >>(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator ^(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator ^(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator ||(X s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator ||(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator ||(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator &&(X s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator &&(X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline friend IllegalEnumAccess operator &&(Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline friend IllegalFlagAccess operator |(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator |(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator &(X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator &(Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator +(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator -(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator *(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator /(X s1, X s2) { return IllegalFlagAccess(); } \
	inline friend IllegalFlagAccess operator ^(X s1, X s2) { return IllegalFlagAccess(); }

#endif // ENUMFLAGS_H__
