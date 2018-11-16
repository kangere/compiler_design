#pragma once

#include "type.hpp"
#include "expr.hpp"
#include "decl.hpp"
#include "stmt.hpp"
//Factory classes 
//to abstract creation of Expressions, Statements, Declarations and Types

class Ast_Factory {

public:
	//TYPES
	Int_type* int_t()
	{ return new Int_type();}

	Float_type* float_t()
	{ return new Float_type();}

	Bool_type* bool_t()
	{ return new Bool_type();}

	Func_type* func_t()
	{return new Func_type();}

	//EXPRESSIONS
	Bool_expr* bool_e(bool b)
	{return new Bool_expr(b);}

	Int_expr* int_e(int n)
	{return new Int_expr(n);}

	Float_expr* float_e(float f)
	{ return new Float_expr(f);}

	Id_expr* id_e(Decl* d, Type* t)
	{ return new Id_expr(d, new Ref_type(t));}

	//Unary Operations Expressions
	Logneg_expr* lneg_e(Expr* e, Type* t)
	{return new Logneg_expr(e,t);}

	Negation_expr* neg_e(Expr* e, Type* t)
	{return new Negation_expr(e,t);}

	Reciprocal_expr* rec_e(Expr* e, Type* t)
	{return new Reciprocal_expr(e,t);}

	//Binary Operation Expression
	Add_expr* add_e(Expr* e1, Expr* e2, Type* t)
	{ return new Add_expr(e1,e2,t);}

	Sub_expr* sub_e(Expr* e1, Expr* e2, Type* t)
	{ return new Sub_expr(e1,e2,t);}

	Mult_expr* mult_e(Expr* e1, Expr* e2, Type* t)
	{ return new Mult_expr(e1,e2,t);}

	Div_expr* div_e(Expr* e1, Expr* e2, Type* t)
	{ return new Div_expr(e1,e2,t);}

	Rem_expr* rem_e(Expr* e1, Expr* e2, Type* t)
	{ return new Rem_expr(e1,e2,t);}

	Assignment_expr* assign_e(Expr* e1, Expr* e2, Type* t)
	{ return new Assignment_expr(e1,e2,t);}

	And_expr* and_e(Expr* e1, Expr* e2)
	{ return new And_expr(e1,e2);}

	Or_expr* or_e(Expr* e1, Expr* e2)
	{ return new Or_expr(e1,e2);}

	Eq_expr* eq_e(Expr* e1, Expr* e2)
	{ return new Eq_expr(e1,e2);}

	Neq_expr* neq_e(Expr* e1, Expr* e2)
	{ return new Neq_expr(e1,e2);}

	Lt_expr* lt_e(Expr* e1, Expr* e2)
	{ return new Lt_expr(e1,e2);}

	Gt_expr* gt_e(Expr* e1, Expr* e2)
	{ return new Gt_expr(e1,e2);}

	Lteq_expr* lteq_e(Expr* e1, Expr* e2)
	{ return new Lteq_expr(e1,e2);}

	Gteq_expr* gteq_e(Expr* e1, Expr* e2)
	{ return new Gteq_expr(e1,e2);}


	Cond_expr* cond_e(Expr* e1, Expr* e2, Expr* e3, Type* t)
	{ return new Cond_expr(e1,e2,e3,t);}

	Func_expr* call_e(std::initializer_list<Expr*> l, Type* t)
	{return new Func_expr(l,t);}

	Func_expr* call_e(std::vector<Expr*> l, Type* t)
	{return new Func_expr(l,t);}


	//DECLARATIONS
	Var_decl* var_d(std::string name, Type* t, Expr* e)
	{ return new Var_decl(name,t,e);}

	Ref_decl* ref_d(std::string name, Type* t, Expr* e)
	{ return new Ref_decl(name,t,e);}

	Func_decl* func_d(std::string name, Type* t,Stmt* s)
	{ return new Func_decl(name,t,s); }



	//STATEMENTS
	Break_stmt* break_s()
	{return new Break_stmt();}

	Continue_stmt* continue_s()
	{return new Continue_stmt();}

	Compound_stmt* compound_s()
	{return new Compound_stmt();}

	Compound_stmt* compound_s(std::initializer_list<Stmt*> ss)
	{ return new Compound_stmt(ss);}

	Expr_stmt* expr_s(Expr* e)
	{ return new Expr_stmt(e);}

	Return_stmt* return_s(Expr* e)
	{ return new Return_stmt(e);}

	While_stmt* while_s(Expr* e, Stmt* s)
	{ return new While_stmt(e,s);}


	If_stmt* if_s(Expr* e, Stmt* s1, Stmt* s2)
	{ return new If_stmt(e,s1,s2);}

	Decl_stmt* decl_s(Decl* d)
	{return new Decl_stmt(d);}


};

