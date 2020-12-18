#include "c4d_plugin.h"
#include "c4d_resource.h"

#include "qc/qcloader.h"
#include "smd/smdloader.h"
#include "vmt/vmtloader.h"
#include "vtf/vtfloader.h"

#include "error.h"

#define SOURCETOOLS_VERSION_MAJOR 0
#define SOURCETOOLS_VERSION_MINOR 90
#define SOURCETOOLS_VERSION_TAG "dev"

Bool PluginStart() {
  // VTF Loader
  if (!VTFLoaderData::RegisterPlugin()) {
    LogError("Failed to register VTF loader.");
    return false;
  }

  // SMD Loader
  if (!SMDLoaderData::RegisterPlugin()) {
    LogError("Failed to register SMD loader.");
    return false;
  }

  // QC Loader
  if (!QCLoaderData::RegisterPlugin()) {
    LogError("Failed to register QC loader.");
    return false;
  }

  // VMT Loader
  if (!VMTLoaderData::RegisterPlugin()) {
    LogError("Failed to register VMT loader.");
    return false;
  }

  Log("Loaded all sourcetools modules.");
  String VersionMessage =
      "Version: "_s + maxon::ToString(SOURCETOOLS_VERSION_MAJOR, nullptr) +
      "."_s + maxon::ToString(SOURCETOOLS_VERSION_MINOR, nullptr) +
      maxon::ToString(SOURCETOOLS_VERSION_TAG, nullptr);
#ifdef _DEBUG
  VersionMessage += "-debug";
#endif
#ifdef ST_PROFILING
  VersionMessage += "-profiling";
#endif
  Log(VersionMessage);

  return true;
}

void PluginEnd() {}

Bool PluginMessage(Int32 id, void *data) {
  switch (id) {
  case C4DPL_INIT_SYS: {
    if (g_resource.Init() == false) {
      LogError("Failed to load resources.");
      return false;
    }
  }
  }

  return true;
}