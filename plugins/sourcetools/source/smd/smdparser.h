#ifndef SMD_PARSER_H__
#define SMD_PARSER_H__

#include "c4d_file.h"
#include "maxon/integer.h"
#include "smdformat.h"

maxon::Bool ParseSMD( const Filename &file, StudiomdlData &smd );

#endif // !SMD_PARSER_H__