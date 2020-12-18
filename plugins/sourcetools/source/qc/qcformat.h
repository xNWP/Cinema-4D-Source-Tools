#pragma once

#include <vector>
#include <memory>

#include "modelproperties.h"

namespace QuakeCTypes
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
		std::vector<std::shared_ptr<QuakeCModelProperties::ModelProperty>> Properties;
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
	std::vector<QuakeCTypes::Mesh> BodyMeshes;
	std::vector<QuakeCTypes::BodyGroup> BodyGroups;
	std::vector<QuakeCTypes::Model> Models;
	std::vector<String> cdmaterials;
	std::vector<QuakeCTypes::IkRule> IkRules;
	QuakeCTypes::Mesh PhysicsMesh;
};