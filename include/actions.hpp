#pragma once


#include "builder.hpp"
#include "token.hpp"
#include "scope.hpp"
#include <string>


class actions{
private:
	Builder m_builder;
	scope_stack m_stack;


public:

	//types
	Type* on_int_type() { return m_builder.int_type(); }

	Type* on_float_type() { return m_builder.float_type(); }

	Type* on_bool_type() { return m_builder.bool_type(); }

	Type* on_func_type() { return m_builder.func_type(); }


	//scope
	void enter_scope(){
		 scope s;
		 m_stack.push_back(s); 
	}


	void leave_scope(){ m_stack.pop_back(); }

	scope get_current_scope() { return m_stack.back();}

	//Expressions
	Expr* on_bool_literal(token const&);
	Expr* on_int_literal(token const&);
	Expr* on_float_literal(token const&);

	Expr* on_identifier_expression(token const&);

	//unary expressions
	Expr* on_lnegation_expression(Expr*);
	Expr* on_negation_expression(Expr*);
	Expr* on_reciprocal_expression(Expr*);

	Expr* on_conditional_expression(Expr*,Expr*,Expr*);
	Expr* on_assignment_expression(Expr*,Expr*);

	Expr* on_or_expression(Expr*,Expr*);
	Expr* on_and_expression(Expr*,Expr*);

	//equality expression
	Expr* on_equals_expression(Expr*,Expr*);
	Expr* on_not_equals_expression(Expr*,Expr*);

	//relational expressions
	Expr* on_lt_expression(Expr*,Expr*);
	Expr* on_gt_expression(Expr*,Expr*);
	Expr* on_lt_eq_expression(Expr*,Expr*);
	Expr* on_gt_eq_expression(Expr*,Expr*);

	//additive expression
	Expr* on_add_expression(Expr*,Expr*);
	Expr* on_sub_expression(Expr*,Expr*);

	//multiplicative expression
	Expr* on_mult_expression(Expr*,Expr*);
	Expr* on_div_expression(Expr*,Expr*);
	Expr* on_remainder_expression(Expr*,Expr*);

	//call expression
	Expr* on_call_expression(std::vector<Expr*>);

	//Statements
	Stmt* on_empty_statement()
	{return m_builder.skip();}

	Stmt* on_break_statement()
	{ return m_builder.make_break(); }

	Stmt* on_continue_statement()
	{ return m_builder.make_continue(); }

	Stmt* on_return_statement(Expr*);

	Stmt* on_while_statement(Expr*,Stmt*);

	Stmt* on_if_statement(Expr*,Stmt*,Stmt*);

	Stmt* on_block_statement(std::vector<Stmt*>);

	Stmt* on_expr_statement(Expr*);

	Stmt* on_decl_statement(Decl*);

	//Declarations
	Decl* finish_variable_declaration(Decl* decl,Expr* expr);
	Decl* on_variable_declaration(token tok,Type* type);
	
	Decl* on_reference_declaration(token tok,Type* type,Expr* expr);
	
	Decl* on_function_declaration(token tok,Type* type);
	Decl* finish_function_declaration(Decl* d, Stmt* s);

};