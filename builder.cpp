#include "builder.hpp"
#include <iostream>
#include <vector>
#include <string>

Expr* 
Builder::make_and(Expr* e1, Expr* e2)
{
	require_bool(e1);
	require_bool(e2);	

	return f.and_e(e1,e2);
}

Expr*
Builder::make_or(Expr* e1, Expr* e2)
{
	require_bool(e1);
	require_bool(e2);

	return f.or_e(e1,e2);	
}

Expr*
Builder::make_lneg(Expr* e)
{
	
	require_bool(e);

	return f.lneg_e(e,f.bool_t());
}

//TODO : Finish Implementation
Expr*
Builder::make_conditional(Expr* e1, Expr* e2, Expr* e3)
{
	require_bool(e1);

	e2 = convert_value(e2);
	e3 = convert_value(e3);

	require_same(e2,e3);

	return f.cond_e(e1,e2,e3,e2->get_type());
}

Expr*
Builder::make_eq(Expr* e1, Expr* e2)
{
	require_same(e1,e2);
	return f.eq_e(e1,e2);
}

Expr*
Builder::make_neq(Expr* e1, Expr* e2)
{
	require_same(e1,e2);
	return f.neq_e(e1,e2);	
}

Expr*
Builder::make_gt(Expr* e1, Expr* e2)
{
	is_same_arithmetic(e1,e2);

	return f.gt_e(e1,e2);
}

Expr*
Builder::make_lt(Expr* e1, Expr* e2)
{
	is_same_arithmetic(e1,e2);

	return f.lt_e(e1,e2);
}

Expr*
Builder::make_gteq(Expr* e1, Expr* e2)
{
	is_same_arithmetic(e1,e2);

	return f.gteq_e(e1,e2);
}

Expr*
Builder::make_lteq(Expr* e1, Expr* e2)
{
	is_same_arithmetic(e1,e2);

	return f.lteq_e(e1,e2);
}

Expr*
Builder::make_add(Expr* e1, Expr* e2)
{
	is_same_arithmetic(e1,e2);

	return f.add_e(e1,e2,e1->get_type());
}

Expr*
Builder::make_sub(Expr* e1, Expr* e2)
{
	is_same_arithmetic(e1,e2);

	return f.sub_e(e1,e2,e1->get_type());
}

Expr*
Builder::make_mult(Expr* e1, Expr* e2)
{
	is_same_arithmetic(e1,e2);

	return f.mult_e(e1,e2,e1->get_type());
}

Expr*
Builder::make_div(Expr* e1, Expr* e2)
{
	is_same_arithmetic(e1,e2);

	return f.div_e(e1,e2,e1->get_type());
}

Expr*
Builder::make_rem(Expr* e1, Expr* e2)
{
	is_same_arithmetic(e1,e2);

	return f.rem_e(e1,e2,e1->get_type());
}

Expr*
Builder::make_neg(Expr* e)
{
	e = require_arithmetic(e);

	return f.neg_e(e,e->get_type());
}

Expr*
Builder::make_assignment(Expr* e1,Expr* e2)
{

	require_ref(e1);

	e2 = convert_value(e2);

	return f.assign_e(e1,e2,new Ref_type(e2->get_type())); 
}

//Statements
Stmt*
Builder::make_break()
{
	return f.break_s();
}

Stmt*
Builder::make_continue()
{
	return f.continue_s();
}

//TODO
Stmt*
Builder::make_return(Expr* e)
{
	return f.return_s(e);
}

Stmt*
Builder::make_block(std::initializer_list<Stmt*> ss)
{
	return f.compound_s(ss);
}

Stmt*
Builder::make_if(Expr* e ,Stmt* s1,Stmt* s2)
{
	require_bool(e);

	return f.if_s(e,s1,s2);
}

Stmt* 
Builder::make_while(Expr* e, Stmt* s)
{
	require_bool(e);

	return f.while_s(e,s);
}

Stmt*
Builder::make_expr(Expr* e)
{
	return f.expr_s(e);
}

Stmt*
Builder::make_decl(Decl* d)
{
	return f.decl_s(d);
}



//Declarations
Decl*
Builder::make_var(std::string name, Type* t, Expr* e)
{
	if(t->is_ref()){
		Ref_type* ref = static_cast<Ref_type*>(t);

		return f.var_d(name,ref->get_ref_type(),e);
	}

	return f.var_d(name,t,e);
}

Decl*
Builder::make_ref(std::string name, Type* t, Expr* e)
{
	if(t->is_ref()){
		Ref_type* ref = static_cast<Ref_type*>(t);

		return f.ref_d(name,ref->get_ref_type(),e);
	}

	return f.ref_d(name,t,e);
}

Decl*
Builder::make_func(std::string name, Type* t,Stmt* s)
{
	return f.func_d(name,t,s);
}
