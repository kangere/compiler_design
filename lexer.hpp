#pragma once

#include "symbol.hpp"
#include "token.hpp"

#include <unordered_map>


class lexer{
private:
	symbol_table *m_table;
	char const* m_first; 
	char const* m_end;
	int m_line;
	int m_col;
	std::unordered_map<std::string,token::type> m_kws;

public:
	lexer(symbol_table& sys,char const* f, char const* e);

	lexer(symbol_table& sys, std::string& s);

	token next_token();

	symbol_table* get_symbol_table() const
	{return m_table;}

private:	
	bool eof(char const* ptr) const
	{return ptr == m_end;}

	bool eof() const
	{return eof(m_first);}

	token gen_token(token::type,int len);
	token gen_word();
	token gen_number();

	char peek() const;

	char peek(int n) const;

	char consume()
	{++m_col; return *m_first++;}



};
