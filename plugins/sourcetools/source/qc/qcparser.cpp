#include "qcparser.h"

#include "qcformat.h"
#include "tao/pegtl.hpp"
#include "error.h"
#include "sharedgrammar.h"

#include "benchmark.h"

namespace qc_grammar
{
	using namespace tao;
	using namespace shared_grammar;

	/* File Objects */

	struct BodyMeshName
		: identifier_ext
	{};

	struct BodyMeshFilepath
		: filepath
	{};

	struct BodyClassHeader
		: pegtl::seq<
		pegtl::istring<'$', 'b', 'o', 'd', 'y'>,
		whitespace,
		opt_quotes_wrapped<BodyMeshName>,
		whitespace,
		opt_quotes_wrapped<BodyMeshFilepath>>
	{};

	struct BodyClass
		: template_opt_class<BodyClassHeader>
	{};

	struct ModelMeshName
		: identifier_ext
	{};

	struct ModelMeshFilepath
		: filepath
	{};

	struct ModelClassHeader
		: pegtl::seq<
		pegtl::istring<'$', 'm', 'o', 'd', 'e', 'l'>,
		whitespace,
		opt_quotes_wrapped<ModelMeshName>,
		whitespace,
		opt_quotes_wrapped<ModelMeshFilepath>>
	{};

	struct ModelPropertyEyeballName
		: identifier_ext
	{};

	struct ModelPropertyEyeballParentBoneName
		: identifier_ext
	{};

	struct ModelPropertyEyeballWorldPosX
		: floatingpoint
	{};

	struct ModelPropertyEyeballWorldPosY
		: floatingpoint
	{};

	struct ModelPropertyEyeballWorldPosZ
		: floatingpoint
	{};

	struct ModelPropertyEyeballMaterialName
		: identifier_ext
	{};

	struct ModelPropertyEyeballYawOffset
		: floatingpoint
	{};

	struct ModelPropertyEyeball
		: pegtl::seq<
		pegtl::istring<'e', 'y', 'e', 'b', 'a', 'l', 'l'>,
		whitespace,
		opt_quotes_wrapped<ModelPropertyEyeballName>,
		whitespace,
		opt_quotes_wrapped<ModelPropertyEyeballParentBoneName>,
		whitespace,
		ModelPropertyEyeballWorldPosX,
		whitespace,
		ModelPropertyEyeballWorldPosY,
		whitespace,
		ModelPropertyEyeballWorldPosZ,
		whitespace,
		opt_quotes_wrapped<ModelPropertyEyeballMaterialName>,
		whitespace,
		floatingpoint, // skip diameter
		whitespace,
		ModelPropertyEyeballYawOffset,
		whitespace,
		opt_quotes_wrapped<identifier_ext>, // skip iris material [deprecated]
		whitespace,
		opt_quotes_wrapped<floatingpoint> // skip iris scale [deprecated]
		>
	{};


	struct ModelClass
		: template_opt_class<ModelClassHeader, ModelPropertyEyeball>
	{};

	struct BodyGroupName
		: identifier_ext
	{};

	struct BodyGroupHeader
		: pegtl::seq<
		pegtl::istring<'$', 'b', 'o', 'd', 'y', 'g', 'r', 'o', 'u', 'p'>,
		whitespace,
		opt_quotes_wrapped<BodyGroupName>>
	{};

	struct BodyGroupMeshName
		: filepath
	{};

	struct BodyGroupEntry
		: pegtl::seq<
		pegtl::istring<'s', 't', 'u', 'd', 'i', 'o'>,
		whitespace,
		opt_quotes_wrapped<BodyGroupMeshName>>
	{};

	struct BodyGroupBlank
		: pegtl::istring<'b', 'l', 'a', 'n', 'k'>
	{};

	struct BodyGroupClass
		: template_opt_class<BodyGroupHeader, BodyGroupEntry, BodyGroupBlank>
	{};

	struct cdmaterials_value : filepath
	{};

	struct cdmaterials : template_keyvalue_pair<pegtl::istring<
		'$', 'c', 'd', 'm', 'a', 't', 'e', 'r', 'i', 'a', 'l', 's'>,
		cdmaterials_value>
	{};

	struct IkName : identifier_ext
	{};

	struct IkEndBone : identifier_ext
	{};

