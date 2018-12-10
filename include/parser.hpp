#pragma once

#include "lexer.hpp"
#include "token.hpp"
#include "symbol.hpp"
#include "expr.hpp"
#include "decl.hpp"
#include "type.hpp"
#include "stmt.hpp"
#include "actions.hpp"
#include <vector>
#include <string>

class parser {
private:
	lexer m_lex;
	token* m_lookahead;
	token* m_last;
	std::vector<token> m_toks;
	actions m_act;



	bool is_eof() const { return m_lookahead == m_last;}

	const token& peek() const {return *m_lookahead;}

	token::type lookahead() const {return peek().get_type();}

	bool next_token_is(token::type t) const
	{ return lookahead() == t;}

	bool next_token_is_not(token::type t) const
	{ return lookahead() != t;}

	token consume();

	//if lookahead is t, cosnume. Otherwise return Eof
	token match(token::type t);

	//if lookahead is t, cosnume. Otherwise error
	token expect(token::type t);

	//if lookahead is t, cosnume. Otherwise UB
	token require(token::type t);

public:
	parser(symbol_table& syms, std::string& input);

	//Expressions
	Expr* parse_primary_expression();

	Expr* parse_expression();

	Expr* parse_assignment_expression();

	Expr* parse_conditional_expression();

	Expr* parse_or_expression();

	Expr* parse_and_expression();

	Expr* parse_equality_expression();

	Expr* parse_relational_expression();

	Expr* parse_additive_expression();

	Expr* parse_multiplicative_expression();

	Expr* parse_unary_expression();

	Expr* parse_postfix_expression();

	std::vector<Expr*> parse_argument_list();

	Expr* parse_argument(); 

	
	//Statements
	Stmt* parse_statement();

	Stmt* parse_empty_statement();

	Stmt* parse_expression_statement();
	
	Stmt* parse_declaration_statement();
	
	Stmt* parse_return_statement();
	
	Stmt* parse_continue_statement();
	
	Stmt* parse_break_statement();
	
	Stmt* parse_while_statement();
	
	Stmt* parse_if_statement();
	
	Stmt* parse_seq_statement();
	
	Stmt* parse_block_statement();



	//Declarations
	std::vector<Decl*> parse_program();

	Decl* parse_declaration_seq();

	Decl* parse_declaration();

	Decl* parse_variable_declaration();

	Decl* parse_function_declaration();

	Decl* parse_reference_declaration();

	Decl* parse_parameter();

	std::vector<Decl*> parse_parameter_list();


	//type
	Type* parse_type();


};
