#include "parser.hpp"
#include <cassert>
#include <stdexcept>


parser::parser(symbol_table& syms, 
				std::string& input)
	: m_lex(syms,input)
{
	while(token tok = m_lex.next_token())
		m_toks.push_back(tok);

	m_lookahead  = m_toks.data();

	m_last = m_lookahead + m_toks.size();
}

token
parser::consume()
{
	assert(!is_eof());

	token ret = *m_lookahead;
	++m_lookahead;

	return ret;
}

token
parser::match(token::type t)
{
	if(next_token_is(t))
		return consume();

	return token();
}

token
parser::expect(token::type t)
{
	if(next_token_is(t))
		return consume();

	throw std::runtime_error("syntax error");

	return token();
}

token
parser::require(token::type n)
{
	assert(next_token_is(n));
	return consume();
}


