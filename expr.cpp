#include "expr.hpp"
#include <iostream>

static void 
print_val(Expr* e)
{
	if(e->get_kind() == int_kind)
	{
		Int_expr *in = static_cast<Int_expr*>(e);
		std::cout << in->get_value() << std::endl;
	} else if(e->get_kind() == float_kind)
	{
		Float_expr *fl = static_cast<Float_expr*>(e);
		std::cout << fl->get_value() << std::endl;
	}
	
}

static void
print_unop(Unop_expr* un)
{
	if(un->get_operator() == logneg_uop)
		std::cout << "not " ;
	else if(un->get_operator() == neg_uop)
		std::cout << "- ";
	
	print(un->get_m(0));

}

void print(Expr* e)
{
	switch(e->get_kind())
	{
		case unop_kind:
			return print_unop(static_cast<Unop_expr*>(e));
		default:
			return print_val(e);
	}
}