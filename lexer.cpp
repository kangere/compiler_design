#include "lexer.hpp"
#include <iostream>
#include <cctype>

//util functions
static bool
is_digit(char c)
{ return std::isdigit(c);}

static bool
is_nondigit(char c)
{ return std::isalpha(c) || c == '_';}

static bool
is_hex(char c)
{return std::isxdigit(c);}

static bool
is_nondigit_or_digit(char c)
{ return is_digit(c) ||  is_nondigit(c);}


lexer::lexer(symbol_table& sys,char const* f, char const* e)
:m_table(&sys), m_first(f), m_end(e), m_line(1),m_col(1)
{
	m_kws.emplace("and", token::and_kw);
	m_kws.emplace("bool", token::bool_kw);
	m_kws.emplace("break", token::break_kw);
	m_kws.emplace("continue", token::continue_kw);
	m_kws.emplace("else", token::else_kw);
	m_kws.emplace("false", token::false_kw);
	m_kws.emplace("fun", token::fun_kw);
	m_kws.emplace("if", token::if_kw);
	m_kws.emplace("int", token::int_kw);
	m_kws.emplace("not", token::not_kw);
	m_kws.emplace("or", token::or_kw);
	m_kws.emplace("ref", token::ref_kw);
	m_kws.emplace("return", token::return_kw);
	m_kws.emplace("true", token::true_kw);
	m_kws.emplace("var", token::var_kw);
	m_kws.emplace("while", token::while_kw);

}


lexer::lexer(symbol_table& sys, std::string& s)
:lexer(sys,s.data(),s.data() + s.size())
{}

token
lexer::gen_token(token::type t, int len)
{
	std::string n(m_first,m_first + len);

	symbol s = m_table->get(n);

	m_first += len;

	return token(s,location(m_line,m_col),t);
}

char
lexer::peek() const
{
	return eof() ? 0 : *m_first;
}

char
lexer::peek(int n) const
{
	return (m_end - m_first) >= n ? 0 : *(m_first + n);
}

token
lexer::next_token()
{
	while(true){
		
		switch(peek())
		{
			case ' ':
				consume();
				continue;
			case '\t':
				m_col += 4;
				consume();
				continue;
			case '\n':
				++m_line;
				m_col = 1;
				consume();
				continue;
			case '\b':
				consume();
				continue;
			case '\f':
				consume();
				continue;
			case '\r':
				consume();
				continue;
			case '\v':
				consume();
				continue;
			case '\\':
				consume();
				continue;
			case '\'':
				consume();
				continue;
			case '\"':
				consume();
				continue;

			//punctuations
			case '(':
				return gen_token(token::lparen,1);
			case ')':
				return gen_token(token::rparen,1);
			case '{':
				return gen_token(token::lbrack,1);
			case '}':
				return gen_token(token::rbrack,1);
			case ',':
				return gen_token(token::comma,1);
			case ';':
				return gen_token(token::semi_colon,1);
			case ':':
				return gen_token(token::colon,1);
			case '-':
				if(peek(1) == '>')
					return gen_token(token::arrow,2);
				return gen_token(token::minus,1);

			//relational operators
			case '=':
				if(peek(1) == '=')
					return gen_token(token::eq_eq,2);
				return gen_token(token::equal,1);
			case '<':
				if(peek(1) == '=')
					return gen_token(token::lt_eq,2);
				return gen_token(token::lt,1);
			case '>':
				if(peek(1) == '=')
					return gen_token(token::gt_eq,2);
				return gen_token(token::gt,1);
			case '!':
				if(peek(1) == '=')
					return gen_token(token::n_eq,2);
				std::cerr << "error:" << m_line << ":" << m_col << std::endl; 
				std::cerr << " expected:'=' , actual:" << peek(1) << std::endl;
				consume();
				continue;
			
			//arithmetic operators
			case '+':
				return gen_token(token::plus,1);
			case '*':
				return gen_token(token::mult,1);
			case '/':
				return gen_token(token::div,1);
			case '%':
				return gen_token(token::percent,1);
			case '?':
				return gen_token(token::qmark,1);

			default:
				if(is_nondigit(*m_first))
					return gen_word();

				/**TODO implement number token generation
				if(is_digit(*m_first))
					return gen_number();
				**/
				if(eof())
					return gen_token(token::eof,1);

				std::cerr << "error:" << m_line << ":" << m_col << std::endl;
				std::cerr << " invalid character: " << m_first<< std::endl;
				consume();
				continue;

		}	
	}
	
}

token
lexer::gen_word()
{
	char const* end = m_first+1;
	int len = 1;

	while(!eof(end) && is_nondigit_or_digit(*end)){
		++end;
		++len;
	}

	//increment column to length of word
	m_col += len;

	std::string id(m_first,end);
	symbol s = m_table->get(id);

	token::type t;

	auto iter = m_kws.find(id);

	if(iter == m_kws.end())
		t = token::identifier;
	else
		t = iter->second;

	//advance lexer
	m_first = end;
	
	return token(s,location(m_line,m_col - len),t);
}




