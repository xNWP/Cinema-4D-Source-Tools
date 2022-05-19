#pragma once

#include <maxon/string.h>
#include <maxon/integer.h>
#include <vector>

namespace st::smd
{
	namespace Types
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

			Float32 Distance(const Point3f& p) const {
				return maxon::Sqrt(
					maxon::Sqr(this->x - p.x) + 
					maxon::Sqr(this->y - p.y) + 
					maxon::Sqr(this->z - p.z));
			}
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

			bool operator==(const WeightmapEntry& wm) const {
				return
					(this->BoneId == wm.BoneId) &&
					(this->Weight == wm.Weight);
			}
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
		std::vector<Types::Bone> Bones;
		std::vector<Types::SkeletonAnimationFrame> SkeletonAnimation;
		std::vector<Types::Triangle> Triangles;
	};
}