// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "QCSequenceAnimation.h"

namespace ST
{
	QCAnimation::QCAnimation(const std::vector<String> &data, Int32 &it)
		: m_fps(30), m_loop(false), m_loop_start(0)
	{
		Int32 tIt = it;
		Bool IsClass = false;
		while (data[tIt] != "}")
		{
			std::vector<String> cmd = ST::Parse::split(data[tIt]);

			for (Int32 i = 0; i < cmd.size(); i++)
			{
				if (tIt == it) // first line
				{
					String name = cmd[1];
					ST::Parse::StripString(name);
					m_name = name;
					String smd = cmd[2];
					ST::Parse::StripString(smd);
					m_smd = Filename(smd);
					if (cmd.size() > 3)
					{
						if (cmd[3] == "{")
							IsClass = true;
						else // single liner parse
						{

						}
					}
				}
			}

			if (!IsClass)
				break;
		}
	}

	void QCAnimation::ParseCommand(const std::vector<String> &data, Int32 &it)
	{
		if (data[it] == "fps")
		{
			m_fps = data[it + 1].ParseToInt32();
			it = it + 1;
		}
		else if (data[it] == "loop")
		{
			m_loop = true;
			it = it + 1;
		}
		else if (data[it] == "startloop")
		{
			m_loop_start = data[it + 1].ParseToInt32();
			it = it + 2;
		}
		else if (data[it] == "weightlist")
		{
			// find in master weight list catalogue
		}
	}
}
