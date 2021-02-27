#pragma once

#include <maxon/integer.h>
#include <maxon/floatingpoint.h>
#include <vector>

namespace st::camio
{
	namespace Types
	{
		struct Frame
		{
			maxon::Float32 time,
				xPosition, yPosition, zPosition,
				xRotation, yRotation, zRotation,
				fov;

			Frame(Float32 Time) : time(Time) { }
		};

		enum class SCALETYPE
		{
			UNKNOWN = 0,
			NONE = 1,
			ALIENSWARM = 2
		};
	}

	struct CamIO
	{
		maxon::Int32 Version;
		Types::SCALETYPE Scaling;
		std::vector<Types::Frame> Frames;
	};
}