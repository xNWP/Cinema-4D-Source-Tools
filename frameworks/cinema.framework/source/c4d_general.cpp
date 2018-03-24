#ifdef __API_INTERN__
	#error "Not in the kernel"
#endif

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "c4d_general.h"
#include "c4d_shader.h"
#include "c4d_file.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"

Bool ParserCache::CopyTo(ParserCache* dest)
{
	return C4DOS.Pr->CopyPCache(this, dest);
}

ParserCache* ParserCache::Alloc(void)
{
	return C4DOS.Pr->AllocPCache();
}

void ParserCache::Free(ParserCache*& p)
{
	C4DOS.Pr->FreePCache(p);
	p = nullptr;
}

Parser* Parser::Alloc(void)
{
	return C4DOS.Pr->Alloc();
}

void Parser::Free(Parser*& pr)
{
	C4DOS.Pr->Free(pr);
	pr = nullptr;
}

Bool Parser::AddVar(const String& str, Float* value, Bool case_sensitive)
{
	return C4DOS.Pr->AddVar(this, &str, value, case_sensitive);
}

Bool Parser::RemoveVar(const String& s, Bool case_sensitive)
{
	return C4DOS.Pr->RemoveVar(this, &s, case_sensitive);
}

Bool Parser::RemoveAllVars(void)
{
	return C4DOS.Pr->RemoveAllVars(this);
}

void Parser::GetParserData(ParserCache* p)
{
	return C4DOS.Pr->GetParserData(this, p);
}

Bool Parser::Init(const String& s, Int32* error, Int32 unit, Int32 angle_unit, Int32 base)
{
	return C4DOS.Pr->Init(this, &s, error, unit, angle_unit, base);
}

Bool Parser::Eval(const String& str, Int32* error, Float* res, Int32 unit, Int32 angletype, Int32 basis)
{
	return C4DOS.Pr->Eval(this, &str, error, res, unit, angletype, basis);
}

Bool Parser::ReEval(Float* result, Int32* error)
{
	return C4DOS.Pr->ReEval(this, result, error);
}

Bool Parser::Calculate(const ParserCache* pdat, Float* result, Int32* error)
{
	return C4DOS.Pr->Calculate(this, pdat, result, error);
}

Bool Parser::AddVarLong(const String& str, Int32* value, Bool case_sensitive)
{
	return C4DOS.Pr->AddVarLong(this, &str, value, case_sensitive);
}

Bool Parser::EvalLong(const String& str, Int32* error, Int32* res, Int32 unit, Int32 basis)
{
	return C4DOS.Pr->EvalLong(this, &str, error, res, unit, basis);
}

Bool Parser::ReEvalLong(Int32* result, Int32* error)
{
	return C4DOS.Pr->ReEvalLong(this, result, error);
}

Bool Parser::CalculateLong(const ParserCache* pdat, Int32* result, Int32* error)
{
	return C4DOS.Pr->CalculateLong(this, pdat, result, error);
}

Bool Parser::Reset(ParserCache* p)
{
	return C4DOS.Pr->Reset(this, p);
}

Bool Parser::GenerateShaderCode(const String& resultVariableName, String* result)
{
	return C4DOS.Pr->GenerateShaderCode(this, resultVariableName, result);
}

Bool Parser::GenerateShaderCodeFromCache(const ParserCache* pdat, const String& resultVariableName, String* result)
{
	return C4DOS.Pr->GenerateShaderCodeFromCache(this, pdat, resultVariableName, result);
}

void GeAddBackgroundHandler(BackgroundHandler* handler, void* tdata, Int32 typeclass, Int32 priority)
{
	C4DOS.Ge->AddBackgroundHandler(handler, tdata, typeclass, priority);
}

Bool GeRemoveBackgroundHandler(void* tdata, Int32 typeclass)
{
	return C4DOS.Ge->RemoveBackgroundHandler(tdata, typeclass);
}

void GeStopBackgroundThreads(Int32 typeclass, BACKGROUNDHANDLERFLAGS flags)
{
	C4DOS.Ge->StopBackgroundThreads(typeclass, flags);
}

