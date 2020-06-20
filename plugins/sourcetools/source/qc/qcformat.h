#ifndef QC_FORMAT_H__
#define QC_FORMAT_H__

#include <string>
#include <vector>
#include <cstdint>
#include <memory>

enum class ModelPropertyType : std::uint32_t
{
	UNKNOWN = 0,
	EYEBALL
};

struct QuakeCFormat
{
	template <typename T>
	struct Vec3
	{
		Vec3() : x(0), y(0), z(0) { }
		T x;
		T y;
		T z;
	};

	struct ModelProperty
	{
		ModelProperty() = delete;
		ModelProperty(ModelPropertyType type) : _type(type) { }

		ModelPropertyType GetType() { return _type; }

	private:
		ModelPropertyType _type;
	};

	struct ModelPropertyEyeball : ModelProperty
	{
		ModelPropertyEyeball(std::string name)
			: ModelProperty(ModelPropertyType::EYEBALL), Name(name),
		EyeballCenter(), YawOffset(0.0f) { }

		std::string Name;
		std::string ParentBoneName;
		Vec3<float> EyeballCenter;
		std::string MaterialName;
		float YawOffset;
	};

	struct Mesh
	{
		Mesh( std::string name ) : Name( name ) {}
		std::string Name;
		std::string Filepath;
	};

	struct Model : Mesh
	{
		Model( std::string name ) : Mesh( name ) {}
		std::vector<std::unique_ptr<ModelProperty>> Properties;
	};

	struct BodyGroup
	{
		BodyGroup( std::string name ) : Name( name ), Blank( false ) {}
		std::string Name;
		std::vector<std::string> Meshes;
		bool Blank = false;
	};

	std::vector<Mesh> BodyMeshes;
	std::vector<BodyGroup> BodyGroups;
	std::vector<Model> Models;
};

#endif // !QC_FORMAT_H__
