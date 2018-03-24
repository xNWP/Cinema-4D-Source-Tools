/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef CUSTOMGUI_DESCPROPERTY_H__
#define CUSTOMGUI_DESCPROPERTY_H__

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "lib_description.h"

class AtomArray;

/// Description property custom GUI ID.
#define CUSTOMGUI_DESCRIPTIONPROPERTY			1000485

/// @addtogroup DESCRIPTIONPROPERTY_CUSTOMGUISETTINGS
/// @ingroup CUSTOMGUISETTINGS
/// @{
#define DESCRIPTIONPROPERTY_SHOWBUTTON					10005			///< ::Bool Show special button.
#define DESCRIPTIONPROPERTY_INDENT							10006			///< ::Bool Indent text.
#define DESCRIPTIONPROPERTY_BPDOT								10007			///< ::Bool Use @BP3D dot.

#define DESCRIPTIONPROPERTY_PARENTMSG						20000			///< @markPrivate
/// @}

#define SETTING_AUTOIDENT			(1)			///< ::Bool Indent text if animation symbol is visible.
#define SETTING_HEIGHT				(2)			///< ::Bool Height.

/// @addtogroup BFM_ACTION_DP
/// @ingroup group_enumeration
/// @{
#define BFM_ACTION_DP_MENUCLICK		'menu'			///< ::Bool Right mouse button.
#define BFM_ACTION_DP_ADDSELECT		'adds'			///< ::Bool Shift.
#define BFM_ACTION_DP_SUBSELECT		'subs'			///< ::Bool Control.
#define BFM_ACTION_DP_FOCUS				'dpfc'			///< ::Bool Focus.
#define BFM_ACTION_DP_ANIMCLICK		'anim'			///< ::Bool Animation click.
#define BFM_ACTION_DP_BUTTONCLICK	'butt'			///< ::Bool Double left mouse button click.
#define BFM_ACTION_QUAL						'qual'			///< ::Int32 Qualifier.
/// @}

/// @addtogroup DESCPROP
/// @ingroup group_enumeration
/// @{
#define DESCPROP_SEQUENCE						(1 << 0)			///< Has a sequence on the current frame.
#define DESCPROP_KEY								(1 << 1)			///< Has a key on the current frame.
#define DESCPROP_AUTOKEY_ACTIVE			(1 << 2)			///< Autokey active icon.
#define DESCPROP_AUTOKEY_INACTIVE		(1 << 3)			///< Autokey inactive icon.
#define DESCPROP_NOANIM							(1 << 4)			///< No animation.
#define DESCPROP_ENABLED						(1 << 5)			///< Enabled.
#define DESCPROP_ANIM_NOT_ALLOWED		(1 << 6)			///< Animation not allowed.
#define DESCPROP_GLOBAL_PARAMETER		(1 << 7)			///< Global parameter.
#define DESCPROP_KEY_CHANGED				(1 << 9)			///< Has a key on the current frame but the value changed.
#define DESCPROP_HIDDEN							(1 << 10)			///< Hidden description property.
#define DESCPROP_LOCKED							(1 << 11)			///< Locked description property.
#define DESCPROP_KEY_MUTED					(1 << 12)			///< Current key frame is muted.
#define DESCPROP_PORTIN							(1 << 13)			///< Port used by XPresso as inport.
#define DESCPROP_PORTIN_CONNECTED		(1 << 14)			///< Port used by XPresso as connected inport.
#define DESCPROP_PORTOUT						(1 << 15)			///< Port used by XPresso as outport.
#define DESCPROP_PORTOUT_CONNECTED	(1 << 16)			///< Port used by XPresso as connected outport.
#define DESCPROP_CHANGED						(1 << 17)			///< The value changed.
#define DESCPROP_NOTOVERRIDE				(1 << 18)			///< Parameter is not overridden. @since R17.032
#define DESCPROP_AUTOTAKE						(1 << 19)			///< Description is enabled for Auto Take. @since R17.032
#define DESCPROP_INVERTENABLING			(1 << 20)			///< Description enabling defined by override from Take has to be inverted. @since R17.032
/// @}

