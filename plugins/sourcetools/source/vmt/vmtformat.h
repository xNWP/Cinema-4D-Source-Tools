#pragma once

#include <any>
#include <unordered_map>

namespace VMTTypes {
enum class ShaderType { UNKNOWN, LIGHTMAPPEDGENERIC, CHARACTER };

enum class ParameterType { BASETEXTURE, BUMPMAP, SSBUMP, TRANSLUCENT };
} // namespace VMTTypes

struct ValveMaterialType {
  VMTTypes::ShaderType Shader;
  std::unordered_map<VMTTypes::ParameterType, std::any> Parameters;
};