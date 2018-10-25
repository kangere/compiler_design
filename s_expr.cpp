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


//expression util functions
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
			os << "| ";
			break;
		case Binop_expr::eq_binop:
			os << "== ";
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
	open(os);
	os << " ?: ";
	s_expr(os,e->get_m(0));
	s_expr(os,e->get_m(1));
	s_expr(os,e->get_m(2));
	close(os);
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




//DECLARATION s-expr Implementation

//declaration util functions
static void 
var_s_expr(std::ostream& os, Var_decl* d)
{
	open(os);
	os << "var_decl ";
	open(os);
	os << "= " << d->get_name() << " ";
	s_expr(os,d->get_expr());
	close(os);
	close(os);
}

static void 
ref_s_expr(std::ostream& os, Ref_decl* d)
{
	open(os);
	os << "ref_decl ";
	open(os);
	os << "= "<< d->get_name() << " ";
	s_expr(os,d->get_expr());
	close(os);
	close(os);
}

static void 
func_s_expr(std::ostream& os, Func_decl* d)
{
	open(os);
	os << "func ";

	open(os);
	for(auto param : d->get_params()){
		s_expr(os,param);
	}
	close(os);

	open(os);
	s_expr(os,d->get_stmt());
	close(os);

	close(os);

}
	


void
s_expr(std::ostream& os, Decl* d)
{
	switch(d->get_kind()){
		case Decl::var_decl:
			return var_s_expr(os,static_cast<Var_decl*>(d));
		case Decl::ref_decl:
			return ref_s_expr(os,static_cast<Ref_decl*>(d));
		case Decl::func_decl:
			return func_s_expr(os,static_cast<Func_decl*>(d));
	}
}




//Statements s-expr

//util functions
static void
while_s_expr(std::ostream& os, While_stmt* s)
{
	open(os);
	os << "while_stmt ";
	s_expr(os,s->get_expr());

	s_expr(os,s->get_stmt());

	close(os);
}

static void
compound_s_expr(std::ostream& os, Compound_stmt* s)
{
	open(os);

	for(auto stmt : s->get_stmts())
		s_expr(os,stmt);

	close(os);
}

static void
if_s_expr(std::ostream& os, If_stmt* s)
{
	open(os);

	os << "if ";
	s_expr(os,s->get_expr());
	os << " then ";
	s_expr(os,s->get_stmt_1());
	os << " else ";
	s_expr(os,s->get_stmt_2());

	close(os);
}

static void
return_s_expr(std::ostream& os, Return_stmt* s)
{
	open(os);
	os << " return ";
	s_expr(os,s->get_expr());
	close(os);

}

static void
expr_s_expr(std::ostream& os, Expr_stmt* s)
{
	open(os);
	os << " expr_stmt ";
	s_expr(os,s->get_expr());
	close(os);
	
}

static void
decl_s_expr(std::ostream& os, Decl_stmt* s)
{
	open(os);
	os << " decl_stmt ";
	s_expr(os,s->get_decl());
	close(os);
}

void
s_expr(std::ostream& os, Stmt* s)
{
	switch(s->get_kind()){
		case Stmt::break_stmt:
			os << "break";
			break;
		case Stmt::continue_stmt:
			os << "continue";
			break;
		case Stmt::while_stmt:
			return while_s_expr(os,static_cast<While_stmt*>(s));
		case Stmt::compound_stmt:
			return compound_s_expr(os,static_cast<Compound_stmt*>(s));
		case Stmt::if_stmt:
			return if_s_expr(os,static_cast<If_stmt*>(s));
		case Stmt::return_stmt:
			return return_s_expr(os,static_cast<Return_stmt*>(s));
		case Stmt::expr_stmt:
			return expr_s_expr(os,static_cast<Expr_stmt*>(s));
		case Stmt::decl_stmt:
			return decl_s_expr(os,static_cast<Decl_stmt*>(s));

	}
}