/// @see GeUserArea::HandleMouseDrag and ::DRAGTYPE_DESCID
struct DescPropertyDragData
{
	AtomArray *arr;			///< Current selection.
	DescID did;					///< Current description ID.
};

//----------------------------------------------------------------------------------------
/// Description property custom GUI (@ref CUSTOMGUI_DESCRIPTIONPROPERTY).\n
/// Here are the settings: @enumerateEnum{DESCRIPTIONPROPERTY_CUSTOMGUISETTINGS}\n
/// The following custom parent message IDs are sent: @enumerateEnum{BFM_ACTION_DP}
//----------------------------------------------------------------------------------------
class DescriptionPropertyCustomGui : public BaseCustomGui<CUSTOMGUI_DESCRIPTIONPROPERTY>
{
		DescriptionPropertyCustomGui();
		~DescriptionPropertyCustomGui();

	public:

		//----------------------------------------------------------------------------------------
		/// Sets the description ID to display.\n
		/// @note The name of the element must have as many parts, separated by ~!~, as @formatParam{id}.@link DescID::GetDepth GetDepth()@endlink. These are displayed separated by dots.
		/// @param[in] id									The description ID.
		//----------------------------------------------------------------------------------------
		void SetDescID(const DescID &id);

		//----------------------------------------------------------------------------------------
		/// Sets the display flags.
		/// @param[in] flags							A combination of these flags: @enumerateEnum{DESCPROP}
		//----------------------------------------------------------------------------------------
		void SetState(Int32 flags);

		//----------------------------------------------------------------------------------------
		/// Gets the display flags.
		/// @return												A combination of these flags: @enumerateEnum{DESCPROP}
		//----------------------------------------------------------------------------------------
		Int32 GetState();

		//----------------------------------------------------------------------------------------
		/// Gets the number of parts. (For instance "Foo . Bar" has 2 parts.)
		/// @return												The number of parts.
		//----------------------------------------------------------------------------------------
		Int32 GetPartCount();

		//----------------------------------------------------------------------------------------
		/// Gets information for each part.
		/// @param[in] part								The part index: @em 0 <= @formatParam{part} < GetPartCount()
		/// @param[in] str								The part title.
		/// @param[in] id									The part ID.
		/// @param[in] onoff							The selection state.
		//----------------------------------------------------------------------------------------
		void GetPartInfo(Int32 part, String &str, DescID &id, Bool &onoff);

		//----------------------------------------------------------------------------------------
		/// Sets the selection state.
		/// @param[in] id									The description ID to set the state for.
		/// @param[in] onoff							The new selection state.
		//----------------------------------------------------------------------------------------
		void SetSelection(const DescID &id, Bool onoff);

		//----------------------------------------------------------------------------------------
		/// Sets the description property settings.
		/// @param[in] settings						The new settings: @enumerateEnum{DESCRIPTIONPROPERTY_CUSTOMGUISETTINGS}
		//----------------------------------------------------------------------------------------
		void ChangeSettings(const BaseContainer &settings);
};

/// @cond IGNORE

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_DEF_
	class iDescriptionPropertyCustomGui : public iBaseCustomGui
	{
		iDescriptionPropertyCustomGui(const BaseContainer &settings, CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings, plugin) { }
	};
#else
	class iDescriptionPropertyCustomGui;
#endif

struct CustomGuiDescriptionPropertyLib : public BaseCustomGuiLib
{
	void	(iDescriptionPropertyCustomGui::*SetState				)(Int32 flags);
	Int32	(iDescriptionPropertyCustomGui::*GetState				)();
	void	(iDescriptionPropertyCustomGui::*SetDescID			)(const DescID &id);
	Int32	(iDescriptionPropertyCustomGui::*GetPartCount		)();
	void	(iDescriptionPropertyCustomGui::*GetPartInfo		)(Int32 part, String &str, DescID &id, Bool &onoff);
	void	(iDescriptionPropertyCustomGui::*SetSelection		)(const DescID &id, Bool onoff);
	void	(iDescriptionPropertyCustomGui::*ChangeSettings	)(const BaseContainer &settings);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

/// @endcond

#endif // CUSTOMGUI_DESCPROPERTY_H__
