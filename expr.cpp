#include "expr.hpp"
#include "debug.hpp"
#include <iostream>

static void 
print_val(Expr* e)
{
	if(e->get_kind() == int_kind)
	{
		Int_expr *in = static_cast<Int_expr*>(e);
		std::cout << in->get_value();
	} 
	else if(e->get_kind() == float_kind)
	{
		Float_expr *fl = static_cast<Float_expr*>(e);
		std::cout << fl->get_value() ;
	} 
	else if(e->get_kind() == bool_kind)
	{
		Bool_expr *b = static_cast<Bool_expr*>(e);
		std::cout << (b->get_value() ? "true" : "false");
	}
	
}

static void
print_unop(Unop_expr* un)
{
	if(un->get_operator() == logneg_uop)
		std::cout << "!" ;
	else if(un->get_operator() == neg_uop)
		std::cout << "-";
	
	print(un->get_m(0));
	std::cout << std::endl;

}

static void
print_binop(Binop_expr* e)
{
	print(e->get_m(0));

	if(e->get_operator() == and_binop)
		std::cout << " & ";
	else if(e->get_operator() == or_binop)
		std::cout << " || ";
	else if(e->get_operator() == eq_binop)
		std::cout << " == ";
	else if(e->get_operator() == neq_binop)
		std::cout << " != ";
	else if(e->get_operator() == lt_binop)
		std::cout << " < ";	
	else if(e->get_operator() == gt_binop)
		std::cout << " > ";
	else if(e->get_operator() == lt_eq_binop)
		std::cout << " <= ";
	else if(e->get_operator() == gt_eq_binop)
		std::cout << " >= ";
	else if(e->get_operator() == add_binop)
		std::cout << " + ";
	else if(e->get_operator() == sub_binop)
		std::cout << " - ";
	else if(e->get_operator() == mult_binop)
		std::cout << " * ";	
	else if(e->get_operator() == div_binop)
		std::cout << " / ";
	else if(e->get_operator() == rem_binop)
		std::cout << " % ";

	print(e->get_m(1));

	std::cout << std::endl;
}

static void
print_cond(Cond_expr* e)
{
	std::cout << "if" << std::endl;
	print(e->get_m(0));
	std::cout << " then " << std::endl;
	print(e->get_m(1));
	std::cout << " else " << std::endl;
	print(e->get_m(2));
}

static void
print_id(Id_expr* e)
{

}


void print(Expr* e)
{
	switch(e->get_kind())
	{
		case unop_kind:
			return print_unop(static_cast<Unop_expr*>(e));
		case binop_kind:
			return print_binop(static_cast<Binop_expr*>(e));
		case cond_kind:
			return print_cond(static_cast<Cond_expr*>(e));
		case id_kind:
			return print_id(static_cast<Id_expr*>(e));
		case int_kind: 
		case float_kind: 
		case bool_kind:
			return print_val(e);
	}
}

void Expr::debug() const
{
	Debugger dp(std::cerr);

	dp.debug(this);
	
}