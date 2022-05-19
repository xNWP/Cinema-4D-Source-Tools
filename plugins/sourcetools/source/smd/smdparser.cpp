#include "smdparser.h"

#include "tao/pegtl.hpp"
#include "error.h"
#include "sharedgrammar.h"

#include <unordered_map>

#include "benchmark.h"

// DEBUG STUFFS
//#define ST_DEBUG_PARSESMD_DUPVERT_DIFFDATA

namespace st::smd
{
	// TODO: There should be a way to do this without relying on a symbol map
	class symbol_map
	{
		using cstr = const char*;
		std::unordered_map<cstr, std::int16_t> i16map;
		std::unordered_map<cstr, std::uint32_t> u32map;
		std::unordered_map<cstr, std::uint8_t> u8map;

	public:
		std::unordered_map<cstr, std::int16_t>& i16() { return i16map; }
		std::unordered_map<cstr, std::uint32_t>& u32() { return u32map; }
		std::unordered_map<cstr, std::uint8_t>& u8() { return u8map; }
	};

	namespace grammar
	{
		using namespace tao;
		using namespace shared_grammar;

		/* File Objects */

		struct version_number : integer
		{};

		struct version
			: pegtl::seq<
			pegtl::string<'v', 'e', 'r', 's', 'i', 'o', 'n'>,
			pegtl::one<' '>,
			version_number>
		{};

		struct node_id : integer
		{};

		struct node_name :
			identifier_ext
		{};

		struct node_parentid : integer
		{};

		struct node_entry
			: pegtl::seq<
			node_id,
			whitespace,
			opt_quotes_wrapped<node_name>,
			whitespace,
			node_parentid,
			pegtl::until<pegtl::eolf>>
		{};

		struct nodes
			: pegtl::seq<
			pegtl::istring<'n', 'o', 'd', 'e', 's'>,
			pegtl::until<pegtl::istring<'e', 'n', 'd'>,
			pegtl::sor<node_entry, pegtl::any>>>
		{};

		struct skeleton_time : integer
		{};

		struct skeleton_id : integer
		{};

		struct skeleton_pos_x : floatingpoint
		{};
		struct skeleton_pos_y : floatingpoint
		{};
		struct skeleton_pos_z : floatingpoint
		{};

		struct skeleton_rot_x : floatingpoint
		{};
		struct skeleton_rot_y : floatingpoint
		{};
		struct skeleton_rot_z : floatingpoint
		{};

		struct skeleton_entry
			: pegtl::seq<
			skeleton_id,
			whitespace,
			skeleton_pos_x, whitespace,
			skeleton_pos_y, whitespace,
			skeleton_pos_z, whitespace,
			skeleton_rot_x, whitespace,
			skeleton_rot_y, whitespace,
			skeleton_rot_z,
			pegtl::until<pegtl::eolf, pegtl::any>>
		{};

		struct skeleton
			: pegtl::seq<
			pegtl::string<'t', 'i', 'm', 'e'>,
			whitespace,
			skeleton_time,
			pegtl::until<pegtl::sor<pegtl::string<'e', 'n', 'd'>, pegtl::at<pegtl::string<'t', 'i', 'm', 'e'>>>,
			pegtl::sor<skeleton_entry, pegtl::any>>>
		{};

		struct triangles_material
			: filepath
		{};

		struct triangles_vertex_parent_bone
			: integer
		{};

		struct triangles_vertex_pos_x
			: floatingpoint
		{};

		struct triangles_vertex_pos_y
			: floatingpoint
		{};

		struct triangles_vertex_pos_z
			: floatingpoint
		{};

		struct triangles_vertex_norm_x
			: floatingpoint
		{};

		struct triangles_vertex_norm_y
			: floatingpoint
		{};

		struct triangles_vertex_norm_z
			: floatingpoint
		{};

		struct triangles_vertex_u
			: floatingpoint
		{};

		struct triangles_vertex_v
			: floatingpoint
		{};

		struct triangles_vertex_bone_id
			: integer
		{};

		struct triangles_vertex_bone_weight
			: floatingpoint
		{};

		struct triangles_vertex
			: pegtl::seq <
			triangles_vertex_parent_bone,
			whitespace,
			triangles_vertex_pos_x,
			whitespace,
			triangles_vertex_pos_y,
			whitespace,
			triangles_vertex_pos_z,
			whitespace,
			triangles_vertex_norm_x,
			whitespace,
			triangles_vertex_norm_y,
			whitespace,
			triangles_vertex_norm_z,
			whitespace,
			triangles_vertex_u,
			whitespace,
			triangles_vertex_v,
			pegtl::opt<whitespace, integer, whitespace,
			pegtl::until<pegtl::eol,
			pegtl::sor<
			pegtl::seq<triangles_vertex_bone_id, whitespace, triangles_vertex_bone_weight>,
			pegtl::any>>>>
		{};

