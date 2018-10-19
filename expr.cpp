#include "expr.hpp"
#include <iostream>

static void 
print_val(Expr* e)
{
	if(e->get_kind() == Expr::int_expr)
	{
		Int_expr *in = static_cast<Int_expr*>(e);
		std::cout << in->get_value();
	} 
	else if(e->get_kind() == Expr::float_expr)
	{
		Float_expr *fl = static_cast<Float_expr*>(e);
		std::cout << fl->get_value() ;
	} 
	else if(e->get_kind() == Expr::bool_expr)
	{
		Bool_expr *b = static_cast<Bool_expr*>(e);
		std::cout << (b->get_value() ? "true" : "false");
	}
	
}

static void
print_unop(Unop_expr* un)
{
	if(un->get_operator() == Unop_expr::logneg_unop)
		std::cout << "!" ;
	else if(un->get_operator() == Unop_expr::neg_unop)
		std::cout << "-";
	else if(un->get_operator() == Unop_expr::rec_unop)
		std::cout << "1/";
	
	print(un->get_m(0));
	std::cout << std::endl;

}

static void
print_binop(Binop_expr* e)
{
	print(e->get_m(0));

	if(e->get_operator() == Binop_expr::and_binop)
		std::cout << " & ";
	else if(e->get_operator() == Binop_expr::or_binop)
		std::cout << " || ";
	else if(e->get_operator() == Binop_expr::eq_binop)
		std::cout << " == ";
	else if(e->get_operator() == Binop_expr::neq_binop)
		std::cout << " != ";
	else if(e->get_operator() == Binop_expr::lt_binop)
		std::cout << " < ";	
	else if(e->get_operator() == Binop_expr::gt_binop)
		std::cout << " > ";
	else if(e->get_operator() == Binop_expr::lt_eq_binop)
		std::cout << " <= ";
	else if(e->get_operator() == Binop_expr::gt_eq_binop)
		std::cout << " >= ";
	else if(e->get_operator() == Binop_expr::add_binop)
		std::cout << " + ";
	else if(e->get_operator() == Binop_expr::sub_binop)
		std::cout << " - ";
	else if(e->get_operator() == Binop_expr::mult_binop)
		std::cout << " * ";	
	else if(e->get_operator() == Binop_expr::div_binop)
		std::cout << " / ";
	else if(e->get_operator() == Binop_expr::rem_binop)
		std::cout << " % ";
	else if(e->get_operator() == Binop_expr::assign_binop)
		std::cout << " = ";

	print(e->get_m(1));

	std::cout << std::endl;
}

static void
print_cond(Cond_expr* e)
{
	
	print(e->get_m(0));
	std::cout << " ? " ;
	print(e->get_m(1));
	std::cout << " : " ;
	print(e->get_m(2));
}

static void
print_id(Id_expr* e)
{
	std::cout << "id_expr: ";
	print(e->get_decl());
}


void print(Expr* e)
{
	switch(e->get_kind())
	{
		case Expr::unop_expr:
			return print_unop(static_cast<Unop_expr*>(e));
		case Expr::binop_expr:
			return print_binop(static_cast<Binop_expr*>(e));
		case Expr::cond_expr:
			return print_cond(static_cast<Cond_expr*>(e));
		case Expr::id_expr:
			return print_id(static_cast<Id_expr*>(e));
		case Expr::int_expr: 
		case Expr::float_expr: 
		case Expr::bool_expr:
			return print_val(e);
	}
}

