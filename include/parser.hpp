#pragma once

#include "lexer.hpp"
#include "token.hpp"
#include "symbol.hpp"
#include <vector>
#include <string>

class parser {
private:
	lexer m_lex;
	token* m_lookahead;
	token* m_last;
	std::vector<token> m_toks;



	bool is_eof() const { return m_lookahead == m_last;}

	const token& peek() const {return *m_lookahead;}

	token::type lookahead() const {return peek().get_type();}

	bool next_token_is(token::type t) const
	{ return lookahead() == t;}

	bool next_token_is_not(token::type t) const
	{ return lookahead() != t;}

	token consume();

	token match(token::type t);

	token expect(token::type t);

	token require(token::type t);

public:
	parser(symbol_table& syms, std::string& input);
};
