#pragma once

#include "c4d_file.h"
#include "maxon/integer.h"
#include "smdformat.h"

maxon::Bool ParseSMD(const Filename &file, StudiomdlData &smd);