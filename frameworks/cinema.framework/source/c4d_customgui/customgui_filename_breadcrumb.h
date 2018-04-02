/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef CUSTOMGUI_FILENAME_BREADCRUMB_H__
#define CUSTOMGUI_FILENAME_BREADCRUMB_H__

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"

/// Filename breadcrumb custom GUI ID.
#define CUSTOMGUI_FILENAME_BREADCRUMB			200000297

/// @addtogroup FILENAME_BREADCRUMB_CUSTOMGUISETTINGS
/// @ingroup CUSTOMGUISETTINGS
/// @{
#define FILENAME_DIRECTORY								10000			///< ::Bool Directory chooser mode.
#define FILENAME_TEXTURE									10001			///< ::Bool Texture mode.
#define FILENAME_SAVE											10002			///< ::Bool Save mode for chooser.
#define FILENAME_READONLY									10003			///< ::Bool Read-only mode for the field.
#define FILENAME_NOSELECT									10004			///< ::Bool Hide file select button.
/// @}

//----------------------------------------------------------------------------------------
/// Filename breadcrumb custom GUI (@ref CUSTOMGUI_FILENAME_BREADCRUMB).\n
/// Here are the settings: @enumerateEnum{FILENAME_BREADCRUMB_CUSTOMGUISETTINGS}
//----------------------------------------------------------------------------------------
class FilenameBreadCrumbCustomGui : public BaseCustomGui<CUSTOMGUI_FILENAME_BREADCRUMB>
{
		FilenameBreadCrumbCustomGui();
		~FilenameBreadCrumbCustomGui();

	public:
};

/// @cond IGNORE

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
#ifndef _INTERNAL_DEF_
	class iFilenameBreadCrumbCustomGui : public iBaseCustomGui
	{
		iFilenameBreadCrumbCustomGui(const BaseContainer &settings, CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings, plugin) { }
	};
#else
	class iFilenameBreadCrumbCustomGui;
#endif

struct CustomGuiFilenameBreadCrumbLib : public BaseCustomGuiLib
{
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

/// @endcond

#endif // CUSTOMGUI_FILENAME_BREADCRUMB_H__