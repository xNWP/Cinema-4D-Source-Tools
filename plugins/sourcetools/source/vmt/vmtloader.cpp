#include "vmtloader.h"

#include "c4d_symbols.h"
#include "error.h"
#include "fstools.h"
#include "vmtparser.h"

#include "c4d_basechannel.h"
#include "c4d_basedocument.h"
#include "c4d_basematerial.h"
#include "c4d_reflection.h"
#include "c4d_resource.h"
#include "lib_description.h"
#include "mmaterial.h"
#include "xbitmap.h"

Bool VMTLoaderData::Identify(BaseSceneLoader *node, const Filename &name,
                             UChar *probe, Int32 size) {
  // VMT is an ASCII format, we will identify via extension
  return (name.GetSuffix().ToLower() == "vmt") ? true : false;
}

FILEERROR VMTLoaderData::Load(BaseSceneLoader *node, const Filename &name,
                              BaseDocument *doc, SCENEFILTER filterflags,
                              maxon::String *error, BaseThread *bt) {
  using namespace VMTTypes;
  ValveMaterialType vmt;
  if (!ParseVMT(name, vmt))
    return FILEERROR::INVALID;

  Settings config;
  auto Folder = name.GetDirectory();
  config.cdmaterials.push_back(Folder);

  // Look for a materials folder
  while ((Folder = Folder.GetDirectory()).IsPopulated()) {
    if (Folder.GetFileString().ToLower() == "materials") {
      config.cdmaterials.push_back(Folder);
      break;
    }
  }

  auto Mat = VMTLoaderData::CreateVMT(vmt, config);

  auto ObjName = name.GetFile();
  ObjName.ClearSuffix();
  Mat->SetName(ObjName.GetString());
  doc->InsertMaterial(Mat);

  return FILEERROR::NONE;
}

Material *VMTLoaderData::CreateVMT(const ValveMaterialType &vmt,
                                   const Settings &config) {
  using pt = VMTTypes::ParameterType;

  /* Create Material */
  auto Mat = Material::Alloc();

  Mat->SetChannelState(CHANNEL_REFLECTION, false);
  Mat->GetDataInstance()->SetBool(REFLECTION_LAYER_IMPORTED, true);

  /* Color */
  if (vmt.Parameters.find(pt::BASETEXTURE) != std::end(vmt.Parameters)) {
    auto Filepath =
        Filename(std::any_cast<String>(vmt.Parameters.at(pt::BASETEXTURE)));
    Filepath.SetSuffix(config.BitmapExtension);
    if (ResolveLocalFilepath(Filepath, config.cdmaterials)) {
      BaseShader *ColorShader = BaseShader::Alloc(Xbitmap);
      ColorShader->SetParameter(BITMAPSHADER_FILENAME, Filepath,
                                DESCFLAGS_SET::NONE);
      Mat->SetParameter(MATERIAL_COLOR_SHADER, ColorShader,
                        DESCFLAGS_SET::NONE);
      Mat->InsertShader(ColorShader);

      if (vmt.Parameters.find(pt::TRANSLUCENT) != std::end(vmt.Parameters)) {
        if (std::any_cast<bool>(vmt.Parameters.at(pt::TRANSLUCENT))) {
          Mat->SetChannelState(CHANNEL_ALPHA, true);

          BaseShader *AlphaShader = BaseShader::Alloc(Xbitmap);
          AlphaShader->SetParameter(BITMAPSHADER_FILENAME, Filepath,
                                    DESCFLAGS_SET::NONE);
          Mat->SetParameter(MATERIAL_ALPHA_SHADER, AlphaShader,
                            DESCFLAGS_SET::NONE);
          Mat->InsertShader(AlphaShader);
        }
      }
    } else {
      LogError("Failed to resolve basetexture filepath: " +
               Filepath.GetString());
    }
  }

  /* BumpMap */
  if (vmt.Parameters.find(pt::BUMPMAP) != std::end(vmt.Parameters)) {
    /* skip for ssbump */
    bool ssbump = false;
    if (vmt.Parameters.find(pt::SSBUMP) != std::end(vmt.Parameters))
      ssbump = std::any_cast<bool>(vmt.Parameters.at(pt::SSBUMP));

    if (!ssbump) {
      Mat->SetChannelState(CHANNEL_NORMAL, true);

      auto Filepath =
          Filename(std::any_cast<String>(vmt.Parameters.at(pt::BUMPMAP)));
      Filepath.SetSuffix(config.BitmapExtension);

      if (ResolveLocalFilepath(Filepath, config.cdmaterials)) {
        BaseShader *BumpShader = BaseShader::Alloc(Xbitmap);

        BumpShader->SetParameter(BITMAPSHADER_FILENAME, Filepath,
                                 DESCFLAGS_SET::NONE);
        Mat->SetParameter(MATERIAL_NORMAL_SHADER, BumpShader,
                          DESCFLAGS_SET::NONE);
        Mat->InsertShader(BumpShader);
      } else {
        LogError("Failed to resolve bumpmap filepath: " + Filepath.GetString());
      }
    }
  }

  return Mat;
}

NodeData *VMTLoaderData::Create() { return NewObjClear(VMTLoaderData); }

Bool VMTLoaderData::RegisterPlugin() {
  if (!RegisterSceneLoaderPlugin(ID_VMTLOADER,
                                 "Valve Material Type (VMT) Loader"_s, 0,
                                 VMTLoaderData::Create, ""_s))
    return false;

  return true;
}