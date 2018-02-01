#include "UserConfig.h"

void GenerateDefaultConfigFile(tinyxml2::XMLDocument &doc)
{
	tinyxml2::XMLNode *node = doc.NewElement(CHECK_FOR_UPDATES);
	doc.InsertEndChild(node);
}