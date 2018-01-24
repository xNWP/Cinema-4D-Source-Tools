#include "AboutDialog.h"

namespace ST
{
	Bool AboutDialog::CreateLayout()
	{
		return LoadDialogResource(ABOUTDLG, nullptr, 0);
	}

	Bool AboutDialog::InitValues()
	{
		String PluginVers = "Version: " + String(xstr(VERSION_MAJOR)) + "." + String(xstr(VERSION_MINOR)) + String(xstr(VERSION_TAG));
		
		if (!this->SetString(IDS_PLUGIN_VERSION, PluginVers, 0, FLAG_CENTER_HORIZ))
			return false;

		AboutDialogBanner *banner = new AboutDialogBanner();
		if (!this->AttachUserArea(*banner, IDC_ABOUT_DIALOG_BANNER, USERAREA_0))
			return false;
		banner->LayoutChanged();
		banner->Redraw();

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