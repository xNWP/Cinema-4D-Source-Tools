#pragma once

#include "c4d_file.h"
#include "maxon/integer.h"
#include "vmtformat.h"

namespace st::vmt
{
	maxon::Bool ParseVMT(const Filename& file, ValveMaterialType& vmt);
}