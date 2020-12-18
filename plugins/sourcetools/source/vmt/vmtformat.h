#pragma once

#include <unordered_map>
#include <any>

namespace VMTTypes
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
	VMTTypes::ShaderType Shader;
	std::unordered_map<VMTTypes::ParameterType, std::any> Parameters;
};