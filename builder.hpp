#pragma once

#include <vector>
#include "factory.hpp"


class Builder{
private:
	//factory member
	Ast_Factory f;

	//util functions
	void require_bool(Expr*);
	Expr* convert_value(Expr*);
	void require_same(Expr*,Expr*);
	void is_same_arithmetic(Expr*,Expr*);
	Expr* require_arithmetic(Expr*);

public:

	//literal expressions
	Expr* make_bool(bool b)
	{ return f.bool_e(b); }

	Expr* make_int(int n)
	{ return f.int_e(n);}

	Expr* make_float(float fn)
	{ return f.float_e(fn);}	

	//Logical expressions
	Expr* make_and(Expr* e1, Expr* e2);

	Expr* make_or(Expr* e1, Expr* e2);

	Expr* make_lneg(Expr* e);

	Expr* make_conditional(Expr* e1, Expr* e2, Expr* e3);

	Expr* make_eq(Expr* e1, Expr* e2);

	Expr* make_neq(Expr* e1, Expr* e2);

	Expr* make_gt(Expr* e1, Expr* e2);

	Expr* make_lt(Expr* e1, Expr* e2);

	Expr* make_gteq(Expr* e1, Expr* e2);
	
	Expr* make_lteq(Expr* e1, Expr* e2);

	Expr* make_add(Expr* e1, Expr* e2);

	Expr* make_sub(Expr* e1, Expr* e2);

	Expr* make_mult(Expr* e1, Expr* e2);

	Expr* make_div(Expr* e1, Expr* e2);

	Expr* make_rem(Expr* e1, Expr* e2);

	Expr* make_neg(Expr* e);


	//Statements
	Stmt* make_break();

	Stmt* make_continue();

	Stmt* make_return(Expr*e);

	Stmt* make_while(Expr* e, Stmt* s);

	Stmt* make_if(Expr* e ,Stmt* s1,Stmt* s2);

	Stmt* make_block(std::initializer_list<Stmt*>);

	Stmt* make_expr(Expr* e);

	Stmt* make_decl(Decl* d);

};