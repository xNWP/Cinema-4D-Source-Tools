#if 1
#ifndef DOXYGEN
#endif
#ifndef MAXON_API
#endif
namespace maxon
{
#ifdef MAXON_TARGET_WINDOWS
#else
#endif
#ifdef MAXON_TARGET_WINDOWS
#else
#endif
#ifdef MAXON_TARGET_WINDOWS
#else
#endif
#ifdef MAXON_TARGET_WINDOWS
#else
#endif
#if defined(MAXON_COMPILER_MSVC)
#elif defined(MAXON_COMPILER_CLANG) || defined(MAXON_COMPILER_GCC)
#else
#endif
#if (__LP64__ || _WIN64) && !defined(__64BIT)
#endif
#if (__LP64__ || _WIN64) && !defined(MAXON_TARGET_64BIT)
#endif
#ifdef MAXON_TARGET_64BIT
#else
#endif
#if defined MAXON_TARGET_IOS
#else
#endif
#ifdef MAXON_TARGET_WINDOWS
#else
#endif
#if defined(MAXON_COMPILER_INTEL)
#else
#endif
/// @cond IGNORE

/// @endcond IGNORE

/// @cond INTERNAL

	namespace details
	{
#ifndef PRIVATE_MAXON_DEFINE_MODULE_INFO
#endif
	}
/// @endcond

#ifndef PRIVATE_MAXON_TRANSLATIONUNIT_FLAGS
#ifdef PRIVATE_MAXON_REGISTRATION_FRAMEWORK
#else
#endif
#endif
#ifdef PRIVATE_MAXON_REGISTRATION_UNIT
#elif defined(__BASE_FILE__)
#else
#endif
#ifndef MAXON_TARGET_64BIT
#else
#endif
#if defined(MAXON_COMPILER_INTEL) || defined(MAXON_COMPILER_GCC) || defined(MAXON_COMPILER_CLANG)
#else
#endif
#ifdef USE_API_MAXON
#endif
#ifndef MAXON_REGISTRATION_EXCLUDE_INTERFACES
	PRIVATE_MAXON_DATATYPE_REGISTER_ENUM(VALUEKIND, "net.maxon.datatype.enum.valuekind", SIZEOF(VALUEKIND), true, "NONE\0VOID_TYPE\0GENERIC\0GENERIC_ARITHMETIC\0SCALAR\0INTEGRAL\0FLOATING_POINT\0ENUM\0ENUM_LIST\0ENUM_FLAGS\0DATA\0DATAPTR\0NONVIRTUAL_INTERFACE\0VIRTUAL_INTERFACE\0REF_OR_POINTER\0POINTER\0STRONG_REFERENCE\0COW_REFERENCE\0UNIQUE_REFERENCE\0ACOW_REFERENCE\0LV_REFERENCE\0RV_REFERENCE\0TUPLE\0NAMED_TUPLE\0STRUCT\0SIMD\0BLOCK\0STRIDED_BLOCK\0ARRAY\0BASEARRAY\0BLOCKARRAY\0RESULT\0DELEGATE\0FUNCTION\0CONST_QUALIFIED\0OPAQUE_QUALIFIED\0SOURCE_LEVEL\0DEEP_CONSTNESS\0INT_SIZE_OR_LESS\0ZERO_INITIALIZED\0ORDERED\0TRIVIALLY_CONSTRUCTIBLE\0TRIVIALLY_DESTRUCTIBLE\0TRIVIALLY_COPYABLE\0TRIVIALLY_EQUATABLE\0OBJECT_REF\0VALUE\0ELEMENT_TYPE_AS_ARG\0NEVER_NULLPTR\0SIGNED\0CONTAINER\0STATIC_ARRAY_CONTAINER\0ARRAY_CONTAINER\0CONTAINER_REF\0GENERIC_CONTAINER\0COW_MASK\0STRONG_MASK\0PTR_MASK\0ARRAY_CONTAINER_MASK\0DERIVED_CONTAINER_MASK\0CONTAINER_MASK\0CONTAINER_OR_REF\0REFERENCE_MASK\0ARITHMETIC_MASK\0TUPLE_MASK\0TUPLE_INHERIT_MASK\0POINTER_FLAGS\0QUALIFIER_MASK\0", const maxon::UInt64 values[] = {(maxon::UInt64) VALUEKIND::NONE, (maxon::UInt64) VALUEKIND::VOID_TYPE, (maxon::UInt64) VALUEKIND::GENERIC, (maxon::UInt64) VALUEKIND::GENERIC_ARITHMETIC, (maxon::UInt64) VALUEKIND::SCALAR, (maxon::UInt64) VALUEKIND::INTEGRAL, (maxon::UInt64) VALUEKIND::FLOATING_POINT, (maxon::UInt64) VALUEKIND::ENUM, (maxon::UInt64) VALUEKIND::ENUM_LIST, (maxon::UInt64) VALUEKIND::ENUM_FLAGS, (maxon::UInt64) VALUEKIND::DATA, (maxon::UInt64) VALUEKIND::DATAPTR, (maxon::UInt64) VALUEKIND::NONVIRTUAL_INTERFACE, (maxon::UInt64) VALUEKIND::VIRTUAL_INTERFACE, (maxon::UInt64) VALUEKIND::REF_OR_POINTER, (maxon::UInt64) VALUEKIND::POINTER, (maxon::UInt64) VALUEKIND::STRONG_REFERENCE, (maxon::UInt64) VALUEKIND::COW_REFERENCE, (maxon::UInt64) VALUEKIND::UNIQUE_REFERENCE, (maxon::UInt64) VALUEKIND::ACOW_REFERENCE, (maxon::UInt64) VALUEKIND::LV_REFERENCE, (maxon::UInt64) VALUEKIND::RV_REFERENCE, (maxon::UInt64) VALUEKIND::TUPLE, (maxon::UInt64) VALUEKIND::NAMED_TUPLE, (maxon::UInt64) VALUEKIND::STRUCT, (maxon::UInt64) VALUEKIND::SIMD, (maxon::UInt64) VALUEKIND::BLOCK, (maxon::UInt64) VALUEKIND::STRIDED_BLOCK, (maxon::UInt64) VALUEKIND::ARRAY, (maxon::UInt64) VALUEKIND::BASEARRAY, (maxon::UInt64) VALUEKIND::BLOCKARRAY, (maxon::UInt64) VALUEKIND::RESULT, (maxon::UInt64) VALUEKIND::DELEGATE, (maxon::UInt64) VALUEKIND::FUNCTION, (maxon::UInt64) VALUEKIND::CONST_QUALIFIED, (maxon::UInt64) VALUEKIND::OPAQUE_QUALIFIED, (maxon::UInt64) VALUEKIND::SOURCE_LEVEL, (maxon::UInt64) VALUEKIND::DEEP_CONSTNESS, (maxon::UInt64) VALUEKIND::INT_SIZE_OR_LESS, (maxon::UInt64) VALUEKIND::ZERO_INITIALIZED, (maxon::UInt64) VALUEKIND::ORDERED, (maxon::UInt64) VALUEKIND::TRIVIALLY_CONSTRUCTIBLE, (maxon::UInt64) VALUEKIND::TRIVIALLY_DESTRUCTIBLE, (maxon::UInt64) VALUEKIND::TRIVIALLY_COPYABLE, (maxon::UInt64) VALUEKIND::TRIVIALLY_EQUATABLE, (maxon::UInt64) VALUEKIND::OBJECT_REF, (maxon::UInt64) VALUEKIND::VALUE, (maxon::UInt64) VALUEKIND::ELEMENT_TYPE_AS_ARG, (maxon::UInt64) VALUEKIND::NEVER_NULLPTR, (maxon::UInt64) VALUEKIND::SIGNED, (maxon::UInt64) VALUEKIND::CONTAINER, (maxon::UInt64) VALUEKIND::STATIC_ARRAY_CONTAINER, (maxon::UInt64) VALUEKIND::ARRAY_CONTAINER, (maxon::UInt64) VALUEKIND::CONTAINER_REF, (maxon::UInt64) VALUEKIND::GENERIC_CONTAINER, (maxon::UInt64) VALUEKIND::COW_MASK, (maxon::UInt64) VALUEKIND::STRONG_MASK, (maxon::UInt64) VALUEKIND::PTR_MASK, (maxon::UInt64) VALUEKIND::ARRAY_CONTAINER_MASK, (maxon::UInt64) VALUEKIND::DERIVED_CONTAINER_MASK, (maxon::UInt64) VALUEKIND::CONTAINER_MASK, (maxon::UInt64) VALUEKIND::CONTAINER_OR_REF, (maxon::UInt64) VALUEKIND::REFERENCE_MASK, (maxon::UInt64) VALUEKIND::ARITHMETIC_MASK, (maxon::UInt64) VALUEKIND::TUPLE_MASK, (maxon::UInt64) VALUEKIND::TUPLE_INHERIT_MASK, (maxon::UInt64) VALUEKIND::POINTER_FLAGS, (maxon::UInt64) VALUEKIND::QUALIFIER_MASK})
#endif
#if defined(MAXON_COMPILER_INTEL) || defined(MAXON_COMPILER_MSVC)
#endif
#ifndef MAXON_TARGET_UNITY_MODE
#endif
}
#endif