Bool GeCheckBackgroundThreadsRunning(Int32 typeclass, Bool all)
{
	return C4DOS.Ge->CheckBackgroundThreadsRunning(typeclass, all);
}

void GeProcessBackgroundThreads(Int32 typeclass)
{
	C4DOS.Ge->ProcessBackgroundThreads(typeclass);
}

void GeShowMouse(Int32 v)
{
	C4DOS.Ge->ShowMouse(v);
}

Bool GeGetScreenDimensions(Int32 x, Int32 y, Bool whole_screen, Int32* sx1, Int32* sy1, Int32* sx2, Int32* sy2)
{
	return C4DOS.Ge->GetScreenDimensions(x, y, whole_screen, sx1, sy1, sx2, sy2);
}

String GeGetLineEnd(void)
{
	String str;
	C4DOS.Ge->GetLineEnd(&str);
	return str;
}

Int32 GeGetDefaultFPS(void)
{
	return C4DOS.Ge->GetDefaultFPS();
}

GEMB_R GeOutString(const String& str, GEMB flags)
{
	return C4DOS.Ge->OutString(&str, flags);
}

OPERATINGSYSTEM GeGetCurrentOS(void)
{
	return C4DOS.Ge->GetCurrentOS();
}

BYTEORDER GeGetByteOrder(void)
{
	return C4DOS.Ge->GetByteOrder();
}

void GeGetGray(Int32* r, Int32* g, Int32* b)
{
	C4DOS.Ge->GetGray(r, g, b);
}

Bool GeChooseColor(Vector* col, Int32 flags)
{
	return C4DOS.Ge->ChooseColor(col, flags);
}

Bool GeOpenHTML(const String& webaddress)
{
	return C4DOS.Ge->OpenHTML(webaddress);
}

Bool GeChooseFont(BaseContainer* bc)
{
	return C4DOS.Ge->ChooseFont(bc);
}

void GeGetSerialInfo(SERIALINFO type, SerialInfo* si)
{
	C4DOS.Ge->GetSerialInfo(type, &si->nr, &si->name, &si->organization, &si->street, &si->city, &si->country);
}

VERSIONTYPE GeGetVersionType(void)
{
	return C4DOS.Ge->GetVersionType();
}

SYSTEMINFO GeGetSystemInfo(void)
{
	return C4DOS.Ge->GetSystemInfo();
}

Bool GeRegisterPlugin(PLUGINTYPE type, Int32 id, const String& str, void* data, Int32 datasize)
{
	return C4DOS.Ge->RegisterPlugin(API_VERSION, type, id, &str, data, datasize);
}

void GePrint(const String& str)
{
	C4DOS.Ge->Print(str);
}

void GeConsoleOut(const String& str)
{
	String s = String("\x01") + str;
	C4DOS.Ge->Print(s);
}

void SetMousePointer(Int32 l)
{
	C4DOS.Ge->SetMousePointer(l);
}

Bool ShowBitmap(const Filename& fn)
{
	return C4DOS.Ge->ShowBitmap1(&fn);
}

Bool ShowBitmap(BaseBitmap* bm)
{
	return C4DOS.Ge->ShowBitmap2(bm);
}

void StopAllThreads(void)
{
	C4DOS.Ge->StopAllThreads();
}

Bool ShutdownThreads(Bool shutdown)
{
	return C4DOS.Ge->ShutdownThreads(shutdown);
}

void StatusClear(void)
{
	C4DOS.Ge->StatusClear();
}

void StatusSetSpin(void)
{
	C4DOS.Ge->StatusSetSpin();
}

void StatusSetBar(Int32 p)
{
	C4DOS.Ge->StatusSetBar(p);
}

void StatusSetText(const String& str)
{
	C4DOS.Ge->StatusSetText(&str);
}

void StatusNetClear(void)
{
	C4DOS.Ge->StatusNetClear();
}

void StatusSetNetLoad(STATUSNETSTATE status)
{
	C4DOS.Ge->StatusSetNetLoad(status);
}

void StatusSetNetBar(Int32 p, const GeData& dat)
{
	C4DOS.Ge->StatusSetNetBar(p, dat);
}

