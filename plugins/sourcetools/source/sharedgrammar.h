#pragma once

#include "tao/pegtl.hpp"

namespace st::shared_grammar
{
    using namespace tao;

    /* Junk */

	struct double_quote
		: pegtl::one<'"'>
	{};

	struct whitespace
		: pegtl::plus<pegtl::blank>
	{};

	struct whitespace_linefeeds
		: pegtl::plus<pegtl::space>
	{};

	/* Primitives */

	struct identifier_ext
		: pegtl::seq<pegtl::identifier_first,
		pegtl::plus <
		pegtl::sor<pegtl::identifier_other,
		pegtl::one<'-', '.', ' ', '{', '}'>>>>
	{};

	struct filename
		: identifier_ext
	{};

	struct filepath
		: pegtl::seq<pegtl::sor<pegtl::identifier_first, pegtl::one<'.', '/', '\\'>>,
		pegtl::plus <
		pegtl::sor<pegtl::identifier_other,
		pegtl::one<'-', '.', '/', '\\', '{', '}', ' '>>>>
	{};

	struct integer
		: pegtl::seq<
		pegtl::opt<pegtl::one<'+', '-'>>,
		pegtl::plus<pegtl::digit>>
	{};

	struct floatingpoint
		: pegtl::seq<
		pegtl::opt<pegtl::one<'+', '-'>>,
		pegtl::plus<pegtl::digit>,
		pegtl::opt<pegtl::seq<pegtl::one<'.'>, pegtl::plus<pegtl::digit>>>>
	{};

	template <typename object>
	struct opt_quotes_wrapped
		: pegtl::seq <
		pegtl::opt<double_quote>,
		object,
		pegtl::opt<double_quote>>
	{};

	template <typename key, typename value>
	struct template_keyvalue_pair
		: pegtl::seq<opt_quotes_wrapped<key>, whitespace, opt_quotes_wrapped<value>>
	{};

	template <typename class_header, typename ...class_attributes>
	struct template_opt_class
		: pegtl::seq <
		opt_quotes_wrapped<class_header>,
		whitespace_linefeeds,
		pegtl::opt <
		pegtl::one<'{'>,
		pegtl::until<pegtl::one<'}'>,
		pegtl::sor <class_attributes..., whitespace_linefeeds, pegtl::any>>>>
	{};

    struct line_comment
		: pegtl::seq<
		pegtl::string<'/', '/'>,
		pegtl::until<pegtl::eolf>>
	{};

	struct multiline_comment
		: pegtl::seq<
		pegtl::string<'/', '*'>,
		pegtl::until<pegtl::string<'*', '/'>>>
	{};

	struct comments
		: pegtl::sor<line_comment, multiline_comment>
	{};
}
