#pragma once

#include <unordered_map>
#include <any>

namespace st::vmt
{
	namespace Types
	{
		enum class ShaderType
		{
			UNKNOWN,
			LIGHTMAPPEDGENERIC,
			CHARACTER
		};

		enum class ParameterType
		{
			BASETEXTURE,
			BUMPMAP,
			SSBUMP,
			TRANSLUCENT
		};
	}

	struct ValveMaterialType
	{
		Types::ShaderType Shader;
		std::unordered_map<Types::ParameterType, std::any> Parameters;
	};
}