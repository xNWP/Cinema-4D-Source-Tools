#if 1
namespace maxon
{
	const maxon::Char* const DataDescriptionDatabaseInterface::MTable::_ids = 
		"LoadDescription@5842c65767b67b83\0" // Result<DataDescription> LoadDescription(const Id& category, const LanguageRef& language, const Id& dataType)
		"LoadDescription@6d2ab978ce209ee4\0" // Result<DataDescription> LoadDescription(const Id& category, const LanguageRef& language, const IdAndVersion& dataType)
		"StoreDescription@2ecdbcb11fb09163\0" // Result<void> StoreDescription(const Id& category, const LanguageRef& language, const Id& dataType, DataDescription& description)
		"StoreDescription@a71cc741b8084422\0" // Result<void> StoreDescription(const Id& category, const LanguageRef& language, const IdAndVersion& dataType, DataDescription& description)
		"DescriptionDefinitionChanged@ab165b8a5efd2584\0" // Result<void> DescriptionDefinitionChanged(const Id& category, const LanguageRef& language, const IdAndVersion& dataType)
		"GetEffectiveEnumList@120481aec6cfddca\0" // Result<BaseArray<Tuple<Id, Data, String>>> GetEffectiveEnumList(const DataDictionary& dataEntry, const DataDictionary& guiEntry, const DataDescription& stringDescription, Bool resolveExtensionPointsAndGui, const AssetRepositoryRef& repository)
		"PostProcessStringDescription@a6d0fae6b20b30ea\0" // Result<void> PostProcessStringDescription(DataDescription& description, const BaseArray<DataDictionary>& entries)
	"";
	MAXON_WARNING_PUSH
	MAXON_WARNING_DISABLE_DEPRECATED
	class DataDescriptionDatabaseInterface::Hxx2::Unresolved : public DataDescriptionDatabaseInterface
	{
	public:
		static const Unresolved* Get(const DataDescriptionDatabaseInterface* o) { return (const Unresolved*) o; }
		static Unresolved* Get(DataDescriptionDatabaseInterface* o) { return (Unresolved*) o; }
		static Result<DataDescription> LoadDescription(const Id& category, const LanguageRef& language, const Id& dataType) { if (maxon::NonvirtualInterfaceReference::PrivateResolve(&_interface, false)) return DataDescriptionDatabaseInterface::LoadDescription(category, language, dataType); return maxon::PrivateGetNullReturnError(maxon::NULL_RETURN_REASON::UNRESOLVED);}
		static Result<DataDescription> LoadDescription(const Id& category, const LanguageRef& language, const IdAndVersion& dataType) { if (maxon::NonvirtualInterfaceReference::PrivateResolve(&_interface, false)) return DataDescriptionDatabaseInterface::LoadDescription(category, language, dataType); return maxon::PrivateGetNullReturnError(maxon::NULL_RETURN_REASON::UNRESOLVED);}
		static Result<void> StoreDescription(const Id& category, const LanguageRef& language, const Id& dataType, DataDescription& description) { if (maxon::NonvirtualInterfaceReference::PrivateResolve(&_interface, false)) return DataDescriptionDatabaseInterface::StoreDescription(category, language, dataType, description); return maxon::PrivateGetNullReturnError(maxon::NULL_RETURN_REASON::UNRESOLVED);}
		static Result<void> StoreDescription(const Id& category, const LanguageRef& language, const IdAndVersion& dataType, DataDescription& description) { if (maxon::NonvirtualInterfaceReference::PrivateResolve(&_interface, false)) return DataDescriptionDatabaseInterface::StoreDescription(category, language, dataType, description); return maxon::PrivateGetNullReturnError(maxon::NULL_RETURN_REASON::UNRESOLVED);}
		static Result<void> DescriptionDefinitionChanged(const Id& category, const LanguageRef& language, const IdAndVersion& dataType) { if (maxon::NonvirtualInterfaceReference::PrivateResolve(&_interface, false)) return DataDescriptionDatabaseInterface::DescriptionDefinitionChanged(category, language, dataType); return maxon::PrivateGetNullReturnError(maxon::NULL_RETURN_REASON::UNRESOLVED);}
		static Result<BaseArray<Tuple<Id, Data, String>>> GetEffectiveEnumList(const DataDictionary& dataEntry, const DataDictionary& guiEntry, const DataDescription& stringDescription, Bool resolveExtensionPointsAndGui, const AssetRepositoryRef& repository) { if (maxon::NonvirtualInterfaceReference::PrivateResolve(&_interface, false)) return DataDescriptionDatabaseInterface::GetEffectiveEnumList(dataEntry, guiEntry, stringDescription, resolveExtensionPointsAndGui, repository); return maxon::PrivateGetNullReturnError(maxon::NULL_RETURN_REASON::UNRESOLVED);}
		static Result<void> PostProcessStringDescription(DataDescription& description, const BaseArray<DataDictionary>& entries) { if (maxon::NonvirtualInterfaceReference::PrivateResolve(&_interface, false)) return DataDescriptionDatabaseInterface::PostProcessStringDescription(description, entries); return maxon::PrivateGetNullReturnError(maxon::NULL_RETURN_REASON::UNRESOLVED);}
	};
	MAXON_WARNING_POP
#ifdef PRIVATE_MAXON_ASSEMBLE_UNRESOLVED
	const maxon::NULL_RETURN_TYPE DataDescriptionDatabaseInterface::MTable::_returnTypes[] = 
	{
		maxon::details::NullReturnType<Result<DataDescription>>::value,
		maxon::details::NullReturnType<Result<DataDescription>>::value,
		maxon::details::NullReturnType<Result<void>>::value,
		maxon::details::NullReturnType<Result<void>>::value,
		maxon::details::NullReturnType<Result<void>>::value,
		maxon::details::NullReturnType<Result<BaseArray<Tuple<Id, Data, String>>>>::value,
		maxon::details::NullReturnType<Result<void>>::value,
		maxon::NULL_RETURN_TYPE::OTHER
	};
#endif
	maxon::Bool DataDescriptionDatabaseInterface::MTable::InitUnresolved(maxon::NonvirtualInterfaceReference::UnresolvedAssembler assembler, MTable* tbl)
	{
	#if defined(PRIVATE_MAXON_ASSEMBLE_UNRESOLVED) && !defined(MAXON_TARGET_DEBUG)
		if (maxon::details::NullReturnType<Result<DataDescription>>::value == maxon::NULL_RETURN_TYPE::OTHER) tbl->_DataDescriptionDatabaseInterface_LoadDescription = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_LoadDescription;
	#else
		tbl->_DataDescriptionDatabaseInterface_LoadDescription = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_LoadDescription;
	#endif
	#if defined(PRIVATE_MAXON_ASSEMBLE_UNRESOLVED) && !defined(MAXON_TARGET_DEBUG)
		if (maxon::details::NullReturnType<Result<DataDescription>>::value == maxon::NULL_RETURN_TYPE::OTHER) tbl->_DataDescriptionDatabaseInterface_LoadDescription_1 = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_LoadDescription_1;
	#else
		tbl->_DataDescriptionDatabaseInterface_LoadDescription_1 = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_LoadDescription_1;
	#endif
	#if defined(PRIVATE_MAXON_ASSEMBLE_UNRESOLVED) && !defined(MAXON_TARGET_DEBUG)
		if (maxon::details::NullReturnType<Result<void>>::value == maxon::NULL_RETURN_TYPE::OTHER) tbl->_DataDescriptionDatabaseInterface_StoreDescription = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_StoreDescription;
	#else
		tbl->_DataDescriptionDatabaseInterface_StoreDescription = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_StoreDescription;
	#endif
	#if defined(PRIVATE_MAXON_ASSEMBLE_UNRESOLVED) && !defined(MAXON_TARGET_DEBUG)
		if (maxon::details::NullReturnType<Result<void>>::value == maxon::NULL_RETURN_TYPE::OTHER) tbl->_DataDescriptionDatabaseInterface_StoreDescription_1 = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_StoreDescription_1;
	#else
		tbl->_DataDescriptionDatabaseInterface_StoreDescription_1 = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_StoreDescription_1;
	#endif
	#if defined(PRIVATE_MAXON_ASSEMBLE_UNRESOLVED) && !defined(MAXON_TARGET_DEBUG)
		if (maxon::details::NullReturnType<Result<void>>::value == maxon::NULL_RETURN_TYPE::OTHER) tbl->_DataDescriptionDatabaseInterface_DescriptionDefinitionChanged = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_DescriptionDefinitionChanged;
	#else
		tbl->_DataDescriptionDatabaseInterface_DescriptionDefinitionChanged = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_DescriptionDefinitionChanged;
	#endif
	#if defined(PRIVATE_MAXON_ASSEMBLE_UNRESOLVED) && !defined(MAXON_TARGET_DEBUG)
		if (maxon::details::NullReturnType<Result<BaseArray<Tuple<Id, Data, String>>>>::value == maxon::NULL_RETURN_TYPE::OTHER) tbl->_DataDescriptionDatabaseInterface_GetEffectiveEnumList = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_GetEffectiveEnumList;
	#else
		tbl->_DataDescriptionDatabaseInterface_GetEffectiveEnumList = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_GetEffectiveEnumList;
	#endif
	#if defined(PRIVATE_MAXON_ASSEMBLE_UNRESOLVED) && !defined(MAXON_TARGET_DEBUG)
		if (maxon::details::NullReturnType<Result<void>>::value == maxon::NULL_RETURN_TYPE::OTHER) tbl->_DataDescriptionDatabaseInterface_PostProcessStringDescription = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_PostProcessStringDescription;
	#else
		tbl->_DataDescriptionDatabaseInterface_PostProcessStringDescription = &Hxx2::Wrapper<Hxx2::Unresolved>::_DataDescriptionDatabaseInterface_PostProcessStringDescription;
	#endif
	#ifdef PRIVATE_MAXON_ASSEMBLE_UNRESOLVED
		return assembler(&_interface, (maxon::Char*) tbl, _returnTypes, SIZEOF(MTable) / SIZEOF(void*));
	#else
		return true;
	#endif
	}
	MAXON_INTERFACE_REGISTER(DataDescriptionDatabaseInterface, "net.maxon.interface.datadescriptiondatabase", nullptr);
	PRIVATE_MAXON_DECLARATION_REGISTER_DECLARATION(DT_ProcessEnumListDelegate,, "net.maxon.datatype.processenumlistdelegate");
	MAXON_REGISTRY_REGISTER(ProcessEnumListDelegates);
}
#endif
