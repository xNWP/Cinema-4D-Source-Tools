#ifndef QC_PARSER_H__
#define QC_PARSER_H__

#include "c4d_file.h"
#include "maxon/integer.h"
#include "qcformat.h"

maxon::Bool ParseQC( const Filename& file, QuakeCFormat& qc );

#endif // !QC_PARSER_H__