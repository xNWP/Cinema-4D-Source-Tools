#ifndef ST_USER_CONFIG_H
#define ST_USER_CONFIG_H

#include "tinyxml2/tinyxml2.h"

#define CHECK_FOR_UPDATES		"CHECK_FOR_UPDATES"

//----------------------------------------------------------------------------------------
/// Generates the default user-configuration file.
///
/// @param[in, out] doc				The document to generate the file from, caller owns the document.
//----------------------------------------------------------------------------------------
void GenerateDefaultConfigFile(tinyxml2::XMLDocument &doc);

#endif