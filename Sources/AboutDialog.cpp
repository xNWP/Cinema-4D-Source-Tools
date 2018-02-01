// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "AboutDialog.h"

namespace ST
{
	Bool AboutDialog::CreateLayout()
	{
		return LoadDialogResource(ABOUTDLG, nullptr, 0);
	}

	Bool AboutDialog::InitValues()
	{
		// Init Version
		String PluginVers = "Version: " + String(xstr(VERSION_MAJOR)) + "." + String(xstr(VERSION_MINOR)) + VERSION_TAG;
		
		if (!this->SetString(IDS_PLUGIN_VERSION, PluginVers, 0, FLAG_CENTER_HORIZ))
			return false;
		this->Enable(IDS_PLUGIN_VERSION, false);

		// Init Translation (if applicable)
		String TransAuthor;
		if (!this->GetString(IDS_TRANSLATION_AUTHOR, TransAuthor))
			return false;
		else
		{
			if (TransAuthor == "")
			{
				this->HideElement(IDS_TRANSLATION_AUTHOR, true);
				this->HideElement(IDS_TRANSLATION_WEBSITE, true);
			}
		}
		
		// Init banner
		AboutDialogBanner *banner = new AboutDialogBanner();
		if (!this->AttachUserArea(*banner, IDC_ABOUT_DIALOG_BANNER, USERAREA_0))
			return false;
		banner->LayoutChanged();
		banner->Redraw();

		// Init donation buttons
		PayPalDonate *paypal = new PayPalDonate();
		if (!this->AttachUserArea(*paypal, IDC_PAYPAL, USERAREA_0))
			return false;
		paypal->LayoutChanged();
		paypal->Redraw();

		SteamDonate *steam = new SteamDonate();
		if (!this->AttachUserArea(*steam, IDC_STEAM, USERAREA_0))
			return false;
		steam->LayoutChanged();
		steam->Redraw();

		return true;
	}

	Bool AboutDialog::AboutDialogBanner::GetMinSize(Int32 &w, Int32 &h)
	{
		w = 240; h = 60;
		return true;
	}

	void AboutDialog::AboutDialogBanner::DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer &msg)
	{
		BaseBitmap *bmp = BaseBitmap::Alloc();
		Filename imagePath(GeGetPluginPath() + "\\res" + "\\AboutBanner.png");
		bmp->Init(imagePath);

		DrawBitmap(bmp, 0, 0, bmp->GetBw(), bmp->GetBh(), 0, 0, bmp->GetBw(), bmp->GetBh(), BMP_ALLOWALPHA);
	}

	Bool AboutDialog::PayPalDonate::GetMinSize(Int32 &w, Int32 &h)
	{
		w = 100; h = 40;
		return true;
	}

	void AboutDialog::PayPalDonate::DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer &msg)
	{
		BaseBitmap *bmp = BaseBitmap::Alloc();
		Filename imagePath(GeGetPluginPath() + "\\res" + "\\paypal.png");
		bmp->Init(imagePath);

		DrawBitmap(bmp, 0, 0, bmp->GetBw(), bmp->GetBh(), 0, 0, bmp->GetBw(), bmp->GetBh(), BMP_ALLOWALPHA);
	}

	Bool AboutDialog::PayPalDonate::InputEvent(const BaseContainer &msg)
	{
		BaseContainer state = msg;
		if (GetInputState(BFM_INPUT_MOUSE, BFM_INPUT_MOUSELEFT, state))
		{
			OpenURL("http://code.thatnwp.com/PayPalDonate.html");
			// using a redirect in case the link changes :)
		}

		return true;
	}

	Bool AboutDialog::SteamDonate::GetMinSize(Int32 &w, Int32 &h)
	{
		w = 100; h = 40;
		return true;
	}

	void AboutDialog::SteamDonate::DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer &msg)
	{
		BaseBitmap *bmp = BaseBitmap::Alloc();
		Filename imagePath(GeGetPluginPath() + "\\res" + "\\steam.png");
		bmp->Init(imagePath);

		DrawBitmap(bmp, 0, 0, bmp->GetBw(), bmp->GetBh(), 0, 0, bmp->GetBw(), bmp->GetBh(), BMP_ALLOWALPHA);
	}

	Bool AboutDialog::SteamDonate::InputEvent(const BaseContainer &msg)
	{
		BaseContainer state = msg;
		if (GetInputState(BFM_INPUT_MOUSE, BFM_INPUT_MOUSELEFT, state))
		{
			OpenURL("http://code.thatnwp.com/SteamDonate.html");
			// using a redirect in case the link changes :)
		}

		return true;
	}

	Bool AboutDialogCommand::Execute(BaseDocument *doc)
	{
		AboutDialog *adlg = NewObjClear(AboutDialog);
		return adlg->Open(DLG_TYPE_MODAL, ABOUT_ID);
	}
}

Bool RegisterAboutDialog()
{
	ST::AboutDialogCommand *ad_cmd = NewObjClear(ST::AboutDialogCommand);
	return RegisterCommandPlugin(ABOUT_ID, GeLoadString(IDS_PLUGIN_NAME), 0, nullptr, GeLoadString(IDS_PLUGIN_NAME), ad_cmd);
}