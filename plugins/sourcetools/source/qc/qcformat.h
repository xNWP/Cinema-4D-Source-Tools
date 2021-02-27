#pragma once

#include <vector>
#include <memory>

#include "modelproperties.h"

namespace st::qc
{
	namespace Types
	{
		struct Mesh
		{
			Mesh() = default;
			Mesh(String name) : Name(name) {}
			String Name;
			String Filepath;
		};

		struct Model : public Mesh
		{
			Model(String name) : Mesh(name) {}
			std::vector<std::shared_ptr<ModelProperties::ModelProperty>> Properties;
		};

		struct BodyGroup
		{
			BodyGroup(String name) : Name(name), Blank(false) {}
			String Name;
			std::vector<String> Meshes;
			bool Blank = false;
		};

		struct IkRule
		{
			IkRule(String name) : Name(name) {}
			String Name;
			String EndBone;
		};
	}

	struct QuakeCFormat
	{
		std::vector<Types::Mesh> BodyMeshes;
		std::vector<Types::BodyGroup> BodyGroups;
		std::vector<Types::Model> Models;
		std::vector<String> cdmaterials;
		std::vector<Types::IkRule> IkRules;
		Types::Mesh PhysicsMesh;
	};
}