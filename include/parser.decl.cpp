#include "parser.hpp"


void
parser::parse_program()
{
	m_act.enter_scope();
	Decl* d = parse_declaration_seq(); 
	m_act.leave_scope();
}

Decl*
parser::parse_declaration_seq()
{

	return parse_declaration();
}

Decl*
parser::parse_declaration()
{
	switch(lookahead()){

		case token::fun_kw:
			return parse_function_declaration();
		case token::var_kw:
			return parse_variable_declaration();
		case token::ref_kw:
			return parse_reference_declaration();
	}
}


Decl*
parser::parse_variable_declaration()
{
	require(token::var_kw);
	token id = expect(token::identifier);

	expect(token::colon);

	Type* type = parse_type();

	Decl* var = m_act.on_variable_declaration(id,type);

	if(match(token::equal)){
		Expr* e = parse_expression();

		expect(token::semi_colon);

		var = m_act.finish_variable_declaration(var,e);
	}

	expect(token::semi_colon);

	return  var;
}

Decl*
parser::parse_reference_declaration()
{
	require(token::ref_kw);

	token id = expect(token::identifier);

	expect(token::colon);

	Type* type = parse_type();

	expect(token::equal);

	Expr* e = parse_expression();

	expect(token::semi_colon);

	return m_act.on_reference_declaration(id,type,e);
}

Decl*
parser::parse_function_declaration()
{
	require(token::fun_kw);

	token id = expect(token::identifier);

	expect(token::lparen);

	std::vector<Decl*> params = parse_parameter_list();

	expect(token::rparen);
	expect(token::arrow);

	Type* type = parse_type();

	Decl* func = m_act.on_function_declaration(id,type);

	//enter block scope
	m_act.enter_scope();

	Stmt* block = parse_statement();

	//leave block scope
	m_act.leave_scope();

	func = m_act.finish_function_declaration(func,block);

	return func;
}

std::vector<Decl*>
parser::parse_parameter_list()
{
	std::vector<Decl*> params;

	Decl* d = parse_parameter();

	if(!d)
		return params;

	params.push_back(d);

	//enter parameter scope
	m_act.enter_scope();

	while(match(token::comma)){
		Decl* d2 = parse_parameter();
		params.push_back(d2);
	}

	//leave parameter scope
	m_act.leave_scope();

	return params;
}

Decl*
parser::parse_parameter()
{
	token id = match(token::identifier);

	expect(token::colon);

	Type* type = parse_type();

	return m_act.on_variable_declaration(id,type);
}