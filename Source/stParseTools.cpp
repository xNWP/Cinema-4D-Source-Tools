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

			while (pos < data.GetLength())
			{
				if (data.FindFirst("\r\n", &it, pos))
				{
					rval->push_back(data.SubStr(pos, it - pos));
					pos = it + 2;
				}
				else
				{
					rval->push_back(data.SubStr(pos, data.GetLength() - pos));
					break;
				}
			}
			return rval;
		}

		std::vector<String>* split(const String &data)
		{
			String name;
			std::vector<String> *substrs = NewObj(std::vector<String>);

			Int32 start = -1;
			for (Int32 i = 0; i <= data.GetLength(); i++)
			{
				if ((data[i] == ' ' || data[i] == '\t') && start == -1)
				{
					continue;
				}
				else if (i == data.GetLength())
				{
					substrs->push_back((data.SubStr(start, i - start)));
				}
				else if (start == -1)
				{
					start = i;
				}
				else if (data[i] == ' ' && start != -1)
				{
					substrs->push_back(data.SubStr(start, i - start));
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

		VertexLitGeneric ParseVertexLitGeneric(const VTFLib::CVMTFile *vmtfile, const Filename &MaterialRoot)
		{
			VertexLitGeneric rval;
			rval = ParseVertexLitGeneric(vmtfile, MaterialRoot, rval);
			return rval;
		}

		VertexLitGeneric ParseVertexLitGeneric(const VTFLib::CVMTFile *vmtfile, const Filename &MaterialRoot, const VertexLitGeneric &vlg)
		{
			VertexLitGeneric rval = vlg;
			VTFLib::Nodes::CVMTGroupNode *groupnode = NULL;
			groupnode = vmtfile->GetRoot();
			VTFLib::Nodes::CVMTNode *node = NULL;

			String nodeName = groupnode->GetName();
			if (nodeName.ToLower() == "patch") // patch, get include first
			{
				for (UInt32 i = 0; i < groupnode->GetNodeCount(); i++)
				{
					node = groupnode->GetNode(i);
					String name = node->GetName();

					if (name.ToLower() == "include")
					{
						VTFLib::Nodes::CVMTStringNode *strNode = (VTFLib::Nodes::CVMTStringNode*)node;
						String incLoc = ParentDirectory(MaterialRoot).GetString() + "\\" + strNode->GetValue();
						incLoc = FSlashToBSlash(incLoc);
						Char *cIncLoc = NewMem(Char, incLoc.GetCStringLen() + 1);
						incLoc.GetCString(cIncLoc, incLoc.GetCStringLen() + 1);
						VTFLib::CVMTFile *inc = NewObj(VTFLib::CVMTFile);
						if(inc->Load(cIncLoc))
							rval = ParseVertexLitGeneric(inc, MaterialRoot, rval);
						DeleteObj(inc);
						DeleteMem(cIncLoc);
					}
					else if (name.ToLower() == "insert" || name.ToLower() == "replace")
					{
						VTFLib::Nodes::CVMTGroupNode *gn = (VTFLib::Nodes::CVMTGroupNode*)node;
						for (UInt32 j = 0; j < gn->GetNodeCount(); j++)
						{
							VTFLib::Nodes::CVMTNode *irNode = gn->GetNode(j);
							ParseVertexLitGenericNode(irNode, rval);
						}
					}
				}
			}
			else
			{
				for (UInt32 h = 0; h < groupnode->GetNodeCount(); h++)
				{
					VTFLib::Nodes::CVMTNode *node = groupnode->GetNode(h);
					ParseVertexLitGenericNode(node, rval);
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

		void ParseVertexLitGenericNode(VTFLib::Nodes::CVMTNode *node, VertexLitGeneric &vlg)
		{
			VTFLib::Nodes::CVMTStringNode *strNode = (VTFLib::Nodes::CVMTStringNode*)node;
			VTFLib::Nodes::CVMTSingleNode *fNode = (VTFLib::Nodes::CVMTSingleNode*)node;
			VTFLib::Nodes::CVMTIntegerNode *intNode = (VTFLib::Nodes::CVMTIntegerNode*)node;
			String name = node->GetName();
			VMTNodeType type = node->GetType();

			if (name.ToLower() == "$basetexture")
			{
				vlg.basetexture = Filename(strNode->GetValue());
				vlg.basetexture.SetSuffix("vtf");
			}
			else if (name.ToLower() == "$bumpmap")
			{
				vlg.bumpmap = Filename(strNode->GetValue());
				vlg.bumpmap.SetSuffix("vtf");
			}
			else if (name.ToLower() == "$detail")
			{
				vlg.detail = Filename(strNode->GetValue());
				vlg.detail.SetSuffix("vtf");
			}
			else if (name.ToLower() == "$phongexponenttexture")
			{
				vlg.PhongExponentTexture = Filename(strNode->GetValue());
				vlg.PhongExponentTexture.SetSuffix("vtf");
			}
			else if (name.ToLower() == "$phong")
			{
				if (type == NODE_TYPE_STRING)
					vlg.phong = String(strNode->GetValue()).ToInt32();
				else
					vlg.phong = intNode->GetValue();
			}
			else if (name.ToLower() == "$basemapalphaphongmask")
			{
				if (type == NODE_TYPE_STRING)
					vlg.BasemapAlphaPhongMask = String(strNode->GetValue()).ToInt32();
				else
					vlg.BasemapAlphaPhongMask = intNode->GetValue();
			}
			else if (name.ToLower() == "$basemapluminancephongmash")
			{
				if (type == NODE_TYPE_STRING)
					vlg.BasemapLuminancePhongMask = String(strNode->GetValue()).ToInt32();
				else
					vlg.BasemapLuminancePhongMask = intNode->GetValue();
			}
			else if (name.ToLower() == "$phongexponent")
				vlg.PhongExponent = String(strNode->GetValue()).ToInt32();
			else if (name.ToLower() == "$translucent")
			{
				if (type == NODE_TYPE_STRING)
					vlg.translucent = String(strNode->GetValue()).ToInt32();
				else
					vlg.translucent = intNode->GetValue();
			}
			else if (name.ToLower() == "$alpha")
				vlg.alpha = fNode->GetValue();
		}
	}
}