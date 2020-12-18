#pragma once

#include <maxon/string.h>
#include <maxon/integer.h>
#include <vector>

namespace SMDTypes
{
	struct Bone
	{
		Int16 Id;
		String Name;
		Int16 ParentId;
	};

	struct Point3f
	{
		Float32 x, y, z;
	};

	struct SkeletonAnimationEntry
	{
		UInt16 Id;
		Point3f Position;
		Point3f Rotation;
	};

	struct SkeletonAnimationFrame
	{
		UInt32 Time;
		std::vector<SkeletonAnimationEntry> Entries;
	};

	struct WeightmapEntry
	{
		Int16 BoneId;
		Float32 Weight;
	};

	struct Vertex
	{
		UInt16 ParentBone;
		Point3f Position;
		Point3f Normals;
		Float32 u;
		Float32 v;
		std::vector<WeightmapEntry> WeightMapEntries;
	};

	struct Triangle
	{
		String Material;
		Vertex Vertices[3];
	};
}

struct StudiomdlData
{
	UChar Version;
	std::vector<SMDTypes::Bone> Bones;
	std::vector<SMDTypes::SkeletonAnimationFrame> SkeletonAnimation;
	std::vector<SMDTypes::Triangle> Triangles;
};