#include "actions.hpp"
#include <string>


Expr*
actions::on_bool_literal(token const& tok)
{
	if(tok.is(token::true_kw))
		return m_builder.make_bool(true);
	
	return m_builder.make_bool(false);
}

Expr*
actions::on_int_literal(token const& tok)
{
	int n = std::stoi(tok.get_lexme().str());

	return m_builder.make_int(n);
}

Expr*
actions::on_float_literal(token const& tok)
{
	float f = std::stoi(tok.get_lexme().str());

	return m_builder.make_float(f);
}

Expr*
actions::on_identifier_expression(token const& tok)
{
	Decl* d = m_stack.lookup(tok.get_lexme());

	if(!d)
		throw std::runtime_error("identifier " + 
			tok.get_lexme().str() + " has not been declared");

	return m_builder.make_id(d);
}

Expr*
actions::on_lnegation_expression(Expr* arg)
{
	return m_builder.make_lneg(arg);
}

Expr*
actions::on_negation_expression(Expr* arg)
{
	return m_builder.make_neg(arg);
}

Expr*
actions::on_reciprocal_expression(Expr* arg)
{
	return m_builder.make_reciprocal(arg);
}

Expr*
actions::on_conditional_expression(Expr* e1, Expr* e2, Expr* e3)
{
	return m_builder.make_conditional(e1,e2,e3);
}

Expr*
actions::on_or_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_or(e1,e2);
}

Expr*
actions::on_and_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_and(e1,e2);
}

Expr*
actions::on_assignment_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_assignment(e1,e2);
}

Expr*
actions::on_equals_expression(Expr* e1,Expr* e2)
{
	return m_builder.make_eq(e1,e2);
}

Expr*
actions::on_not_equals_expression(Expr* e1,Expr* e2)
{
	return m_builder.make_neq(e1,e2);
}

Expr*
actions::on_lt_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_lt(e1,e2);
}

Expr*
actions::on_gt_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_gt(e1,e2);
}

Expr*
actions::on_lt_eq_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_lteq(e1,e2);
}

Expr*
actions::on_gt_eq_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_gteq(e1,e2);
}

Expr*
actions::on_add_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_add(e1,e2);
}

Expr*
actions::on_sub_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_sub(e1,e2);
}

Expr*
actions::on_mult_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_mult(e1,e2);
}

Expr*
actions::on_div_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_div(e1,e2);
}

Expr*
actions::on_remainder_expression(Expr* e1, Expr* e2)
{
	return m_builder.make_rem(e1,e2);
}

Expr*
actions::on_call_expression(std::vector<Expr*> vec)
{
	return m_builder.make_call(vec);
}



//Statements
Stmt*
actions::on_block_statement(std::vector<Stmt*> s)
{
	return m_builder.make_block(s);
}

Stmt*
actions::on_return_statement(Expr* e)
{
	return m_builder.make_return(e);
}

Stmt*
actions::on_while_statement(Expr* e, Stmt* s)
{
	return m_builder.make_while(e,s);
}

Stmt*
actions::on_if_statement(Expr* e, Stmt* s1, Stmt* s2)
{
	return m_builder.make_if(e,s1,s2);
}

Stmt*
actions::on_expr_statement(Expr* e)
{
	return m_builder.make_expr(e);
}

Stmt*
actions::on_decl_statement(Decl* d)
{
	return m_builder.make_decl(d);
}


//Declarations
Decl*
actions::on_function_declaration(token tok,Type* t){

	scope current = get_current_scope();

	Decl* fun = m_builder.make_func(tok.get_lexme().str(),t);

	current.declare(tok.get_lexme(),fun);

	return fun;
}

Decl*
actions::finish_function_declaration(Decl* d, Stmt* s)
{
	Func_decl* fun = static_cast<Func_decl*>(d);

	fun->set_block_stmt(s);

	return fun;
}

Decl*
actions::finish_variable_declaration(Decl* d, Expr* e)
{
	Var_decl* var = static_cast<Var_decl*>(d);

	var->set_initializer(e);

	return var;
}

Decl*
actions::on_variable_declaration(token tok, Type* t)
{	
	scope current = get_current_scope();

	Decl* var = m_builder.make_var(tok.get_lexme().str(),t);

	current.declare(tok.get_lexme(),var);

	return var;
}


Decl*
actions::on_reference_declaration(token tok, Type* t, Expr* e)
{
	if(!m_stack.lookup(tok.get_lexme()))
		throw std::runtime_error("Referencing undeclared object");


	return m_builder.make_ref(tok.get_lexme().str(),t,e);
}