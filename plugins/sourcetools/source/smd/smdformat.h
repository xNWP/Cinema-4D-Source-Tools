#ifndef SMD_FORMAT_H__
#define SMD_FORMAT_H__

#include <cstdint>
#include <string>
#include <vector>

struct StudiomdlData
{
	struct Bone
	{
		std::int16_t Id;
		std::string Name;
		std::int16_t ParentId;
	};

	struct Point3f
	{
		float x, y, z;
	};

	struct SkeletonAnimationEntry
	{
		std::int16_t Id;
		Point3f Position;
		Point3f Rotation;
	};

	struct SkeletonAnimationFrame
	{
		std::uint32_t Time;
		std::vector<SkeletonAnimationEntry> Entries;
	};

	struct WeightmapEntry
	{
		std::int16_t BoneId;
		float Weight;
	};

	struct Vertex
	{
		std::int16_t ParentBone;
		Point3f Position;
		Point3f Normals;
		float u;
		float v;
		std::vector<WeightmapEntry> WeightMapEntries;
	};

	struct Triangle
	{
		std::string Material;
		Vertex Vertices[3];
	};

	std::uint8_t Version;
	std::vector<Bone> Bones;
	std::vector<SkeletonAnimationFrame> SkeletonAnimation;
	std::vector<Triangle> Triangles;
};

#endif // !SMD_FORMAT_H__
