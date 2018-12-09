#include "parser.hpp"



Expr*
parser::parse_primary_expression()
{

	if(token tok = match(token::int_lit)){
		return m_act.on_int_literal(tok);
	
	}else if(token tok = match(token::float_lit)){
		return m_act.on_float_literal(tok);
	
	} else if(token tok = match(token::bool_lit)){
		return m_act.on_bool_literal(tok);
	
	} else if (token tok = match(token::identifier)){
		return m_act.on_identifier_expression(tok);

	} else if(token tok = match(token::lparen)){

		Expr* expr = parse_expression();

		expect(token::rparen);

		return expr;
	}

	throw std::runtime_error("Expected factor");
}


Expr*
parser::parse_expression()
{
	return parse_assignment_expression();
}	

Expr*
parser::parse_assignment_expression()
{
	Expr* e1 = parse_conditional_expression();

	if(match(token::equal)){
		Expr* e2 = parse_assignment_expression();
		return m_act.on_assignment_expression(e1,e2);
	}

	return e1;
}

Expr*
parser::parse_conditional_expression()
{
	Expr* cond = parse_or_expression();

	if(match(token::qmark)){
		Expr* e1 = parse_expression();

		//expect semi-colon
		expect(token::semi_colon);

		Expr* e2 = parse_conditional_expression();

		cond = m_act.on_conditional_expression(cond,e1,e2);
	}

	return cond;
}

Expr*
parser::parse_or_expression()
{
	Expr* e1 = parse_and_expression();

	if(match(token::or_kw)){
		Expr* e2 = parse_or_expression();

		e1 = m_act.on_or_expression(e1,e2);
	}

	return e1;
}

Expr*
parser::parse_and_expression()
{
	Expr* e1 = parse_equality_expression();

	if(match(token::and_kw)){
		Expr* e2 = parse_and_expression();

		e1 = m_act.on_and_expression(e1,e2);
	}

	return e1;
}

Expr*
parser::parse_equality_expression()
{

	Expr* e1  = parse_relational_expression();

	if(token tok = match(token::eq_eq)){
		Expr* e2 = parse_equality_expression();
		e1 = m_act.on_equals_expression(e1,e2);	
		
	}else if(token tok = match(token::n_eq)){
		Expr* e2 = parse_equality_expression();
		e1 = m_act.on_not_equals_expression(e1,e2);

	}
	
	return e1;
}

Expr*
parser::parse_relational_expression()
{
	Expr* e1 = parse_additive_expression();

	if(match(token::lt)){

		Expr* e2 = parse_relational_expression();

		e1 = m_act.on_lt_expression(e1,e2);

	} else if(match(token::gt)){
		
		Expr* e2 = parse_relational_expression();

		e1 = m_act.on_gt_expression(e1,e2);

	} else if(match(token::lt_eq)){
		
		Expr* e2 = parse_relational_expression();

		e1 = m_act.on_lt_eq_expression(e1,e2);

	} else if(match(token::gt_eq)){
		
		Expr* e2 = parse_relational_expression();

		e1 = m_act.on_gt_eq_expression(e1,e2);
	}

	return e1;
}

Expr*
parser::parse_additive_expression()
{

	Expr* e1 = parse_multiplicative_expression();

	if(token tok = match(token::plus)){
		Expr* e2 = parse_additive_expression(); 
		e1 = m_act.on_add_expression(e1,e2);
	
	}else if(token tok = match(token::minus)){
		Expr* e2 = parse_additive_expression();
		e1 = m_act.on_sub_expression(e1,e2);
		
	}

	return e1;
}

Expr*
parser::parse_multiplicative_expression()
{
	Expr* e1 = parse_unary_expression();

	if(token tok = match(token::mult)){
		Expr* e2 = parse_multiplicative_expression();
		e1 = m_act.on_mult_expression(e1,e2);
	
	} else if(token tok = match(token::div)){
		Expr* e2 = parse_multiplicative_expression();
		e1 = m_act.on_div_expression(e1,e2);

	} else if(token tok = match(token::percent)){
		Expr* e2 = parse_multiplicative_expression();
		e1 = m_act.on_remainder_expression(e1,e2);

	}

	return e1;
}

Expr*
parser::parse_unary_expression()
{

	Expr* e1 = parse_postfix_expression();

	if(token tok = match(token::minus)){
		Expr* e2 = parse_unary_expression();
		return m_act.on_negation_expression(e2); 

	} else if(token tok = match(token::div)) {
		Expr* e2 = parse_unary_expression();
		return m_act.on_reciprocal_expression(e2); 	
			
	} else if(token tok = match(token::not_kw)) {
		Expr* e2 = parse_unary_expression();
		return m_act.on_lnegation_expression(e2); 	
			
	}
	

	return e1;
}


Expr*
parser::parse_postfix_expression()
{
	Expr* e1 = parse_primary_expression();

	if(match(token::lparen)){
		std::vector<Expr*> e2 = parse_argument_list();
		e2.insert(e2.begin(),e1);
		
		//expect closing right parenthesis
		expect(token::rparen);

		return m_act.on_call_expression(e2);
	}

	return e1;
}

std::vector<Expr*>
parser::parse_argument_list()
{
	std::vector<Expr*> args;

	Expr* e1 = parse_argument();

	if(!e1)
		return args;
	
	args.push_back(e1);

	while(match(token::comma)){
		Expr* e2 = parse_argument();
		args.push_back(e2);
	}

	return args;
}

Expr*
parser::parse_argument()
{
	return parse_expression();
}