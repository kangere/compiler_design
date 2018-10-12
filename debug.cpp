#include "type.hpp"
#include "decl.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include <iostream>

//All AST structures have a debug function 
//that is implemented in this file

//util functions
//skip line
static void
skipl(std::ostream& out)
{
	out << std::endl;
}

static void
indent(std::ostream& out)
{
	out << "\t";
}

//skip line  and indent output stream
static void
skipl_indent(std::ostream& out)
{
	skipl(out);
	indent(out);
}


//Expressions debug functions 
static void
debug_literal(std::ostream& os,  Expr * e)
{
	
	print(os,e->get_type());
	os << ": ";

	if(e->get_kind() == Expr::bool_expr)
	{
		Bool_expr * b = static_cast<Bool_expr*>(e);
		os << (void*)b << ": " <<(b->get_value() ? "true" : "false");
	}
	else if(e->get_kind() == Expr::int_expr)
	{
		Int_expr* in = static_cast<Int_expr*>(e);
		os << (void*)in << ": " << in->get_value(); 
	}
	else if(e->get_kind() == Expr::float_expr)
	{
		Float_expr* f = static_cast<Float_expr*>(e);
		os << (void*)f << ": " << f->get_value();
	}

	skipl(os);
}

static void
debug_unop(std::ostream& os, Unop_expr* e)
{
	print(os,e->get_type());

	switch(e->get_operator()){
		case Unop_expr::logneg_unop:
			os << ":log_neg_expr ";
			break;
		case Unop_expr::neg_unop:
			os << ":neg_expr ";
			break;
		case Unop_expr::val_unop:
			os << ":val_expr ";
			break;
		case Unop_expr::rec_unop:
			os << ":rec_expr ";
			break;
	}

	os << (void*)e;
	
	skipl_indent(os);
	debug(os,e->get_m(0));

} 

static void
debug_binop(std::ostream& os, Binop_expr* e)
{
	print(os,e->get_type());

	switch(e->get_operator()){
		case Binop_expr::and_binop:
			os << ":and_expr ";
			break;
		case Binop_expr::or_binop:
			os << ":or_expr ";
			break;
		case Binop_expr::eq_binop:
			os << ":eq_expr ";
			break;
		case Binop_expr::neq_binop:
			os << ":neq_expr ";
			break;
		case Binop_expr::lt_binop:
			os << ":lt_expr ";
			break;
		case Binop_expr::gt_binop:
			os << ":gt_expr ";
			break;
		case Binop_expr::lt_eq_binop:
			os << ":lt_eq_expr ";
			break;
		case Binop_expr::gt_eq_binop:
			os << ":gt_eq_expr ";
			break;
		case Binop_expr::add_binop:
			os << ":add_expr ";
			break;
		case Binop_expr::sub_binop:
			os << ":sub_expr ";
			break;
		case Binop_expr::mult_binop:
			os << ":mult_expr ";
			break;
		case Binop_expr::div_binop:
			os << ":div_expr ";
			break;
		case Binop_expr::rem_binop:
			os << ":rem_expr ";
			break;
		case Binop_expr::assign_binop:
			os << ":assign_expr ";
			break;
		case Binop_expr::func_binop:
			os << ":func_expr ";
			break;
	}

	os << (void*)e;

	skipl_indent(os);
	debug(os,e->get_m(0));
	indent(os);
	debug(os,e->get_m(1));

}

static void
debug_cond(std::ostream& os, Cond_expr* e)
{
	print(os,e->get_type());
	os << "if_expr";
	skipl_indent(os);
	debug(os,e->get_m(0));
	indent(os);
	debug(os,e->get_m(1));
	indent(os);
	debug(os,e->get_m(2));
}

void debug(std::ostream& os,  Expr * e)
{
	switch(e->get_kind()){
		case Expr::int_expr:
		case Expr::float_expr:
		case Expr::bool_expr:
			return debug_literal(os,e);
		case Expr::unop_expr:
			return debug_unop(os,static_cast<Unop_expr*>(e));
		case Expr::binop_expr:
			return debug_binop(os,static_cast<Binop_expr*>(e));
		case Expr::cond_expr:
			return debug_cond(os, static_cast<Cond_expr*>(e));
		case Expr::id_expr:
			break;

	}
}