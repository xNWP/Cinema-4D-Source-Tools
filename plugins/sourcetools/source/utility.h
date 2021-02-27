#pragma once

#include "c4d_file.h"
#include "c4d_tools.h"
#include <vector>

namespace st
{
	bool ResolveLocalFilepath(Filename& fp, const std::vector<Filename>& searchdirectories, const Bool& isdir = false);

	const maxon::Matrix SrcToC4DTransformMatrix = MatrixScale(Vector(-1.0f, 1.0f, 1.0f)) * MatrixRotX(PI / 2);
}