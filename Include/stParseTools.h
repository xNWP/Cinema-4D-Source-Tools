// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_PARSE_TOOLS_H
#define ST_PARSE_TOOLS_H

#include "c4d.h"
#include "stVMT.h"
#include <vector>
#include "VTFLib/VTFLib.h"

namespace ST
{
	namespace Parse
	{
		//----------------------------------------------------------------------------------------
		/// Split's a string into it's individual lines (CRLF).
		///
		/// @param[in] data				The input string.
		///
		/// @return						Pointer to std::vector<String>* array of individual lines.
		//----------------------------------------------------------------------------------------
		std::vector<String>* ParseLines(const String &data);

		//----------------------------------------------------------------------------------------
		/// Split line into its individual components.
		///
		/// @param[in] data				The input string.
		///
		/// @return						Pointer to std::vector<String>* array of components.
		//----------------------------------------------------------------------------------------
		std::vector<String>* split(const String &data);

		//----------------------------------------------------------------------------------------
		/// Find's a child by name of object start.
		///
		/// @param[in] start			Object to look through.
		/// @param[in] name				Name of the object we're looking for.
		///
		/// @return						BaseObject* found child, can be nullptr.
		//----------------------------------------------------------------------------------------
		BaseObject* FindChild(BaseObject *start, const String &name);

		//----------------------------------------------------------------------------------------
		/// Fills a VertexLitGeneric struct will all values from a VMT file. (assumes VTFLib.dll is loaded)
		///
		/// @param[in] vmtfile			The vmtfile to read from. Can be VertexLitGeneric or patch.
		/// @param[in] MaterialRoot		The root material folder i.e. pak01_dir/materials
		///
		/// @return						VertexLitGeneric of filled in data.
		//----------------------------------------------------------------------------------------
		VertexLitGeneric ParseVertexLitGeneric(const VTFLib::CVMTFile *vmtfile, const Filename &MaterialRoot);

		//----------------------------------------------------------------------------------------
		/// Fills a VertexLitGeneric struct will all values from a VMT file. Uses VLG as a basis and overwrites values. (assumes VTFLib.dll is loaded)
		///
		/// @param[in] vmtfile			The vmtfile to read from. Can be VertexLitGeneric or patch.
		/// @param[in] MaterialRoot		The root material folder i.e. pak01_dir/materials
		/// @param[in] vlg				The file to base return of off, overwrites values.
		///
		/// @return						VertexLitGeneric of filled in data.
		//----------------------------------------------------------------------------------------
		VertexLitGeneric ParseVertexLitGeneric(const VTFLib::CVMTFile *vmtfile, const Filename &MaterialRoot, const VertexLitGeneric &vlg);

		//----------------------------------------------------------------------------------------
		/// Goes up a level in directory. C:\SomeDir\Dir2 becomes C:\SomeDir
		///
		/// @param[in] filename			The input path.
		///
		/// @return						The parent directory.
		//----------------------------------------------------------------------------------------
		Filename ParentDirectory(const Filename &filename);

		//----------------------------------------------------------------------------------------
		/// Converts forward slashes to back slashes.
		///
		/// @param[in] string			The string to convert.
		///
		/// @return						The converted string.
		//----------------------------------------------------------------------------------------
		String FSlashToBSlash(const String &string);

		//----------------------------------------------------------------------------------------
		/// Read's a node and fills out the respective value in vlg.
		///
		/// @param[in] node				The node to read.
		/// @param[out]	vlg				The VertexLitGeneric to modify.
		//----------------------------------------------------------------------------------------
		void ParseVertexLitGenericNode(VTFLib::Nodes::CVMTNode *node, VertexLitGeneric &vlg);

		//----------------------------------------------------------------------------------------
		/// Removes beginning and ending " from string.
		///
		/// @param[in,out] string		The string to strip.
		//----------------------------------------------------------------------------------------
		void StripString(String &string);

		//----------------------------------------------------------------------------------------
		/// Removes preceeding tab spaces, and normal spaces from a string.
		///
		/// @param[in] istring			The string to trim.
		///
		/// @return String				The trimmed string.
		//----------------------------------------------------------------------------------------
		String trim(const String &istring);

		//----------------------------------------------------------------------------------------
		/// Reads a line from a file.
		///
		/// @param[in] file				The file to read from.
		///
		/// @return String				The Line.
		//----------------------------------------------------------------------------------------
		String ReadLine(BaseFile &file);
	}
}

#endif