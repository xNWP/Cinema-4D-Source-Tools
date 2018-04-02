// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "stParseTools.h"

namespace ST
{
	namespace Parse
	{
		std::vector<String>* ParseLines(const String &data)
		{
			std::vector<String> *rval = NewObj(std::vector<String>);
			Int32 it = 0;
			Int32 pos = 0;
			Bool FavourLF = false;

			while (pos < data.GetLength())
			{
				if (FavourLF)
				{
					if (data.FindFirst("\n", &it, pos))
					{
						rval->push_back(data.SubStr(pos, it - pos));
						pos = it + 1;
						continue;
					}
					else
					{
						FavourLF = false;
					}
				}
				else if (data.FindFirst("\r\n", &it, pos))
				{
					rval->push_back(data.SubStr(pos, it - pos));
					pos = it + 2;
				}
				else if (data.FindFirst("\n", &it, pos))
				{
					rval->push_back(data.SubStr(pos, it - pos));
					pos = it + 1;
					FavourLF = true;
				}
				else
				{
					rval->push_back(data.SubStr(pos, data.GetLength() - pos));
					break;
				}
			}
			return rval;
		}

		std::vector<String> split(const String &data)
		{
			std::vector<String> substrs;
			if (trim(data) == "")
				return substrs;

			Int32 start = -1;
			for (Int32 i = 0; i <= data.GetLength(); i++)
			{
				if ((data[i] == ' ' || data[i] == '\t') && start == -1)
				{
					continue;
				}
				else if (i == data.GetLength() && start != -1)
				{
					substrs.push_back((data.SubStr(start, i - start)));
				}
				else if (start == -1)
				{
					start = i;
				}
				else if ((data[i] == ' ' || data[i] == '\t') && start != -1)
				{
					substrs.push_back(data.SubStr(start, i - start));
					start = -1;
				}
			}
			return substrs;
		}

		std::vector<String> splitParam(const String &data)
		{
			std::vector<String> substrs;
			if (trim(data) == "")
				return substrs;

			Int32 start = -1;
			for (Int32 i = 0; i <= data.GetLength(); i++)
			{
				if ((data[i] == ' ' || data[i] == '\t') && start == -1)
				{
					continue;
				}
				else if (data[i] == '"')
				{
					start = i + 1;
					i++;
					while (data[i] != '"')
					{
						i++;
					}
					if (start != i)
						substrs.push_back(data.SubStr(start, i - start));

					start = -1;
				}
				else if (i == data.GetLength() && start != -1)
				{
					substrs.push_back((data.SubStr(start, i - start)));
				}
				else if (start == -1)
				{
					start = i;
				}
				else if ((data[i] == ' ' || data[i] == '\t') && start != -1)
				{
					substrs.push_back(data.SubStr(start, i - start));
					start = -1;
				}
			}
			return substrs;
		}

		BaseObject* FindChild(BaseObject *start, const String &name)
		{
			std::vector<BaseObject*> children;
			BaseObject *NewStart = start->GetDown();
			if (NewStart != nullptr)
			{
				if (NewStart->GetName() == name)
					return NewStart;

				children.push_back(NewStart);
				while (NewStart->GetNext() != nullptr)
				{
					NewStart = NewStart->GetNext();
					if (NewStart->GetName() == name)
						return NewStart;
					children.push_back(NewStart);
				}
				for (Int32 i = 0; i < children.size(); i++)
				{
					BaseObject *res = FindChild(children[i], name);
					if (res)
						return res;
				}
			}

			return nullptr;
		}

		VertexLitGeneric ParseVertexLitGeneric(BaseFile &vmtfile, const Filename &MaterialRoot)
		{
			VertexLitGeneric rval;
			rval = ParseVertexLitGeneric(vmtfile, MaterialRoot, rval);
			return rval;
		}

		VertexLitGeneric ParseVertexLitGeneric(BaseFile &vmtfile, const Filename &MaterialRoot, const VertexLitGeneric &vlg)
		{
			VertexLitGeneric rval = vlg;
			String line = ReadLine(vmtfile);
			std::vector<String> lines = Parse::splitParam(line);

			if (lines[0] == "patch") // patch, get include first
			{
				for (Int64 i = vmtfile.GetPosition(); i < vmtfile.GetLength(); i = vmtfile.GetPosition())
				{
					line = ReadLine(vmtfile);
					lines = Parse::splitParam(line);

					if (lines[0] == "include")
					{
						String incLoc = ParentDirectory(MaterialRoot).GetString() + "\\" + lines[1];
						incLoc = FSlashToBSlash(incLoc);
						AutoAlloc<BaseFile> inc;

						if(inc->Open(incLoc))
							rval = ParseVertexLitGeneric(inc, MaterialRoot, rval);
					}
					else if (lines[0] == "insert" || lines[0] == "replace")
					{
						line = ReadLine(vmtfile);
						while (line != "}")
						{
							lines = splitParam(line);
							ParseVertexLitGenericNode(lines, rval);
						}
					}
				}
			}
			else
			{
				for (Int64 i = vmtfile.GetPosition(); i < vmtfile.GetLength(); i = vmtfile.GetPosition())
				{
					line = ReadLine(vmtfile);
					lines = splitParam(line);
					ParseVertexLitGenericNode(lines, rval);
				}
			}

			return rval;
		}

