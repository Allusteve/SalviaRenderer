#ifndef SASL_PARSER_GRAMMARS_LITERAL_CONSTANT_H
#define SASL_PARSER_GRAMMARS_LITERAL_CONSTANT_H

#include "../parser_forward.h"
#include "../../parser_tree/literal.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex.hpp>

SASL_DEFINE_GRAMMAR( literal_constant_grammar, sasl::parser_tree::constant() ){
	template <typename TokenDefT, typename SASLGrammarT>
	literal_constant_grammar( const TokenDefT& tok, SASLGrammarT& g );

	SASL_GRAMMAR_RULE_DEFINITION_HELPER();

	typename rule<sasl::parser_tree::constant()>::type lit_const;
};

#endif