		struct triangle_entry
			: pegtl::seq<
			opt_quotes_wrapped<triangles_material>, whitespace_linefeeds,
			triangles_vertex, pegtl::opt<whitespace_linefeeds>,
			triangles_vertex, pegtl::opt<whitespace_linefeeds>, 
			triangles_vertex, pegtl::opt<whitespace_linefeeds>>
		{};

		struct triangles
			: pegtl::seq<
			pegtl::string<'t', 'r', 'i', 'a', 'n', 'g', 'l', 'e', 's'>,
			pegtl::until<pegtl::string<'e', 'n', 'd'>,
			pegtl::sor<triangle_entry, pegtl::any>>>
		{};

		struct smd_file
			: pegtl::until<pegtl::eof,
			pegtl::sor<
			comments,
			version,
			nodes,
			skeleton,
			triangles,

			pegtl::any>>
		{};

		/* Actions */
		template <typename Rule>
		struct action
			: pegtl::nothing<Rule>
		{};

		template<>
		struct action<version_number>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				s.Version = UChar(std::stoi(in.string()));
			}
		};

		template<>
		struct action<node_id>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				Types::Bone b;
				b.Id = UInt16(std::stoi(in.string()));
				s.Bones.push_back(std::move(b));
			}
		};

		template<>
		struct action<node_name>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				(s.Bones.end() - 1)->Name = String(in.string().c_str());
			}
		};

		template<>
		struct action<node_parentid>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				(s.Bones.end() - 1)->ParentId = UInt16(std::stoi(in.string()));
			}
		};

		template<>
		struct action<skeleton_time>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				Types::SkeletonAnimationFrame f;
				f.Time = UInt32(std::stoi(in.string()));
				s.SkeletonAnimation.push_back(std::move(f));
			}
		};

		template<>
		struct action<skeleton_id>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				Types::SkeletonAnimationEntry e;
				e.Id = UInt16(std::stoi(in.string()));
				(s.SkeletonAnimation.end() - 1)->Entries.push_back(std::move(e));
			}
		};

		template<>
		struct action<skeleton_pos_x>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				((s.SkeletonAnimation.end() - 1)->Entries.end() - 1)->
					Position.x = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<skeleton_pos_y>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				((s.SkeletonAnimation.end() - 1)->Entries.end() - 1)->
					Position.y = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<skeleton_pos_z>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				((s.SkeletonAnimation.end() - 1)->Entries.end() - 1)->
					Position.z = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<skeleton_rot_x>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				((s.SkeletonAnimation.end() - 1)->Entries.end() - 1)->
					Rotation.x = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<skeleton_rot_y>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				((s.SkeletonAnimation.end() - 1)->Entries.end() - 1)->
					Rotation.y = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<skeleton_rot_z>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				((s.SkeletonAnimation.end() - 1)->Entries.end() - 1)->
					Rotation.z = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<triangles_material>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				Types::Triangle t;
				t.Material = String(in.string().c_str());
				s.Triangles.emplace_back(std::move(t));

				// set/reset vertex index
				smap.u8()["triangles_vertex_index"] = 0;
			}
		};

		template<>
		struct action<triangles_vertex_parent_bone>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				Types::Vertex v;
				v.ParentBone = UInt16(std::stoi(in.string()));
				(s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]] = std::move(v);
			}
		};

		template<>
		struct action<triangles_vertex_pos_x>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				(s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]].Position.x = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<triangles_vertex_pos_y>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				(s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]].Position.y = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<triangles_vertex_pos_z>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				(s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]].Position.z = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<triangles_vertex_norm_x>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				(s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]].Normals.x = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<triangles_vertex_norm_y>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				(s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]].Normals.y = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<triangles_vertex_norm_z>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				(s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]].Normals.z = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<triangles_vertex_u>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				(s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]].u = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<triangles_vertex_v>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				(s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]].v = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<triangles_vertex_bone_id>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				Types::WeightmapEntry w;
				w.BoneId = std::uint16_t(std::stoi(in.string()));
				(s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]]
					.WeightMapEntries.push_back(std::move(w));
			}
		};

		template<>
		struct action<triangles_vertex_bone_weight>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				((s.Triangles.end() - 1)->Vertices[smap.u8()["triangles_vertex_index"]]
					.WeightMapEntries.end() - 1)->Weight = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<triangles_vertex>
		{
			template <typename Input>
			static void apply(const Input& in, StudiomdlData& s, symbol_map& smap)
			{
				// increment vertex index
				smap.u8()["triangles_vertex_index"]++;
			}
		};

	}

	maxon::Bool ParseSMD(const Filename& file, StudiomdlData& smd)
	{
		IF_PROFILING(Benchmark ParseSMDBench("ParseSMD"));
		tao::pegtl::file_input infile(file.GetString().GetCStringCopy());
		symbol_map symbolmap;

		maxon::Bool bOk;

		try
		{
			bOk = tao::pegtl::parse<grammar::smd_file, grammar::action>(infile, smd, symbolmap);
		}
		catch (tao::pegtl::parse_error& e)
		{
			LogErrorWhat(e);
			return false;
		}
		catch (tao::pegtl::input_error& e)
		{
			LogErrorWhat(e);
			return false;
		}

		/* check for errors */

		if (!bOk)
		{
			LogError("Exception free error in SMD PEGTL Parser.");
			return false;
		}

		if (smd.Version != 1)
		{
			LogError("SMD version != 1");
			return false;
		}

		if (smd.Bones.empty())
		{
			LogError("SMD missing bones.");
			return false;
		}

		if (smd.SkeletonAnimation.empty())
		{
			LogError("SMD missing skeleton pose.");
			return false;
		}

		if (smd.SkeletonAnimation[0].Entries.size() != smd.Bones.size())
		{
			LogError("SMD skeleton pose is incompatible with bone definition.");
			return false;
		}

		/* DEBUG CODE: used to check for duplicate vertices with differing weightmaps. */
#ifdef	ST_DEBUG_PARSESMD_DUPVERT_DIFFDATA
		{
			IF_PROFILING(Benchmark ParseSMDDebugBench("ParseSMD-DebugDupVertsDiffData-Bench"));
			std::vector<std::vector<smd::Types::Vertex>> Vertices;
			for (const auto& tri : smd.Triangles) {
				for (const auto& vert : tri.Vertices) {
					bool bFound = false;
					for (auto it = std::rbegin(Vertices); it != std::rend(Vertices); it++) {
						if (vert.Position.Distance((*it)[0].Position) < 0.01f) {
							it->push_back(vert);
							bFound = true;
							break;
						}
					}

					if (!bFound) Vertices.push_back({ vert });
				}
			}

			Int32 weightDiff = 0;
			Int32 normalsDiff = 0;
			Int32 parentBoneDiff = 0;
			Int32 groupIt = 0;
			for (const auto& verts : Vertices) {
				if (verts.size() > 1) {
					auto cmpVert = verts[0];
					for (const auto& otherVert : verts) {
						Bool bDiff = false;
						
						if (otherVert.WeightMapEntries != cmpVert.WeightMapEntries) {
							bDiff = true; weightDiff++;
						}

						if (otherVert.Normals.Distance(cmpVert.Normals) > 0.01f) {
							bDiff = true; normalsDiff++;
						}

						if (otherVert.ParentBone != cmpVert.ParentBone) {
							bDiff = true; parentBoneDiff++;
						}

						if (bDiff) {
							String vertListStr = "Group " + String::IntToString(groupIt++) + "\n";
							for (const auto& x : verts) {
								vertListStr +=
									"[" + String::IntToString(x.ParentBone) + "] " +
									"[" + String::FloatToString(x.Position.x) + ", " +
									String::FloatToString(x.Position.y) + ", " +
									String::FloatToString(x.Position.z) + "] " +
									"[" + String::FloatToString(x.Normals.x) + ", " +
									String::FloatToString(x.Normals.y) + ", " +
									String::FloatToString(x.Normals.z) + "] " +
									"[" + String::FloatToString(x.u) + ", " +
									String::FloatToString(x.v) + "] " +
									"[";
								for (auto y : x.WeightMapEntries) vertListStr +=
									"(" + String::IntToString(y.BoneId) + ", " + String::FloatToString(y.Weight) + "), ";
								vertListStr.Delete(vertListStr.GetLength() - 2, 2);
								vertListStr += "]\n";
							}
							Log(vertListStr);
							break;
						}
					}
				}
			}

			String dMsg = "Parent Bone Diffs: " + String::IntToString(parentBoneDiff)
				+ " Weight Diffs: " + String::IntToString(weightDiff)
				+ " Normal Diffs: " + String::IntToString(normalsDiff);
			Log(dMsg);
		}
#		endif

		return true;
	}
}