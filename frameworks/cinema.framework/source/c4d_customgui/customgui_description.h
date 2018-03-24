/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef CUSTOMGUI_DESCRIPTION_H__
#define CUSTOMGUI_DESCRIPTION_H__

#include "customgui_base.h"
#include "c4d_basecontainer.h"

class AtomArray;
class DescID;
class Description;
struct DescriptionGuiLib;

/// Description custom GUI ID.
#define CUSTOMGUI_DESCRIPTION			1000469

/// @addtogroup DESCRIPTION_CUSTOMGUISETTINGS
/// @ingroup CUSTOMGUISETTINGS
/// @{
#define DESCRIPTION_ALLOWFOLDING				'fldg'			///< ::Bool Allow folding.
#define DESCRIPTION_SHOWTITLE						'titl'			///< ::Bool Show title.
#define DESCRIPTION_NOUNDO							'noun'			///< ::Bool No undo.
#define DESCRIPTION_OBJECTSNOTINDOC			'onid'			///< ::Bool Objects are not located in document.
#define DESCRIPTION_MODALMODE						'modl'			///< ::Int32 Mode for modal dialogs: @em 1==normal, @em 2==no scrollareas
#define DESCRIPTION_LEFTMATEDITREGION		'lmer'			///< ::Bool Mode for left %Material Manager region.
#define DESCRIPTION_STORAGE							'stor'			///< BaseContainer* Pointer to layout storage, stored as @c void.
#define DESCRIPTION_FOLDERSTORE					'fsto'			///< BaseContainer* Pointer to layout storage, stored as @c void.
#define DESCRIPTION_SCALE_ALL_ELEMENTS	'sael'			///< ::Bool Scale all elements.
#define DESCRIPTION_NO_SHOW_SUBCHANNELS	'nssc'			///< ::Bool Remove "Show Sub-channels" the context menu.
#define DESCRIPTION_OPEN_ALL_GROUPS			'opag'			///< ::Bool Unfold all parameter groups.
#define DESCRIPTION_NO_TAKE_OVERRIDES		'ntov'			///< ::Bool: If @formatConstant{true} ignore the overrides enabling/disabling. @since R17.032
#define DESCRIPTION_SINGLEDESC_MODE			'sing'			///< @markPrivate @since R17.032
/// @}

//----------------------------------------------------------------------------------------
/// Callback function.
/// @param[in] master							The registered dialog pointer.
/// @param[in] msg								The message container: @enumerateEnum{MCB}
/// @return												The result.
//----------------------------------------------------------------------------------------
typedef GeData MasterCallBackFunc(GeDialog *master, const BaseContainer &msg);
/// @addtogroup MCB
/// @ingroup group_enumeration
/// @{
#define MCB_NAVIGATIONCHANGED					'navc'			///< The navigation tabs have changed. The message container contains the full names of the navigation tabs.
#define MCB_SETATOMARRAY							'seta'			///< @markPrivate
/// @}

//----------------------------------------------------------------------------------------
/// Allows to query the number of active objects:
/// @code
/// Int32 cnt = sub->MasterMessage(BaseContainer(MM_HASOBJECTS)).GetInt32();
/// @endcode
//----------------------------------------------------------------------------------------
#define MM_HASOBJECTS									'haso'

struct DescriptionFilter
{
	//----------------------------------------------------------------------------------------
	/// @markPrivate Description filter callback. Registered with DescriptionCustomGui::SetFilter().\n
	/// Checks if the description element @formatParam{id} should be visible.
	//----------------------------------------------------------------------------------------
	Bool (*FilterID)(const Description *desc, const DescID &id, const BaseContainer &bc, Bool &subfilter, Bool &hide);
};

/// Attribute Manager filter flags.
enum AMFILTERFLAGS
{
	AMFILTERFLAGS_0							= 0,					///< None.
	AMFILTERFLAGS_SHOWHIDDEN		= 1 << 0,			///< Show hidden parameters.
	AMFILTERFLAGS_SHOWANIMONLY	= 1 << 1,			///< Show animated parameters.
	AMFILTERFLAGS_SHOWLOCKED		= 1 << 2			///< Show locked parameters.
} ENUM_END_FLAGS(AMFILTERFLAGS);


#ifndef _INTERNAL_DEF_CUSTOMGUI_DESCRIPTION

//----------------------------------------------------------------------------------------
/// Attribute Manager custom GUI (@ref CUSTOMGUI_DESCRIPTION).\n
/// Here are the settings: @enumerateEnum{DESCRIPTION_CUSTOMGUISETTINGS}
//----------------------------------------------------------------------------------------
class DescriptionCustomGui : public BaseCustomGui<CUSTOMGUI_DESCRIPTION>
{
		DescriptionCustomGui();
		~DescriptionCustomGui();

