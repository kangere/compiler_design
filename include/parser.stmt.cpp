#include "parser.hpp"


Stmt*
parser::parse_statement()
{
	switch(lookahead())
	{
		case token::semi_colon:
			return parse_empty_statement();
		case token::if_kw:
			return parse_if_statement();
		case token::while_kw:
			return parse_while_statement();
		case token::return_kw:
			return parse_return_statement();
		case token::continue_kw:
			return parse_continue_statement();
		case token::break_kw:
			return parse_break_statement();
		case token::lbrace:
			return parse_block_statement();
		case token::var_kw:
		case token::ref_kw:
		case token::fun_kw:
			return parse_declaration_statement();

		default:
			return parse_expression_statement();
	}
}

Stmt*
parser::parse_empty_statement()
{
	return m_act.on_empty_statement();
}

Stmt*
parser::parse_if_statement()
{
	require(token::if_kw);
	expect(token::lparen);
	
	Expr* e = parse_expression();

	expect(token::rparen);
	Stmt* s1 = parse_statement();

	expect(token::else_kw);
	Stmt* s2 = parse_statement();

	return m_act.on_if_statement(e,s1,s2);
}

Stmt*
parser::parse_while_statement()
{
	require(token::while_kw);

	expect(token::lparen);

	Expr* e = parse_expression();

	expect(token::rparen);

	Stmt* s = parse_statement();

	return m_act.on_while_statement(e,s);
}

Stmt*
parser::parse_break_statement()
{
	require(token::break_kw);
	expect(token::semi_colon);

	return m_act.on_break_statement();
}

Stmt*
parser::parse_continue_statement()
{
	require(token::continue_kw);
	expect(token::semi_colon);

	return m_act.on_continue_statement();
} 

Stmt*
parser::parse_return_statement()
{
	require(token::return_kw);

	Expr* e = parse_expression();

	expect(token::semi_colon);

	return m_act.on_expr_statement(e);
}

Stmt*
parser::parse_expression_statement()
{
	Expr* e = parse_expression();

	expect(token::semi_colon);

	return m_act.on_expr_statement(e);
}

Stmt*
parser::parse_declaration_statement()
{
	Decl* d = parse_declaration_seq();

	return m_act.on_decl_statement(d);
}

Stmt*
parser::parse_block_statement()
{
	require(token::lbrace);

	std::vector<Stmt*> vec;
	while(next_token_is_not(token::rbrace)){

		Stmt* s = parse_statement();

		vec.push_back(s);	
	}
	
	expect(token::rbrace);

	return m_act.on_block_statement(vec);
}