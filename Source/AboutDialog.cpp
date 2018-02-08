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
		banner = NewObj(AboutDialogBanner);
		if (!this->AttachUserArea(*banner, IDC_ABOUT_DIALOG_BANNER, USERAREA_0))
			return false;
		banner->LayoutChanged();
		banner->Redraw();

		// Init donation buttons
		paypal = NewObj(PayPalDonate);
		if (!this->AttachUserArea(*paypal, IDC_PAYPAL, USERAREA_0))
			return false;
		paypal->LayoutChanged();
		paypal->Redraw();

		steam = NewObj(SteamDonate);
		if (!this->AttachUserArea(*steam, IDC_STEAM, USERAREA_0))
			return false;
		steam->LayoutChanged();
		steam->Redraw();

		// Set initial tab to about page
		this->SetInt32(IDT_TAB_GROUP, IDT_ABOUT);

		// Set settings according to user file.
		tinyxml2::XMLDocument *M_DOC = NewObj(tinyxml2::XMLDocument);
		String StrLoc = GeGetPluginPath().GetString();
		StrLoc += "\\"; StrLoc += USER_CONFIG_LOC;
		char *ChaLoc = StrLoc.GetCStringCopy();
		tinyxml2::XMLError error = M_DOC->LoadFile(ChaLoc);

		if (error != tinyxml2::XML_SUCCESS)
			MessageDialog(GeLoadString(IDS_CRITICAL_ERROR));

		String probe;

		// Auto-Update
		if (!GetUserConfig(M_DOC, CHECK_FOR_UPDATES, probe))
			MessageDialog(GeLoadString(IDS_CRITICAL_ERROR));
		if (probe == "true")
			this->SetBool(IDC_AUTO_UPDATE, true);
		else
			this->SetBool(IDC_AUTO_UPDATE, false);

		DeleteObj(M_DOC);
		DeleteMem(ChaLoc);

		return true;
	}

	Bool AboutDialog::Command(Int32 id, const BaseContainer &msg)
	{
		// Save Settings
		if (id == IDC_SAVE_SETTINGS)
		{
			tinyxml2::XMLDocument *M_DOC = NewObj(tinyxml2::XMLDocument);
			String StrLoc = GeGetPluginPath().GetString();
			StrLoc += "\\"; StrLoc += USER_CONFIG_LOC;
			char *ChaLoc = StrLoc.GetCStringCopy();
			tinyxml2::XMLError error = M_DOC->LoadFile(ChaLoc);

			if (error != tinyxml2::XML_SUCCESS)
				MessageDialog(GeLoadString(IDS_CRITICAL_ERROR));

			Bool bProbe;

			// Auto-Update
			this->GetBool(IDC_AUTO_UPDATE, bProbe);
			if (bProbe)
				SetUserConfig(M_DOC, CHECK_FOR_UPDATES, "true");
			else
				SetUserConfig(M_DOC, CHECK_FOR_UPDATES, "false");

			M_DOC->SaveFile(ChaLoc);
			DeleteObj(M_DOC);
			DeleteMem(ChaLoc);
			MessageDialog(GeLoadString(IDS_SETTINGS_SAVED));

			return true;
		}

		return true;
	}

	void AboutDialog::DestroyWindow()
	{
		DeleteObj(banner);
		DeleteObj(paypal);
		DeleteObj(steam);
	}

	AboutDialog::AboutDialogBanner::~AboutDialogBanner()
	{
		BaseBitmap::Free(bmp);
	}

	Bool AboutDialog::AboutDialogBanner::GetMinSize(Int32 &w, Int32 &h)
	{
		w = 240; h = 60;
		return true;
	}

	void AboutDialog::AboutDialogBanner::DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer &msg)
	{
		bmp = BaseBitmap::Alloc();
		Filename imagePath(GeGetPluginPath() + "\\res" + "\\AboutBanner.png");
		bmp->Init(imagePath);

		DrawBitmap(bmp, 0, 0, bmp->GetBw(), bmp->GetBh(), 0, 0, bmp->GetBw(), bmp->GetBh(), BMP_ALLOWALPHA);
	}

	AboutDialog::PayPalDonate::~PayPalDonate()
	{
		BaseBitmap::Free(bmp);
	}

	Bool AboutDialog::PayPalDonate::GetMinSize(Int32 &w, Int32 &h)
	{
		w = 100; h = 40;
		return true;
	}

	void AboutDialog::PayPalDonate::DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer &msg)
	{
		bmp = BaseBitmap::Alloc();
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

	AboutDialog::SteamDonate::~SteamDonate()
	{
		BaseBitmap::Free(bmp);
	}

	Bool AboutDialog::SteamDonate::GetMinSize(Int32 &w, Int32 &h)
	{
		w = 100; h = 40;
		return true;
	}

	void AboutDialog::SteamDonate::DrawMsg(Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer &msg)
	{
		bmp = BaseBitmap::Alloc();
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
		adlg = NewObjClear(AboutDialog);
		if (!adlg->Open(DLG_TYPE_MODAL, ABOUT_ID))
			return false;

		DeleteObj(adlg);
		return true;
	}
}

Bool RegisterAboutDialog()
{
	ST::AboutDialogCommand *ad_cmd = NewObjClear(ST::AboutDialogCommand);
	return RegisterCommandPlugin(ABOUT_ID, GeLoadString(IDS_PLUGIN_NAME), 0, nullptr, GeLoadString(IDS_PLUGIN_NAME), ad_cmd);
}