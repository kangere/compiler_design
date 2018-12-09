#pragma once

#include <vector>
#include "factory.hpp"


class Builder{
private:

	//error count;
	int errors;

	//factory member
	Ast_Factory f;

	//util functions
	Expr* require_bool(Expr*);
	Expr* convert_value(Expr*);
	std::pair<Expr*,Expr*> require_same(Expr*,Expr*);
	std::pair<Expr*,Expr*> is_same_arithmetic(Expr*,Expr*);
	Expr* require_arithmetic(Expr*);
	Expr* require_ref(Expr*);
	Expr* require_function(Expr*);

public:

	Builder()
	:errors(0)
	{}

	//Types
	Type* int_type() { return f.int_t(); }

	Type* float_type() { return f.float_t(); }

	Type* bool_type() { return f.bool_t(); }

	Type* func_type() { return f.func_t(); }

	//return num errors
	int num_errors() const
	{ return errors;}

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

	Expr* make_reciprocal(Expr* e);

	Expr* make_assignment(Expr* e1,Expr* e2);

	Expr* make_id(Decl* d);

	Expr* make_call(std::initializer_list<Expr*>);
	Expr* make_call(std::vector<Expr*>);


	//Statements
	Stmt* make_break();

	Stmt* make_continue();

	Stmt* make_return(Expr*e);

	Stmt* make_while(Expr* e, Stmt* s);

	Stmt* make_if(Expr* e ,Stmt* s1,Stmt* s2);

	Stmt* make_block(std::initializer_list<Stmt*>);

	Stmt* make_block(std::vector<Stmt*>);

	Stmt* make_expr(Expr* e);

	Stmt* make_decl(Decl* d);

	Stmt* skip(){ return f.skip_s();}


	//Declarations

	Decl* make_var(std::string,Type*,Expr*);
	Decl* make_var(std::string,Type*);

	Decl* make_ref(std::string,Type*,Expr*);

	//Implement
	Decl* make_func(std::string,Type*,Stmt*);
	Decl* make_func(std::string,Type*);

};