void StatusSetNetText(const String& str)
{
	C4DOS.Ge->StatusSetNetText(&str);
}

void SpecialEventAdd(Int32 messageid, UInt p1, UInt p2)
{
	C4DOS.Ge->SpecialEventAdd(messageid, p1, p2);
}

void EventAdd(EVENT flags)
{
	C4DOS.Ge->EventAdd(flags);
}

Bool GeSyncMessage(Int32 messageid, Int32 destid, UInt p1, UInt p2)
{
	return C4DOS.Ge->SyncMessage(messageid, destid, p1, p2);
}

Bool DrawViews(DRAWFLAGS flags, BaseDraw* bd)
{
	return C4DOS.Ge->DrawViews(flags, bd);
}

Bool SendModelingCommand(Int32 command, ModelingCommandData& data)
{
	return C4DOS.Ge->SendModelingCommand(command, data);
}

Filename GetGlobalTexturePath(Int32 i)
{
	Filename fn;
	C4DOS.Ge->GetGlobalTexturePath(i, &fn);
	return fn;
}

void SetGlobalTexturePath(Int32 i, const Filename& fn)
{
	C4DOS.Ge->SetGlobalTexturePath(i, &fn);
}

Bool IsInSearchPath(const Filename& texfilename, const Filename& docpath)
{
	return C4DOS.Ge->IsInSearchPath(texfilename, docpath);
}

Bool GenerateTexturePath(const Filename& docpath, const Filename& srcname, const Filename& suggestedfolder, Filename* dstname, NetRenderService* service, BaseThread* bt)
{
	return C4DOS.Ge->GenerateTexturePath(docpath, srcname, suggestedfolder, dstname, service, bt);
}

void FlushTexture(const Filename& docpath, const String& name, const Filename& suggestedfolder)
{
	C4DOS.Ge->FlushTexture(&docpath, &name, suggestedfolder);
}

void FlushUnusedTextures(void)
{
	C4DOS.Ge->FlushUnusedTextures();
}

BaseContainer* GetToolPluginData(BaseDocument* doc, Int32 id)
{
	return C4DOS.Ge->GetToolPluginData(doc, id);
}

BaseContainer* GetWorldPluginData(Int32 id)
{
	return C4DOS.Ge->GetWorldPluginData(id);
}

Bool SetWorldPluginData(Int32 id, const BaseContainer& bc, Bool add)
{
	return C4DOS.Ge->SetWorldPluginData(id, &bc, add);
}

void SaveWorldPreferences()
{
	C4DOS.Ge->SaveWorldPreferences();
}

BaseContainer GetWorldContainer(void)
{
	BaseContainer bc;
	C4DOS.Ge->GetWorldContainer(&bc);
	return bc;
}

BaseContainer* GetWorldContainerInstance(void)
{
	return C4DOS.Ge->GetWorldContainerInstance();
}

void SetWorldContainer(const BaseContainer& bc)
{
	C4DOS.Ge->SetWorldContainer(&bc);
}

Vector GetViewColor(Int32 colid)
{
	return C4DOS.Ge->GetColor(colid);
}

void SetViewColor(Int32 colid, const Vector& col)
{
	C4DOS.Ge->SetViewColor(colid, col);
}

void ErrorStringDialog(CHECKVALUERANGE type, Float x, Float y, CHECKVALUEFORMAT is)
{
	C4DOS.Ge->ErrorStringDialog(type, x, y, is);
}

Bool ReadPluginInfo(Int32 pluginid, void* buffer, Int32 size)
{
	return C4DOS.Ge->ReadPluginInfo(pluginid, (Char*)buffer, size);
}

Bool WritePluginInfo(Int32 pluginid, void* buffer, Int32 size)
{
	return C4DOS.Ge->WritePluginInfo(pluginid, (Char*)buffer, size);
}

Bool ReadRegInfo(Int32 pluginid, void* buffer, Int32 size)
{
	return C4DOS.Ge->ReadPluginReg(pluginid, (Char*)buffer, size);
}

