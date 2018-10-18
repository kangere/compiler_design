#include "decl.hpp"
#include "expr.hpp"
#include "stmt.hpp"

#include <iostream>

//util functions

//open brackets
static void
open(std::ostream& os){
	os << "(";
}
//close brackets
static void
close(std::ostream& os){
	os << ")";
}



static void
s_expr_lit(std::ostream& os, Expr* e)
{
	if(e->get_kind() == Expr::int_expr){

		Int_expr* in = static_cast<Int_expr*>(e);
		os << in->get_value();

	}else if(e->get_kind() == Expr::float_expr){
		
		Float_expr* fl = static_cast<Float_expr*>(e);
		os << fl->get_value();

	}else if(e->get_kind() == Expr::bool_expr){
		
		Bool_expr* bo = static_cast<Bool_expr*>(e);
		os << bo->get_value();
	}
}

static void
s_expr_idexpr(std::ostream& os, Id_expr* e)
{

}

static void
s_expr_unop(std::ostream& os, Unop_expr* e)
{
	open(os);

	switch(e->get_operator()){
		case Unop_expr::logneg_unop:
			os << "not ";
			break;
		case Unop_expr::neg_unop:
			os << "- ";
			break;
		case Unop_expr::rec_unop:
			os << "/ ";
			break;
		case Unop_expr::val_unop:
			os << "";
			break;
	}

	s_expr(os,e->get_m(0));

	close(os);
}
static void
s_expr_binop(std::ostream& os, Binop_expr* e)
{
	open(os);

	switch(e->get_operator()){
		case Binop_expr::and_binop:
			os << "& ";
			break;
		case Binop_expr::or_binop:
			os << "or ";
			break;
		case Binop_expr::eq_binop:
			os << "= ";
			break;
		case Binop_expr::neq_binop:
			os << "!= ";
			break;
		case Binop_expr::lt_binop:
			os << "< ";
			break;
		case Binop_expr::gt_binop:
			os << "> ";
			break;
		case Binop_expr::lt_eq_binop:
			os << "<= ";
			break;
		case Binop_expr::gt_eq_binop:
			os << ">= ";
			break;
		case Binop_expr::add_binop:
			os << "+ ";
			break;
		case Binop_expr::sub_binop:
			os << "- ";
			break;
		case Binop_expr::mult_binop:
			os << "* ";
			break;
		case Binop_expr::div_binop:
			os << "/ ";
			break;
		case Binop_expr::rem_binop:
			os << "/ ";
			break;
		case Binop_expr::assign_binop:
			os << "= ";
			break;
		case Binop_expr::func_binop:
			os << "func ";
			break;
	}

	s_expr(os,e->get_m(0));
	os << " ";
	s_expr(os,e->get_m(1));

	close(os);

}
static void
s_expr_cond(std::ostream& os, Cond_expr* e)
{

}


void 
s_expr(std::ostream& os, Expr* e)
{
	switch(e->get_kind()){
		case Expr::int_expr:
		case Expr::float_expr:
		case Expr::bool_expr:
			return s_expr_lit(os,e);
		case Expr::id_expr:
			return s_expr_idexpr(os,static_cast<Id_expr*>(e));
		case Expr::unop_expr:
			return s_expr_unop(os,static_cast<Unop_expr*>(e));
		case Expr::binop_expr:
			return s_expr_binop(os,static_cast<Binop_expr*>(e));
		case Expr::cond_expr:
			return s_expr_cond(os,static_cast<Cond_expr*>(e));
	}
}