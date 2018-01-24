#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include "c4d.h"
#include "main.h"

namespace ST
{
	//----------------------------------------------------------------------------------------
	/// Displays information about the plugin. Also helps to show users that the plugin is working.
	//----------------------------------------------------------------------------------------
	class AboutDialog : public GeDialog
	{
	public:
		Bool CreateLayout();
		Bool InitValues();

	private:
		//----------------------------------------------------------------------------------------
		/// Banner definition for AboutDialog
		//----------------------------------------------------------------------------------------
		class AboutDialogBanner : public GeUserArea
		{
		public:
			Bool GetMinSize(Int32 &w, Int32 &h);
			void DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer &msg);
		};
	};

	//----------------------------------------------------------------------------------------
	/// The CommandData class for the about dialog
	//----------------------------------------------------------------------------------------
	class AboutDialogCommand : public CommandData
	{
	public:
		Bool Execute(BaseDocument *doc);
	};
}

#endif