Bool WriteRegInfo(Int32 pluginid, void* buffer, Int32 size)
{
	return C4DOS.Ge->WritePluginReg(pluginid, (Char*)buffer, size);
}

Bool GeGetMovieInfo(const Filename& fn, Int32* frames, Float* fps)
{
	return C4DOS.Ge->GetMovieInfo(&fn, frames, fps);
}

Bool GeRegistryAdd(Int32 sub_id, REGISTRYTYPE main_id, void* data)
{
	return C4DOS.Ge->RegistryAdd(sub_id, main_id, data);
}

Bool GeRegistryRemove(Int32 sub_id, REGISTRYTYPE main_id)
{
	return C4DOS.Ge->RegistryRemove(sub_id, main_id);
}

Registry* GeRegistryFind(Int32 sub_id, REGISTRYTYPE main_id)
{
	return C4DOS.Ge->RegistryFind(sub_id, main_id);
}

Registry* GeRegistryGetLast(REGISTRYTYPE main_id)
{
	return C4DOS.Ge->RegistryGetLast(main_id);
}

Registry* GeRegistryGetFirst(REGISTRYTYPE main_id)
{
	return C4DOS.Ge->RegistryGetFirst(main_id);
}

Bool GeRegistryGetAutoID(Int32* id)
{
	return C4DOS.Ge->RegistryGetAutoID(id);
}

REGISTRYTYPE Registry::GetMainID(void)
{
	REGISTRYTYPE main_id;
	Int32				 sub_id;
	void*				 data;
	if (!C4DOS.Ge->RegistryGetData(this, &main_id, &sub_id, &data))
		return REGISTRYTYPE_ANY;
	return main_id;
}

Int32 Registry::GetSubID(void)
{
	REGISTRYTYPE main_id;
	Int32				 sub_id;
	void*				 data;
	if (!C4DOS.Ge->RegistryGetData(this, &main_id, &sub_id, &data))
		return 0;
	return sub_id;
}

void* Registry::GetData(void)
{
	REGISTRYTYPE main_id;
	Int32				 sub_id;
	void*				 data;
	if (!C4DOS.Ge->RegistryGetData(this, &main_id, &sub_id, &data))
		return nullptr;
	return data;
}

Bool RenameDialog(String* str)
{
	return C4DOS.Ge->RenameDialog(str);
}

Bool LassoSelection::Start(GeDialog& dlg, Int32 mode, Int32 start_x, Int32 start_y, Int32 start_button, Int32 sx1, Int32 sy1, Int32 sx2, Int32 sy2)
{
	return C4DOS.Cd->LSStart(this, (CBaseFrame*)dlg.Get(), mode, start_x, start_y, start_button, sx1, sy1, sx2, sy2);
}

Bool LassoSelection::Start(GeUserArea& ua, Int32 mode, Int32 start_x, Int32 start_y, Int32 start_button, Int32 sx1, Int32 sy1, Int32 sx2, Int32 sy2)
{
	return C4DOS.Cd->LSStart(this, (CBaseFrame*)ua.Get(), mode, start_x, start_y, start_button, sx1, sy1, sx2, sy2);
}

Bool LassoSelection::Start(EditorWindow* win, Int32 mode, Int32 start_x, Int32 start_y, Int32 start_button, Int32 sx1, Int32 sy1, Int32 sx2, Int32 sy2)
{
	return C4DOS.Cd->LSStart(this, (CBaseFrame*)win, mode, start_x, start_y, start_button, sx1, sy1, sx2, sy2);
}

Bool LassoSelection::GetRectangle(Float& x1, Float& y1, Float& x2, Float& y2)
{
	return C4DOS.Cd->LSGetRectangle(this, x1, y1, x2, y2);
}

Bool LassoSelection::CheckSingleClick()
{
	return C4DOS.Cd->LSCheckSingleClick(this);
}

Bool LassoSelection::Test(Int32 x, Int32 y)
{
	return C4DOS.Cd->LSTest(this, x, y);
}

Bool LassoSelection::TestPolygon(const Vector& pa, const Vector& pb, const Vector& pc, const Vector& pd)
{
	return C4DOS.Cd->LSTestPolygon(this, pa, pb, pc, pd);
}

