// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef QC_SEQUENCE_ANIMATION_H
#define QC_SEQUENCE_ANIMATION_H

#include "c4d.h"
#include <map>
#include "stParseTools.h"
#include <vector>

namespace ST
{
	struct QCWeightList
	{
		String name;
		std::map<String, Float32> weights;
	};

	//----------------------------------------------------------------------------------------
	/// Class that contains all the necessary information for a QC $sequence object.
	//----------------------------------------------------------------------------------------
	class QCAnimation
	{
	public:
		//----------------------------------------------------------------------------------------
		/// Fills out all data of the object given an array of lines.
		///
		/// @param[in] data					Array of lines (likely from the qc file).
		/// @param[in,out] it				Iterator for where the $animation tag begins,
		///									returns as the closing tag, or same for one line animation tags.
		//----------------------------------------------------------------------------------------
		QCAnimation(const std::vector<String> &data, Int32 &it);

		UInt32 GetFPS() const { return m_fps; }
		String GetName() const { return m_name; }
		Filename GetSMD() const { return m_smd; }
		Bool IsLoop() const { return m_loop; }
		Int32 GetLoopStart() const { return m_loop_start; }
		QCWeightList GetWeights() const { return m_weights; }
	private:
		//----------------------------------------------------------------------------------------
		/// Fills out object data from line filled with command(s).
		///
		/// @param[in] data					Array of line elements.
		/// @param[in,out] it				Iterator of where first element is, returns as the next element start.
		//----------------------------------------------------------------------------------------
		void ParseCommand(const std::vector<String> &data, Int32 &it);

		UInt32 m_fps;
		String m_name;
		Filename m_smd;
		Bool m_loop;
		Int32 m_loop_start;
		QCWeightList m_weights;
	};
}

#endif