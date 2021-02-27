#pragma once

#include "c4d_file.h"
#include "maxon/integer.h"
#include "camioformat.h"

namespace st::camio
{
	maxon::Bool ParseCamIO(const Filename& filename, CamIO& camio);

	maxon::Bool CheckCamIOFileHeader(const Filename& filename);
}