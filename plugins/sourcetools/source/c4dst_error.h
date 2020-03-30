#ifndef SOURCETOOLS_ERROR_H__
#define SOURCETOOLS_ERROR_H__

#include "debugdiagnostics.h"

#if(_DEBUG)
	#define Log( MSG ) DiagnosticOutput( "@ @: @", __DATE__, __TIME__, MSG );
	#define LogError( MSG ) DiagnosticOutput( "@ @ FILE: @ FN: @ - @", __DATE__, __TIME__, __FILE__, __func__, MSG );
	#define LogErrorWhat( WHAT ) DiagnosticOutput( "@ @ FILE: @ FN: @ what(): @", __DATE__, __TIME__, __FILE__, __func__, WHAT.what() );
#else
	#define Log( MSG )
	#define LogError( MSG )
	#define LogErrorWhat( WHAT )
#endif

#endif // !SOURCETOOLS_ERROR_H__
