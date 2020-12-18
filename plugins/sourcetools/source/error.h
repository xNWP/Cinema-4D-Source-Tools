#pragma once

#include <c4d_help.h>
#include <string>

namespace st {
void iLog(const String &msg);
void iLogError(const String &msg, const char *FILE, const char *FUNC,
               UInt LINE);
void iLogErrorWhat(const String &WHAT, const char *FILE, const char *FUNC,
                   UInt LINE);
} // namespace st

#define Log(MSG) st::iLog(MSG)
#define LogError(MSG) st::iLogError(MSG, __FILE__, __func__, __LINE__)
#define LogErrorWhat(WHAT)                                                     \
  st::iLogErrorWhat(WHAT.what(), __FILE__, __func__, __LINE__)