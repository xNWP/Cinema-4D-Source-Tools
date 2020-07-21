#include "qcparser.h"

#include "qcformat.h"
#include "tao/pegtl.hpp"
#include "c4dst_error.h"

namespace qc_grammar
{
	using namespace tao;

	/* Junk */

	struct double_quote
		: pegtl::one<'"'>
	{};

	struct whitespace
		: pegtl::plus<pegtl::space>
	{};

	/* Primitives */

	struct identifier_ext
		: pegtl::plus <
		pegtl::sor<pegtl::identifier_other,
		pegtl::one<'-', '.'>>>
	{};

	struct filepath
		: pegtl::plus <
		pegtl::sor<pegtl::identifier_other,
		pegtl::one<'-', '.', '/', '\\'>>>
	{};

	struct integer
		: pegtl::plus<pegtl::digit>
	{};

	struct floatingpoint
		: pegtl::seq <
		pegtl::opt<pegtl::one<'+', '-'>>,
		integer,
		pegtl::opt<pegtl::seq<
		pegtl::one<'.'>, integer>>>
	{};

	template <typename object>
	struct opt_quotes_wrapped
		: pegtl::seq <
		pegtl::opt<double_quote>,
		object,
		pegtl::opt<double_quote>>
	{};

	template <typename class_header, typename ...class_attributes>
	struct template_opt_class
		: pegtl::seq <
		class_header,
		pegtl::opt <
		whitespace,
		pegtl::one<'{'>,
		pegtl::until<pegtl::one<'}'>,
		pegtl::sor < class_attributes..., whitespace, pegtl::any >>>>
	{};

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
		: identifier_ext
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

	struct qc_file
		: pegtl::until<pegtl::eof,
		pegtl::sor<

		BodyClass,
		ModelClass,
		BodyGroupClass,

		pegtl::any>>
	{};

	/* Actions */

	template <typename Rule>
	struct action
		: pegtl::nothing<Rule>
	{};

	template<>
	struct action< BodyMeshName >
	{
		template <typename Input>
		static void apply( const Input& In, QuakeCFormat& qc )
		{
			qc.BodyMeshes.emplace_back( QuakeCFormat::Mesh( In.string() ) );
		}
	};

	template <>
	struct action< BodyMeshFilepath >
	{
		template <typename Input>
		static void apply( const Input& In, QuakeCFormat& qc )
		{
			( qc.BodyMeshes.end() - 1 )->Filepath = In.string();
		}
	};

	template<>
	struct action< BodyGroupName >
	{
		template <typename Input>
		static void apply( const Input& In, QuakeCFormat& qc )
		{
			qc.BodyGroups.emplace_back( QuakeCFormat::BodyGroup( In.string() ) );
		}
	};

	template<>
	struct action< BodyGroupMeshName >
	{
		template <typename Input>
		static void apply( const Input& In, QuakeCFormat& qc )
		{
			( qc.BodyGroups.end() - 1 )->Meshes.emplace_back( In.string() );
		}
	};

	template<>
	struct action< BodyGroupBlank >
	{
		template <typename Input>
		static void apply( const Input& In, QuakeCFormat& qc )
		{
			( qc.BodyGroups.end() - 1 )->Blank = true;
		}
	};

	template<>
	struct action< ModelMeshName >
	{
		template <typename Input>
		static void apply( const Input& In, QuakeCFormat& qc )
		{
			qc.Models.emplace_back( QuakeCFormat::Model( In.string() ) );
		}
	};

	template <>
	struct action< ModelMeshFilepath >
	{
		template <typename Input>
		static void apply( const Input& In, QuakeCFormat& qc )
		{
			( qc.Models.end() - 1 )->Filepath = In.string();
		}
	};

	template<>
	struct action< ModelPropertyEyeballName >
	{
		template <typename Input>
		static void apply( const Input& In, QuakeCFormat& qc )
		{
			( qc.Models.end() - 1 )->Properties.push_back( std::make_unique<QuakeCFormat::ModelPropertyEyeball>( In.string() ) );
		}
	};
}

maxon::Bool ParseQC( const Filename& file, QuakeCFormat& qc )
{
	tao::pegtl::file_input infile( file.GetString().GetCStringCopy() );

	maxon::Bool bOk;
	try
	{
		bOk = tao::pegtl::parse<qc_grammar::qc_file, qc_grammar::action>( infile, qc );
	}
	catch ( tao::pegtl::parse_error& e )
	{
		LogErrorWhat( e );
		return false;
	}

	/* Check for errors */

	if ( !bOk )
	{
		LogError( "Exception free error in QC PEGTL Parser." );
		return false;
	}

	return true;
}