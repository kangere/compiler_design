#include "parser.hpp"



Expr*
parser::parse_primary_expression()
{

	if(is_eof())
		return nullptr;

	token tok = consume();

	if(tok.is(token::int_lit)){
		return m_act.on_int_literal(tok);
	
	}else if(tok.is(token::float_lit)){
		return m_act.on_float_literal(tok);
	
	} else if(tok.is_bool_lit()){
		return m_act.on_bool_literal(tok);
	
	} else if (tok.is(token::identifier)){
		return m_act.on_identifier_expression(tok);

	} else if(tok.is(token::lparen)){

		Expr* expr = parse_expression();

		expect(token::rparen);

		return expr;
	}

	throw std::runtime_error("Expected Primary Expression, actual: " 
							+ tok.get_lexme().str());
}


Expr*
parser::parse_expression()
{
	if(is_eof())
		return nullptr;

	return parse_assignment_expression();
}	

Expr*
parser::parse_assignment_expression()
{
	Expr* e1 = parse_conditional_expression();

	if(next_token_is(token::equal)){

		//consume equal
		consume();

		Expr* e2 = parse_assignment_expression();
		return m_act.on_assignment_expression(e1,e2);
	}

	return e1;
}

Expr*
parser::parse_conditional_expression()
{
	Expr* cond = parse_or_expression();

	if(next_token_is(token::qmark)){

		//consume qmark
		consume();

		Expr* e1 = parse_expression();

		//expect colon
		expect(token::colon);

		Expr* e2 = parse_conditional_expression();

		cond = m_act.on_conditional_expression(cond,e1,e2);
	}

	return cond;
}

Expr*
parser::parse_or_expression()
{
	Expr* e1 = parse_and_expression();

	if(next_token_is(token::or_kw)){

		//consume or
		consume();

		Expr* e2 = parse_or_expression();

		e1 = m_act.on_or_expression(e1,e2);
	}

	return e1;
}

Expr*
parser::parse_and_expression()
{
	Expr* e1 = parse_equality_expression();

	if(next_token_is(token::and_kw)){

		//consume and
		consume();

		Expr* e2 = parse_and_expression();

		e1 = m_act.on_and_expression(e1,e2);
	}

	return e1;
}

Expr*
parser::parse_equality_expression()
{

	Expr* e1  = parse_relational_expression();

	if(next_token_is(token::eq_eq)){
		//consume equal equal
		consume();

		Expr* e2 = parse_equality_expression();
		e1 = m_act.on_equals_expression(e1,e2);	
		
	}else if(next_token_is(token::n_eq)){
		//consume not equal
		consume();

		Expr* e2 = parse_equality_expression();
		e1 = m_act.on_not_equals_expression(e1,e2);

	}
	
	return e1;
}

Expr*
parser::parse_relational_expression()
{
	Expr* e1 = parse_additive_expression();

	if(next_token_is(token::lt)){

		consume();

		Expr* e2 = parse_relational_expression();

		e1 = m_act.on_lt_expression(e1,e2);

	} else if(next_token_is(token::gt)){
		//consume greater than 
		consume();

		Expr* e2 = parse_relational_expression();

		e1 = m_act.on_gt_expression(e1,e2);

	} else if(next_token_is(token::lt_eq)){
		//consume less than or equal
		consume();

		Expr* e2 = parse_relational_expression();

		e1 = m_act.on_lt_eq_expression(e1,e2);

	} else if(next_token_is(token::gt_eq)){
		//consume greater than or equal
		consume();

		Expr* e2 = parse_relational_expression();

		e1 = m_act.on_gt_eq_expression(e1,e2);
	}

	return e1;
}

Expr*
parser::parse_additive_expression()
{

	Expr* e1 = parse_multiplicative_expression();

	if(next_token_is(token::plus)){
		//consume plus
		consume();

		Expr* e2 = parse_additive_expression(); 
		e1 = m_act.on_add_expression(e1,e2);
	
	}else if(next_token_is(token::minus)){
		//consume minus
		consume();

		Expr* e2 = parse_additive_expression();
		e1 = m_act.on_sub_expression(e1,e2);
		
	}

	return e1;
}

Expr*
parser::parse_multiplicative_expression()
{
	Expr* e1 = parse_unary_expression();

	if(next_token_is(token::mult)){
		//consume multiplication
		consume();

		Expr* e2 = parse_multiplicative_expression();
		e1 = m_act.on_mult_expression(e1,e2);
	
	} else if(next_token_is(token::div)){
		//consume division sign
		consume();

		Expr* e2 = parse_multiplicative_expression();
		e1 = m_act.on_div_expression(e1,e2);

	} else if(next_token_is(token::percent)){
		//consume percent sign
		consume();

		Expr* e2 = parse_multiplicative_expression();
		e1 = m_act.on_remainder_expression(e1,e2);

	}

	return e1;
}

Expr*
parser::parse_unary_expression()
{	

	if(next_token_is(token::minus)){
		//consume minus
		consume();

		Expr* e2 = parse_unary_expression();
		return m_act.on_negation_expression(e2); 

	} else if(next_token_is(token::div)) {
		//consume division
		consume();

		Expr* e2 = parse_unary_expression();
		return m_act.on_reciprocal_expression(e2); 	
			
	} else if(next_token_is(token::not_kw)) {
		//consume not keyword
		consume();

		Expr* e2 = parse_unary_expression();
		return m_act.on_lnegation_expression(e2); 	
			
	}
	
	Expr* e1 = parse_postfix_expression();

	return e1;
}


Expr*
parser::parse_postfix_expression()
{
	Expr* e1 = parse_primary_expression();

	if(next_token_is(token::lparen)){
		//consume left parenthesis
		consume();

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

	while(next_token_is(token::comma)){
		//consume comma
		consume();

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