Int32 LassoSelection::GetMode()
{
	return C4DOS.Cd->LSGetMode(this);
}

LassoSelection* LassoSelection::Alloc()
{
	return C4DOS.Cd->LSAlloc();
}

void LassoSelection::Free(LassoSelection*& ls)
{
	C4DOS.Cd->LSFree(ls);
	ls = nullptr;
}

void FindInManager(BaseList2D* bl)
{
	C4DOS.Ge->FindInManager(bl);
}

void GeSleep(Int32 milliseconds)
{
	C4DOS.Ge->GeSleep(milliseconds);
}

Bool GeIsMainThread()
{
	return C4DOS.Ge->IsMainThread();
}

Bool GeIsMainThreadAndNoDrawThread()
{
	return C4DOS.Ge->IsMainThreadAndNoDrawThread();
}

Bool GeIsActiveToolEnabled(void)
{
	return C4DOS.Ge->IsActiveToolEnabled();
}

GeListHead* GetScriptHead(Int32 type)
{
	return C4DOS.Ge->GetScriptHead(type);
}

Bool GetCommandLineArgs(C4DPL_CommandLineArgs& args)
{
	return C4DOS.Ge->GetCommandLineArgs(args);
}

Int32 GetDynamicScriptID(BaseList2D* bl)
{
	return C4DOS.Ge->GetDynamicScriptID(bl);
}

Bool GeGetLanguage(Int32 index, String* extension, String* name, Bool* default_language)
{
	return C4DOS.Ge->GetLanguage(index, extension, name, default_language);
}

Filename GeFilterSetSuffix(const Filename& name, Int32 id)
{
	return C4DOS.Ge->FilterSetSuffix(name, id);
}

IDENTIFYFILE GeIdentifyFile(const Filename& name, UChar* probe, Int32 probesize, IDENTIFYFILE recognition, BasePlugin** bp)
{
	return C4DOS.Ge->IdentifyFile(name, probe, probesize, recognition, bp);
}

GeData SendCoreMessage(Int32 coreid, const BaseContainer& msg, Int32 eventid)
{
	return C4DOS.Ge->SendCoreMessage(coreid, msg, eventid);
}

String GetMacModel(const String& machinemodel)
{
	return C4DOS.Ge->GetMacModel(machinemodel);
}

BaseContainer GetMachineFeatures(MachineFeaturesType type)
{
	GeData dat = SendCoreMessage(COREMSG_CINEMA, BaseContainer(COREMSG_CINEMA_GETMACHINEFEATURES), (Int32)type);
	if (!dat.GetContainer())
		return BaseContainer();
	return *dat.GetContainer();
}

Bool GePluginMessage(Int32 id, void* data)
{
	return C4DOS.Ge->PluginMessage(id, data);
}

Bool CheckIsRunning(CHECKISRUNNING type)
{
	return C4DOS.Ge->CheckIsRunning(type);
}

String GeGetDefaultFilename(Int32 id)
{
	return C4DOS.Ge->GetDefaultFilename(id).GetString();
}

String GetObjectName(Int32 type)
{
	return C4DOS.Ge->GetObjectName(type);
}

String GetTagName(Int32 type)
{
	return C4DOS.Ge->GetTagName(type);
}

Int32 GetObjectType(const String& name)
{
	return C4DOS.Ge->GetObjectType(name);
}

Int32 GetTagType(const String& name)
{
	return C4DOS.Ge->GetTagType(name);
}

Bool GeGetMemoryStat(BaseContainer& stat)
{
	return C4DOS.Ge->GeGetMemoryStat(stat);
}


Bool PopupEditText(Int32 screenx, Int32 screeny, Int32 width, Int32 height, const String& changeme, Int32 flags, PopupEditTextCallback* func, void* userdata)
{
	return C4DOS.Ge->PopupEditText(screenx, screeny, width, height, changeme, flags, func, userdata);
}

