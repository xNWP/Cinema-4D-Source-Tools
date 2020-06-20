#include "qcloader.h"

Bool QCLoaderData::Identify( BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size )
{
	// QuakeC is an ASCII format with no FourCC/Header so we will use the file extension
	return ( name.GetSuffix().ToLower() == "qc" ) ? true : false;
}