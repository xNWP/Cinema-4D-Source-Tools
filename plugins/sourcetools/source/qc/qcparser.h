#pragma once

#include "c4d_file.h"
#include "maxon/integer.h"
#include "qcformat.h"

namespace st::qc
{
	maxon::Bool ParseQC(const Filename& file, QuakeCFormat& qc);
}