void StartEditorRender(Bool active_only, Bool raybrush, Int32 x1, Int32 y1, Int32 x2, Int32 y2, BaseThread* bt, BaseDraw* bd, Bool newthread)
{
	C4DOS.Ge->StartEditorRender(active_only, raybrush, x1, y1, x2, y2, bt, bd, newthread);
}

String FormatNumber(const GeData& val, Int32 format, Int32 fps, Bool bUnit)
{
	return C4DOS.Ge->FormatNumber(val, format, fps, bUnit, nullptr);
}

GeData StringToNumber(const String& text, Int32 format, Int32 fps, const LENGTHUNIT* lengthunit)
{
	return C4DOS.Ge->StringToNumber(text, format, fps, lengthunit);
}

Int32	GeDebugSetFloatingPointChecks(Int32 on)
{
	return C4DOS.Ge->GeDebugSetFloatingPointChecks(on);
}

void GeDebugOut(const Char* s, ...)
{
#ifdef MAXON_TARGET_DEBUG
	va_list arp;
	va_start(arp, s);

	Char t[2048];

	vsprintf_safe(t, sizeof(t), s, arp);
	C4DOS.Ge->GeDebugOut("%s", t);

	va_end(arp);
#endif
}

String GeGetDegreeChar()
{
	return C4DOS.Ge->GeGetDegreeChar();
}

String GeGetPercentChar()
{
	return C4DOS.Ge->GeGetPercentChar();
}

void CallCommand(Int32 id, Int32 subid)
{
	if (!GeIsMainThreadAndNoDrawThread())
		return;
	BaseContainer msg(COREMSG_CINEMA_EXECUTEEDITORCOMMAND);
	msg.SetInt32(COREMSG_CINEMA_EXECUTEEDITORCOMMAND, id);
	msg.SetInt32(COREMSG_CINEMA_EXECUTESUBID, subid);
	SendCoreMessage(COREMSG_CINEMA, msg, 0);
}

String GetCommandName(Int32 id)
{
	if (!GeIsMainThreadAndNoDrawThread())
		return String();
	BaseContainer msg(COREMSG_CINEMA_GETCOMMANDNAME);
	msg.SetInt32(COREMSG_CINEMA_GETCOMMANDNAME, id);
	return SendCoreMessage(COREMSG_CINEMA, msg, 0).GetString();
}

String GetCommandHelp(Int32 id)
{
	if (!GeIsMainThreadAndNoDrawThread())
		return String();
	BaseContainer msg(COREMSG_CINEMA_GETCOMMANDHELP);
	msg.SetInt32(COREMSG_CINEMA_GETCOMMANDHELP, id);
	return SendCoreMessage(COREMSG_CINEMA, msg, 0).GetString();
}

Bool IsCommandEnabled(Int32 id)
{
	if (!GeIsMainThreadAndNoDrawThread())
		return false;
	BaseContainer msg(COREMSG_CINEMA_GETCOMMANDENABLED);
	msg.SetInt32(COREMSG_CINEMA_GETCOMMANDENABLED, id);
	return SendCoreMessage(COREMSG_CINEMA, msg, 0).GetInt32();
}

Bool IsCommandChecked(Int32 id)
{
	if (!GeIsMainThreadAndNoDrawThread())
		return false;
	BaseContainer msg(COREMSG_CINEMA_GETCOMMANDCHECKED);
	msg.SetInt32(COREMSG_CINEMA_GETCOMMANDCHECKED, id);
	return SendCoreMessage(COREMSG_CINEMA, msg, 0).GetInt32();
}

Bool SendMailAvailable()
{
	return C4DOS.Ge->SendMailAvailable();
}

Bool SendMail(const String& t_subject, const String* t_to, const String* t_cc, const String* t_bcc, Filename* t_attachments, const String& t_body, Int32 flags)
{
	return C4DOS.Ge->SendMail(t_subject, t_to, t_cc, t_bcc, t_attachments, t_body, flags);
}

Bool GetSystemEnvironmentVariable(const String& varname, String& result)
{
	return C4DOS.Ge->GetSystemEnvironmentVariable(varname, result);
}

Int32 GetShortcutCount()
{
	return C4DOS.Ge->GetShortcutCount();
}

