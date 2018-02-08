// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_ABOUT_DIALOG_H
#define ST_ABOUT_DIALOG_H

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
		Bool Command(Int32 id, const BaseContainer &msg);
		void DestroyWindow();

	private:
		class AboutDialogBanner;
		AboutDialogBanner *banner;
		class PayPalDonate;
		PayPalDonate *paypal;
		class SteamDonate;
		SteamDonate *steam;

		//----------------------------------------------------------------------------------------
		/// Banner definition for AboutDialog
		//----------------------------------------------------------------------------------------
		class AboutDialogBanner : public GeUserArea
		{
		public:
			~AboutDialogBanner();
			Bool GetMinSize(Int32 &w, Int32 &h);
			void DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer &msg);

		private:
			BaseBitmap *bmp;
		};

		//----------------------------------------------------------------------------------------
		/// PayPal Donate Button definition for AboutDialog
		//----------------------------------------------------------------------------------------
		class PayPalDonate : public GeUserArea
		{
		public:
			~PayPalDonate();
			Bool GetMinSize(Int32 &w, Int32 &h);
			void DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer &msg);
			Bool InputEvent(const BaseContainer &msg);

		private:
			BaseBitmap *bmp;
		};

		//----------------------------------------------------------------------------------------
		/// Steam Donate Button definition for AboutDialog
		//----------------------------------------------------------------------------------------
		class SteamDonate : public GeUserArea
		{
		public:
			~SteamDonate();
			Bool GetMinSize(Int32 &w, Int32 &h);
			void DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer &msg);
			Bool InputEvent(const BaseContainer &msg);

		private:
			BaseBitmap *bmp;
		};
	};

	//----------------------------------------------------------------------------------------
	/// The CommandData class for the about dialog
	//----------------------------------------------------------------------------------------
	class AboutDialogCommand : public CommandData
	{
	public:
		Bool Execute(BaseDocument *doc);

	private:
		AboutDialog *adlg;
	};
}

#endif