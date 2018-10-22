#pragma once

#include "type.hpp"
#include "expr.hpp"
#include "decl.hpp"
#include "stmt.hpp"
//Factory classes 
//to abstract creation of Expressions, Statements, Declarations

class Ast_Factory {
public:
	//types
	Int_type* int_t()
	{ return new Int_type();}

	Float_type* float_t()
	{ return new Float_type();}

	Bool_type* bool_t()
	{ return new Bool_type();}

	//Literal expression 
	template<typename T, typename V>
	T* literal(V v)
	{ return new T(v);}

	//Id expression
	Id_expr* make_id(Decl* d, Type* t)
	{ return new Id_expr(d, new Ref_type(t));}

	//Unary Operations Expressions
	template<typename T>
	T* make_unop(Expr* e, Type* t)
	{ return new T(e,t);}

	//Binary Operation Expression
	template<typename T>
	T* make_binop(Expr* e1, Expr* e2, Type* t)
	{ return new T(e1,e2,t);}

	//boolean binary expression
	template<typename T>
	T* make_binop(Expr* e1, Expr* e2)
	{ return new T(e1,e2);}


	//tuple creation
	/*template<typename T,typename E>
	T* make_tuple(E*... e,Type* t)
	{ return new T(e,t);}*/

	//Conditional Expressions
	Cond_expr* make_cond(Expr* e1, Expr* e2, Expr* e3, Type* t)
	{ return new Cond_expr(e1,e2,e3,t);}
};