	public:
		//----------------------------------------------------------------------------------------
		/// Registers the master callback function.
		/// @param[in] dlg								The parent dialog. @callerOwnsPointed{dialog}
		/// @param[in] func								The callback function.
		//----------------------------------------------------------------------------------------
		void SetMaster(GeDialog *dlg, MasterCallBackFunc *func);

		//----------------------------------------------------------------------------------------
		/// Sends a master message to the custom GUI.
		/// @param[in] msg								The message: ::MM_HASOBJECTS.
		/// @return												The result.
		//----------------------------------------------------------------------------------------
		GeData MasterMessage(const BaseContainer &msg);

		//----------------------------------------------------------------------------------------
		/// Sets the objects that are shown.
		/// @param[in] list								The objects to show.
		//----------------------------------------------------------------------------------------
		void SetObjectList(const AtomArray &list);

		//----------------------------------------------------------------------------------------
		/// Sets a single objects to show.
		/// @param[in] op									The object to show. @callerOwnsPointed{object}
		//----------------------------------------------------------------------------------------
		void SetObject(C4DAtom *op);

		//----------------------------------------------------------------------------------------
		/// Retrieves the objects that are shown.
		/// @param[out] list							Filled with the objects shown.
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool GetObjectList(AtomArray &list);

		//----------------------------------------------------------------------------------------
		/// @markPrivate Registers a filter callback for the description.
		/// @param[in] flt								The callback structure, or @formatConstant{nullptr} to unregister the filter. @callerOwnsPointed{structure}
		//----------------------------------------------------------------------------------------
		void SetFilter(DescriptionFilter *flt);

		//----------------------------------------------------------------------------------------
		/// @markPrivate
		//----------------------------------------------------------------------------------------
		Int32 HighlightDescID(Int32 id, Bool check);

		//----------------------------------------------------------------------------------------
		/// Sets the active description tab.
		/// @param[in] activetab					The tab's page description ID.
		//----------------------------------------------------------------------------------------
		void SetActiveTabPage(const DescID &activetab);

		//----------------------------------------------------------------------------------------
		/// Retrieves the description IDs of the selected description elements.
		/// @param[out] selection					Filled with the description IDs of the selected description elements. The container elements' type is ::CUSTOMDATATYPE_DESCID.
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool GetDescIDSelection(BaseContainer &selection);

		//----------------------------------------------------------------------------------------
		/// Gets the current filter string and flags.
		/// @param[out] flags							Assigned the filter flags: @enumerateEnum{AMFILTERFLAGS}
		/// @return												The current filter string.
		//----------------------------------------------------------------------------------------
		String GetFilterString(AMFILTERFLAGS &flags);

		//----------------------------------------------------------------------------------------
		/// Sets the current filter string and flags.
		/// @param[in] filter							The filter string.
		/// @param[in] flags							The filter flags: @enumerateEnum{AMFILTERFLAGS}
		//----------------------------------------------------------------------------------------
		void SetFilterString(const String &filter, AMFILTERFLAGS flags);
};

#endif

/// @cond IGNORE

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#if !defined _INTERNAL_DEF_ && !defined __API_INTERN__
	class iDescriptionCustomGui
	{
	};
#else
	class iDescriptionCustomGui;
#endif

struct DescriptionGuiLib : public BaseCustomGuiLib
{
	void			(iDescriptionCustomGui::*SetObjectList)(const AtomArray &list);
	void			(iDescriptionCustomGui::*SetObject)(C4DAtom *op);
	Bool			(iDescriptionCustomGui::*GetObjectList)(AtomArray &list);
	void			(iDescriptionCustomGui::*SetMaster)(GeDialog *dlg, MasterCallBackFunc *func);
	GeData		(iDescriptionCustomGui::*MasterMessage)(const BaseContainer &msg);
	void			(iDescriptionCustomGui::*SetFilter)(DescriptionFilter *flt);
	Int32			(iDescriptionCustomGui::*HighlightDescID)(Int32 id, Bool check);
	void			(iDescriptionCustomGui::*SetActiveTabPage)(const DescID &activetab);
	Bool			(iDescriptionCustomGui::*GetDescIDSelection)(BaseContainer &selection);
	void			(iDescriptionCustomGui::*SetFilterString)(const String &str, AMFILTERFLAGS flags);
	String		(iDescriptionCustomGui::*GetFilterString)(AMFILTERFLAGS &flags);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

/// @endcond

#endif // CUSTOMGUI_DESCRIPTION_H__
