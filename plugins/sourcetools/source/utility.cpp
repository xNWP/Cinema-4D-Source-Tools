#include "utility.h"

#include "c4d.h"

namespace st
{
	bool ResolveLocalFilepath(Filename& fp, const std::vector<Filename>& searchdirectories, const Bool& isdir)
	{
		Filename Match;
		maxon::String strFp = fp.GetString();

		// direct match
		for (const auto& dir : searchdirectories)
		{
			maxon::String strMatch = dir.GetString();
			if (!(strMatch.EndsWith('/') || strMatch.EndsWith('\\')))
			{
				strMatch.AppendChar('/').GetValue();
			}

			if (strFp.StartsWith('.'))
			{
				strFp.Erase(0, 1).GetValue();
			}

			if (strFp.StartsWith('/') || strFp.StartsWith('\\'))
			{
				strFp.Erase(0, 1).GetValue();
			}

			strMatch += strFp;
			strMatch.Replace('\\', '/').GetValue();
			Match = strMatch;

			if (GeFExist(Match, isdir))
			{
				fp = Match;
				return true;
			}
		}

		// soft match
		for (const auto& dir : searchdirectories)
		{
			if (GeSearchFile(dir, fp, &Match))
			{
				fp = Match;
				return true;
			}
		}

		return false;
	}
}