	struct IkChain
		: pegtl::seq<
		opt_quotes_wrapped<pegtl::istring<'$', 'i', 'k', 'c', 'h', 'a', 'i', 'n'>>,
		whitespace,
		opt_quotes_wrapped<IkName>,
		whitespace,
		opt_quotes_wrapped<IkEndBone>,
		pegtl::until<pegtl::eol, pegtl::any>>
	{};

	struct CollisionMeshName : filepath
	{};

	struct CollisionPhysics
		: pegtl::seq<pegtl::sor <
		opt_quotes_wrapped<pegtl::istring<'$', 'c', 'o', 'l', 'l', 'i', 's', 'i', 'o', 'n', 'j', 'o', 'i', 'n', 't', 's'>>,
		opt_quotes_wrapped<pegtl::istring<'$', 'c', 'o', 'l', 'l', 'i', 's', 'i', 'o', 'n', 'm', 'o', 'd', 'e', 'l'>>>,
		whitespace,
		opt_quotes_wrapped<CollisionMeshName>>
	{};

	struct CollisionPhysicsClass
		: template_opt_class<CollisionPhysics, pegtl::any>
	{};

	struct qc_file
		: pegtl::until<pegtl::eof,
		pegtl::sor<

		BodyClass,
		ModelClass,
		BodyGroupClass,
		cdmaterials,
		IkChain,
		CollisionPhysicsClass,

		comments,
		whitespace_linefeeds,
		pegtl::any>>
	{};

	/* Actions */

	template <typename Rule>
	struct action
		: pegtl::nothing<Rule>
	{};

	template<>
	struct action<BodyMeshName>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			qc.BodyMeshes.emplace_back(QuakeCTypes::Mesh(In.string().c_str()));
		}
	};

	template <>
	struct action<BodyMeshFilepath>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			(qc.BodyMeshes.end() - 1)->Filepath = In.string().c_str();
		}
	};

	template<>
	struct action<BodyGroupName>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			qc.BodyGroups.emplace_back(QuakeCTypes::BodyGroup(In.string().c_str()));
		}
	};

	template<>
	struct action<BodyGroupMeshName>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			(qc.BodyGroups.end() - 1)->Meshes.emplace_back(In.string().c_str());
		}
	};

	template<>
	struct action<BodyGroupBlank>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			(qc.BodyGroups.end() - 1)->Blank = true;
		}
	};

	template<>
	struct action<ModelMeshName>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			qc.Models.emplace_back(QuakeCTypes::Model(In.string().c_str()));
		}
	};

	template <>
	struct action<ModelMeshFilepath>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			(qc.Models.end() - 1)->Filepath = In.string().c_str();
		}
	};

	template<>
	struct action<ModelPropertyEyeballName>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			(qc.Models.end() - 1)->Properties.push_back(std::make_shared<QuakeCModelProperties::ModelPropertyEyeball>(In.string().c_str()));
		}
	};

	template<>
	struct action<cdmaterials_value>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			qc.cdmaterials.push_back(String(In.string().c_str()));
		}
	};

	template<>
	struct action<IkName>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			qc.IkRules.emplace_back(QuakeCTypes::IkRule(In.string().c_str()));
		}
	};

	template<>
	struct action<IkEndBone>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			(qc.IkRules.end() - 1)->EndBone = String(In.string().c_str());
		}
	};

	template<>
	struct action<CollisionMeshName>
	{
		template <typename Input>
		static void apply(const Input& In, QuakeCFormat& qc)
		{
			qc.PhysicsMesh = QuakeCTypes::Mesh("physics");
			qc.PhysicsMesh.Filepath = In.string().c_str();
		}
	};
}

maxon::Bool ParseQC(const Filename& file, QuakeCFormat& qc)
{
	IF_PROFILING(Benchmark ParseQCBench("ParseQC"));
	tao::pegtl::file_input infile( file.GetString().GetCStringCopy() );

	maxon::Bool bOk;
	try
	{
		bOk = tao::pegtl::parse<qc_grammar::qc_file, qc_grammar::action>(infile, qc);
	}
	catch (tao::pegtl::parse_error& e)
	{
		LogErrorWhat(e);
		return false;
	}

	/* Check for errors */

	if (!bOk)
	{
		LogError("Exception free error in QC PEGTL Parser.");
		return false;
	}

	return true;
}