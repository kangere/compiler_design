#include "decl.hpp"
#include "expr.hpp"
#include "stmt.hpp"

#include <iostream>

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

}
static void
s_expr_binop(std::ostream& os, Binop_expr* e)
{

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