		Filename ParentDirectory(const Filename &filename)
		{
			String str = filename.GetString();
			String res;
			for (Int32 i = str.GetLength() - 1; i >= 0; i--)
			{
				if (str[i] == '\\')
				{
					res = str.SubStr(0, i);
					break;
				}
			}
			return res;
		}

		String FSlashToBSlash(const String &string)
		{
			String rval = string;
			for (Int32 i = 0; i < rval.GetLength(); i++)
			{
				if (rval[i] == '/')
					rval[i] = '\\';
			}
			return rval;
		}

		void ParseVertexLitGenericNode(const std::vector<String> &params, VertexLitGeneric &vlg)
		{
			if (params.size() == 0)
				return;

			if (params[0] == "$basetexture")
			{
				vlg.basetexture = Filename(params[1]);
				vlg.basetexture.SetSuffix("vtf");
			}
			else if (params[0] == "$bumpmap")
			{
				vlg.bumpmap = Filename(params[1]);
				vlg.bumpmap.SetSuffix("vtf");
			}
			else if (params[0] == "$detail")
			{
				vlg.detail = Filename(params[1]);
				vlg.detail.SetSuffix("vtf");
			}
			else if (params[0] == "$phongexponenttexture")
			{
				vlg.PhongExponentTexture = Filename(params[1]);
				vlg.PhongExponentTexture.SetSuffix("vtf");
			}
			else if (params[0] == "$phong")
			{
				vlg.phong = (Bool)params[1].ToInt();
			}
			else if (params[0] == "$basemapalphaphongmask")
			{
				vlg.BasemapAlphaPhongMask = (Bool)params[1].ToInt();
			}
			else if (params[0] == "$basemapluminancephongmash")
			{
				vlg.BasemapLuminancePhongMask = (Bool)params[1].ToInt();
			}
			else if (params[0] == "$phongexponent")
			{
				vlg.PhongExponent = params[1].ToInt32();
			}
			else if (params[0] == "$translucent")
			{
				vlg.translucent = (Bool)params[1].ToInt();
			}
			else if (params[0] == "$alphatest")
			{
				vlg.translucent = (Bool)params[1].ToInt();
			}
			else if (params[0] == "$alpha")
			{
				vlg.alpha = params[1].ToFloat();
			}
			else if (params[0] == "$Iris")
			{
				vlg.Iris = Filename(params[1]);
				vlg.Iris.SetSuffix("vtf");
			}
			else if (params[0] == "$AmbientOcclTexture")
			{
				vlg.AmbientOcclTexture = Filename(params[1]);
				vlg.AmbientOcclTexture.SetSuffix("vtf");
			}
			else if (params[0] == "$Envmap")
			{
				vlg.Envmap = Filename(params[1]);
				vlg.Envmap.SetSuffix("vtf");
			}
		}

		void StripString(String &string)
		{
			string = string.SubStr(1, string.GetLength() - 2);
		}

		String trim(const String &istring)
		{
			String string = istring;
			if (string == "")
				return string;
			Bool bOk = false;
			while (!bOk)
			{
				if (string[0] == ' ' || string[0] == '\t')
					string = string.SubStr(1, string.GetLength() - 1);
				if (string[string.GetLength()] == ' ' || string[string.GetLength()] == '\t')
					string = string.SubStr(0, string.GetLength() - 1);
				if (string[0] == ' ' || string[0] == '\t' ||
					string[string.GetLength()] == ' ' || string[string.GetLength()] == '\t')
					bOk = false;
				else
					bOk = true;
			}
			return string;
		}

		String ReadLine(BaseFile &file)
		{
			String rval;
			Char *cval = NewMem(Char, 1024);
			Int64 i = file.GetPosition();
			Int32 it = 0;
			while (i < file.GetLength())
			{
				Char c;
				file.ReadChar(&c);
				i = file.GetPosition();
				if (c == '\r')
				{
					file.Seek(1);
					break;
				}
				if (c == '\n')
				{
					break;
				}
				*(cval + it) = c;
				it++;
			}
			*(cval + it) = '\0';
			rval = cval;
			DeleteMem(cval);
			return rval;
		}

		String PeekLine(BaseFile &file)
		{
			auto pos = file.GetPosition();
			String rval = ReadLine(file);
			file.Seek(pos, FILESEEK_START);
			return rval;
		}
	}
}