BaseContainer GetShortcut(Int32 index)
{
	return C4DOS.Ge->GetShortcut(index);
}

Bool AddShortcut(const BaseContainer& bc)
{
	return C4DOS.Ge->AddShortcut(bc);
}

Bool RemoveShortcut(Int32 index)
{
	return C4DOS.Ge->RemoveShortcut(index);
}

Bool LoadShortcutSet(const Filename& fn, Bool add)
{
	return C4DOS.Ge->LoadShortcutSet(fn, add);
}

Bool SaveShortcutSet(const Filename& fn)
{
	return C4DOS.Ge->SaveShortcutSet(fn);
}

Int32 FindShortcutsFromID(Int32 pluginid, Int32* indexarray, Int32 maxarrayelements)
{
	return C4DOS.Ge->FindShortcutsFromID(pluginid, indexarray, maxarrayelements);
}

Int32 FindShortcuts(const BaseContainer& scut, Int32* idarray, Int32 maxarrayelements)
{
	return C4DOS.Ge->FindShortcuts(scut, idarray, maxarrayelements);
}

Bool CheckCommandShortcut(Int32 id, Int32 key, Int32 qual)
{
	return C4DOS.Ge->CheckCommandShortcut(id, key, qual);
}

void InsertCreateObject(BaseDocument* doc, BaseObject* op, BaseObject* activeobj)
{
	C4DOS.Ge->InsertCreateObject(doc, op, activeobj);
}

UInt32 GeGetCinemaInfo(CINEMAINFO info)
{
	return (*C4DOS.Ge->GetCinemaInfo)(info);
}

void CopyToClipboard(const String& text)
{
	(*C4DOS.Ge->CopyToClipboard)(text);
}

void CopyToClipboard(BaseBitmap* map, Int32 ownerid)
{
	(*C4DOS.Ge->CopyToClipboardB)(map, ownerid);
}

Bool GetStringFromClipboard(String* txt)
{
	return (*C4DOS.Ge->GetStringFromClipboard)(txt);
}

Bool GetBitmapFromClipboard(BaseBitmap* map)
{
	return (*C4DOS.Ge->GetBitmapFromClipboard)(map);
}

CLIPBOARDTYPE GetClipboardType(void)
{
	return (*C4DOS.Ge->GetClipboardType)();
}

Int32 GetC4DClipboardOwner(void)
{
	return (*C4DOS.Ge->GetC4DClipboardOwner)();
}

Bool AskForAdministratorPrivileges(const String& msg, const String& caption, Bool allowsuperuser, void** token)
{
	return (*C4DOS.Ge->AskForAdministratorPrivileges)(msg, caption, allowsuperuser, token);
}

void EndAdministratorPrivileges()
{
	(*C4DOS.Ge->EndAdministratorPrivileges)();
}

void RestartApplication(const Utf16Char* param, Int32 exitcode, const Utf16Char** path)
{
	(*C4DOS.Ge->RestartApplication)(param, exitcode, path);
}

void SetExitCode(Int32 exitCode)
{
	(*C4DOS.Ge->SetExitCode)(exitCode);
}

void GeDebugOut(const String& s)
{
#ifdef MAXON_TARGET_DEBUG
	Char* c = s.GetCStringCopy();
	if (c)
	{
		GeDebugOut(c);
		DeleteMem(c);
	}
#endif
}

void BrowserLibraryPopup(Int32 mx, Int32 my, Int32 defw, Int32 defh, Int32 pluginwindowid, Int32 presettypeid, void* userdata, BrowserPopupCallback callback)
{
	return C4DOS.Ge->BrowserLibraryPopup(mx, my, defw, defh, pluginwindowid, presettypeid, userdata, callback);
}

void GeUpdateUI()
{
	C4DOS.Ge->GeUpdateUI();
}

const BaseBitmap* GetCursorBitmap(Int32 type, Int32& hotspotx, Int32& hotspoty)
{
	return C4DOS.Ge->GetCursorBitmap(type, hotspotx, hotspoty);
}

ModelingCommandData::~ModelingCommandData()
{
	AtomArray::Free(result);
}
