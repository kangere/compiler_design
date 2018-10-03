#include "expr.hpp"
#include <iostream>

static void 
print_val(Expr* e)
{
	if(e->get_kind() == int_kind)
	{
		Int_expr *in = static_cast<Int_expr*>(e);
		std::cout << in->get_value();
	}
	
}

static void
print_unop(Unary_expr* un)
{
	if(un->get_operator() == logical_neg_uop)
		std::cout << "not " ;
	else if(un->get_operator() == neg_uop)
		std::cout << "- ";
	
	print(un->get_m_expr(1));

	std::cout << std::endl;
}

void print(Expr* e)
{
	switch(e->get_kind())
	{
		case unary_kind:
			return print_unop(static_cast<Unary_expr*>(e));
		default:
			return print_val(e);
	}
}