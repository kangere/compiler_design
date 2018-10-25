#pragma once

#include "factory.hpp"

class Builder{
private:
	//factory member
	Ast_Factory f;

public:

	Bool_expr* make_bool(bool b)
	{ return f.bool_e(b); }

	Int_expr* make_int(int n)
	{ return f.int_e(n);}

	Float_expr* make_float(float fn)
	{ return f.float_e(fn);}	

	//Logical expressions
	And_expr* make_and(Expr* e1, Expr* e2);

	Or_expr* make_or(Expr* e1, Expr* e2);

	Logneg_expr* make_not(Expr* e1, Expr* e2);


};