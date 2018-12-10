#include "parser.hpp"


std::vector<Decl*>
parser::parse_program()
{
	std::vector<Decl*> declarations;


	m_act.enter_scope(); 	//enter the global scope
	
	while(Decl* d = parse_declaration_seq())
		declarations.push_back(d);

	m_act.leave_scope();	//leave the global scope

	return declarations;
}

Decl*
parser::parse_declaration_seq()
{
	if(is_eof())
		return nullptr;

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

	throw std::runtime_error(m_lookahead->get_lexme().str() + " is not a declaration");
}


Decl*
parser::parse_variable_declaration()
{
	require(token::var_kw);
	token id = expect(token::identifier);

	expect(token::colon);

	Type* type = parse_type();

	Decl* var = m_act.on_variable_declaration(id,type);

	if(next_token_is(token::equal)){

		//consume equal
		consume();

		Expr* e = parse_expression();

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

	//enter parameter scope
	m_act.enter_scope();

	std::vector<Decl*> params = parse_parameter_list();

	expect(token::rparen);
	expect(token::arrow);

	Type* ret_type = parse_type();

	Func_type* f_type = m_act.on_func_type();


	//set return type of function type
	f_type->set_return_type(ret_type);

	//Add parameter types 
	for(const Decl* p : params)
		f_type->add_param(p->get_type());



	Decl* func = m_act.on_function_declaration(id,f_type);

	//enter block scope
	m_act.enter_scope();

	Stmt* block = parse_statement();

	//leave block scope
	m_act.leave_scope();

	//leave parameter scope
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

	while(next_token_is(token::comma)){

		//consume comma
		consume();

		Decl* d2 = parse_parameter();
		params.push_back(d2);
	}

	return params;
}

Decl*
parser::parse_parameter()
{
	if(token id = match(token::identifier)){
		expect(token::colon);

		Type* type = parse_type();

		return m_act.on_variable_declaration(id,type);	
	}

	return nullptr;
}