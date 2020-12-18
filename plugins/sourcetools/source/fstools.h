#pragma once

#include "c4d_file.h"
#include <vector>

bool ResolveLocalFilepath(Filename &fp,
                          const std::vector<Filename> &searchdirectories,
                          const Bool &isdir = false);
