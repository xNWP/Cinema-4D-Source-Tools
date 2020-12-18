#pragma once

#include "c4d_file.h"
#include "maxon/integer.h"
#include "vmtformat.h"

maxon::Bool ParseVMT( const Filename& file, ValveMaterialType& vmt );