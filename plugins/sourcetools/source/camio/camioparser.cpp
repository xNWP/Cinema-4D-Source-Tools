#include "camioparser.h"

#include "error.h"
#include "tao/pegtl.hpp"
#include "sharedgrammar.h"

#include "benchmark.h"

namespace st::camio
{
	namespace grammar
	{
		using namespace tao::pegtl;
		using namespace shared_grammar;

		struct version : integer {};
		struct scaling : identifier_ext {};

		struct header
			: seq<
			istring<'a', 'd', 'v', 'a', 'n', 'c', 'e', 'd', 'f', 'x', ' ', 'C', 'a', 'm'>, whitespace_linefeeds,
			istring<'v', 'e', 'r', 's', 'i', 'o', 'n'>, whitespace, version, whitespace_linefeeds,
			istring<'s', 'c', 'a', 'l', 'e', 'F', 'o', 'v'>, whitespace, scaling, whitespace_linefeeds,
			istring<'c', 'h', 'a', 'n', 'n', 'e', 'l', 's', ' ', 't', 'i', 'm', 'e', ' ', 'x', 'P', 'o', 's', 'i', 't',
			'i', 'o', 'n', ' ', 'y', 'P', 'o', 's', 'i', 't', 'i', 'o', 'n', ' ', 'z', 'P', 'o', 's', 'i', 't', 'i', 'o',
			'n', ' ', 'x', 'R', 'o', 't', 'a', 't', 'i', 'o', 'n', ' ', 'y', 'R', 'o', 't', 'a', 't', 'i', 'o', 'n', ' ',
			'z', 'R', 'o', 't', 'a', 't', 'i', 'o', 'n', ' ', 'f', 'o', 'v'>, whitespace_linefeeds,
			istring<'D', 'A', 'T', 'A'>>
		{};

		struct time : floatingpoint {};
		struct xPos : floatingpoint {};
		struct yPos : floatingpoint {};
		struct zPos : floatingpoint {};
		struct xRot : floatingpoint {};
		struct yRot : floatingpoint {};
		struct zRot : floatingpoint {};
		struct fov : floatingpoint {};

		struct frame
			: seq<time, whitespace,
			xPos, whitespace,
			yPos, whitespace,
			zPos, whitespace,
			xRot, whitespace,
			yRot, whitespace,
			zRot, whitespace,
			fov>
		{};

		struct camio_file
			: seq<
			header,
			until<eof,
			sor<whitespace_linefeeds,
			comments,
			frame>>>
		{};

		/* Actions */
		template <typename Rule>
		struct action
			: nothing<Rule>
		{};

		template<>
		struct action<version>
		{
			template <typename Input>
			static void apply(const Input& in, CamIO& camio)
			{
				camio.Version = std::stoi(in.string());
			}
		};

		template<>
		struct action<scaling>
		{
			template <typename Input>
			static void apply(const Input& in, CamIO& camio)
			{
				if (in.string() == "none")
					camio.Scaling = Types::SCALETYPE::NONE;
				else if (in.string() == "alienSwarm")
					camio.Scaling = Types::SCALETYPE::ALIENSWARM;
				else
				{
					String msg = "Unknown Scaling Type: "_s;
					msg += String(in.string().c_str());
					LogError(msg);
					camio.Scaling = Types::SCALETYPE::UNKNOWN;
				}
			}
		};

		template<>
		struct action<time>
		{
			template <typename Input>
			static void apply(const Input& in, CamIO& camio)
			{
				camio.Frames.emplace_back(Float32(std::stof(in.string())));
			}
		};

		template<>
		struct action<xPos>
		{
			template <typename Input>
			static void apply(const Input& in, CamIO& camio)
			{
				(camio.Frames.end() - 1)->xPosition = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<yPos>
		{
			template <typename Input>
			static void apply(const Input& in, CamIO& camio)
			{
				(camio.Frames.end() - 1)->yPosition = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<zPos>
		{
			template <typename Input>
			static void apply(const Input& in, CamIO& camio)
			{
				(camio.Frames.end() - 1)->zPosition = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<xRot>
		{
			template <typename Input>
			static void apply(const Input& in, CamIO& camio)
			{
				(camio.Frames.end() - 1)->xRotation = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<yRot>
		{
			template <typename Input>
			static void apply(const Input& in, CamIO& camio)
			{
				(camio.Frames.end() - 1)->yRotation = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<zRot>
		{
			template <typename Input>
			static void apply(const Input& in, CamIO& camio)
			{
				(camio.Frames.end() - 1)->zRotation = Float32(std::stof(in.string()));
			}
		};

		template<>
		struct action<fov>
		{
			template <typename Input>
			static void apply(const Input& in, CamIO& camio)
			{
				(camio.Frames.end() - 1)->fov = Float32(std::stof(in.string()));
			}
		};
	}

	maxon::Bool ParseCamIO(const Filename& filename, CamIO& camio)
	{
		IF_PROFILING(Benchmark ParseCamIOBench("ParseCamIO"));
		tao::pegtl::file_input infile(filename.GetString().GetCStringCopy());

		maxon::Bool bOk;
		try
		{
			bOk = tao::pegtl::parse<grammar::camio_file, grammar::action>(infile, camio);
		}
		catch (tao::pegtl::parse_error& e)
		{
			LogErrorWhat(e);
			return false;
		}

		/* Check for errors */

		if (!bOk)
		{
			LogError("Exception free error in CamIO PEGTL Parser.");
			return false;
		}

		return true;
	}

	maxon::Bool CheckCamIOFileHeader(const Filename& filename)
	{
		IF_PROFILING(Benchmark CheckCamIOFileHeaderBench("CheckCamIOFileHeader"));
		tao::pegtl::file_input infile(filename.GetString().GetCStringCopy());

		maxon::Bool bOk;
		try
		{
			bOk = tao::pegtl::parse<grammar::header>(infile);
		}
		catch (tao::pegtl::parse_error& e)
		{
			LogErrorWhat(e);
			return false;
		}

		/* Check for errors */
		if (!bOk)
		{
			LogError("Exception free error in CamIO PEGTL Parser.");
			return false;
		}

		return true;
	}
}