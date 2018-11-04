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
indent_func(int indent,std::ostream& out)
{
	for(int i = 0 ; i < indent;i++){
		out << "\t";
	}
}


//Util functions for debugging expressions 
static void
debug_literal(int indent,std::ostream& os,  Expr * e)
{
	indent_func(indent,os);

	print(os,e->get_type());
	os << "_expr: ";

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
debug_unop(int indent,std::ostream& os, Unop_expr* e)
{
	indent_func(indent,os);
	

	switch(e->get_operator()){
		case Unop_expr::logneg_unop:
			os << "log_neg_expr:";
			break;
		case Unop_expr::neg_unop:
			os << "neg_expr:";
			break;
		case Unop_expr::val_unop:
			os << "val_expr:";
			break;
		case Unop_expr::rec_unop:
			os << "rec_expr:";
			break;
	}
	print(os,e->get_type());

	os << (void*)e;
	
	
	skipl(os);
	//increase indent level
	++indent;
	debug(os,e->get_m(0),indent);

} 

static void
debug_binop(int indent,std::ostream& os, Binop_expr* e)
{
	indent_func(indent,os);

	

	switch(e->get_operator()){
		case Binop_expr::and_binop:
			os << "and_expr:";
			break;
		case Binop_expr::or_binop:
			os << "or_expr:";
			break;
		case Binop_expr::eq_binop:
			os << "eq_expr:";
			break;
		case Binop_expr::neq_binop:
			os << "neq_expr:";
			break;
		case Binop_expr::lt_binop:
			os << "lt_expr:";
			break;
		case Binop_expr::gt_binop:
			os << "gt_expr:";
			break;
		case Binop_expr::lt_eq_binop:
			os << "lt_eq_expr:";
			break;
		case Binop_expr::gt_eq_binop:
			os << "gt_eq_expr:";
			break;
		case Binop_expr::add_binop:
			os << "add_expr:";
			break;
		case Binop_expr::sub_binop:
			os << "sub_expr:";
			break;
		case Binop_expr::mult_binop:
			os << "mult_expr:";
			break;
		case Binop_expr::div_binop:
			os << "div_expr:";
			break;
		case Binop_expr::rem_binop:
			os << "rem_expr:";
			break;
		case Binop_expr::assign_binop:
			os << "assign_expr:";
			break;
	}

	print(os,e->get_type());

	os << (void*)e;

	//increase indent level
	++indent;
	skipl(os);
	debug(os,e->get_m(0),indent);
	debug(os,e->get_m(1),indent);

}

//TODO fix conditional indent
static void
debug_cond(int indent,std::ostream& os, Cond_expr* e)
{
	indent_func(indent,os);

	
	os << "if_expr:";
	print(os,e->get_type());
	//increase indent level
	++indent;
	skipl(os);
	debug(os,e->get_m(0),indent);
	skipl(os);
	debug(os,e->get_m(1),indent);
	skipl(os);
	debug(os,e->get_m(2),indent);
}

void debug_idexpr(int indent,std::ostream& os, Id_expr* e)
{
	indent_func(indent,os);

	print(os,e->get_type());
	os << "id_expr: " << (void*)e;

	//increase indent level
	++indent;
	skipl(os);
	debug(os,e->get_decl(),indent);

}

//Debug Expressions
void debug(std::ostream& os,  Expr * e, int indent)
{
	switch(e->get_kind()){
		case Expr::int_expr:
		case Expr::float_expr:
		case Expr::bool_expr:
			return debug_literal(indent,os,e);
		case Expr::unop_expr:
			return debug_unop(indent,os,static_cast<Unop_expr*>(e));
		case Expr::binop_expr:
			return debug_binop(indent,os,static_cast<Binop_expr*>(e));
		case Expr::cond_expr:
			return debug_cond(indent,os, static_cast<Cond_expr*>(e));
		case Expr::id_expr:
			return debug_idexpr(indent,os,static_cast<Id_expr*>(e));

	}
}




//Util functions to debug declarations
static void
debug_var_decl(int indent,std::ostream& os, Var_decl* d)
{
	indent_func(indent,os);

	os << "var_decl " << d->get_name() << ":";
	print(os, d->get_type());
	os << " " << (void*)d;

	//increase indent level
	++indent;
	skipl(os);
	debug(os,d->get_expr(),indent);

}

static void
debug_ref_decl(int indent,std::ostream& os, Ref_decl* d)
{
	indent_func(indent,os);

	os << "ref_decl " << d->get_name() << ":";
	print(os,d->get_type());
	os << " " << (void*)d;

	//increase indent level
	++indent;
	skipl(os);
	debug(os,d->get_expr(),indent);
}

static void
debug_func_decl(int indent,std::ostream& os, Func_decl* d)
{
	indent_func(indent,os);

	os << "func_decl " << d->get_name() << ": " << (void*)d;
	print(os,d->get_type());

	++indent;
	skipl(os);

	for(auto param : d->get_params())
		debug(os,param,indent);

	skipl(os);
	++indent;
	debug(os,d->get_stmt(),indent);


}	

//Debug Declarations
void debug(std::ostream& os, Decl* d,int indent)
{
	switch(d->get_kind()){
		case Decl::var_decl:
			return debug_var_decl(indent,os,static_cast<Var_decl*>(d));
		case Decl::ref_decl:
			return debug_ref_decl(indent,os,static_cast<Ref_decl*>(d));
		case Decl::func_decl:
			return debug_func_decl(indent,os,static_cast<Func_decl*>(d));
	}
}



//Util functions to debug statenents
static void 
debug_while(int indent, std::ostream& os, While_stmt* s)
{
	indent_func(indent,os);

	os << "while_stmt: " << (void*)s;

	++indent;
	skipl(os);
	debug(os,s->get_expr(),indent);
	debug(os,s->get_stmt(),indent);

}

static void 
debug_cmp_stmt(int indent, std::ostream& os, Compound_stmt* s)
{
	indent_func(indent,os);

	os << "cmp_stmt: " << (void*)s;

	++indent;
	skipl(os);

	for(auto stmt : s->get_stmts())
		debug(os,stmt,indent);
}
static void 
debug_return(int indent, std::ostream& os, Return_stmt* s)
{
	indent_func(indent,os);

	os << "return_stmt: " << (void*)s;

	skipl(os);
	++indent;
	debug(os,s->get_expr(),indent);
}

static void 
debug_if_stmt(int indent, std::ostream& os, If_stmt* s)
{
	indent_func(indent,os);

	os << "if_stmt: " << (void*)s;

	++indent;
	skipl(os);
	debug(os,s->get_expr(),indent);
	skipl(os);
	debug(os,s->get_stmt_1(),indent);
	skipl(os);
	debug(os,s->get_stmt_2(),indent);
}

static void 
debug_expr_stmt(int indent, std::ostream& os, Expr_stmt* s)
{
	indent_func(indent,os);

	os << "expr_stmt: " << (void*)s;

	++indent;
	skipl(os);
	debug(os,s->get_expr(),indent);
}
static void 
debug_decl_stmt(int indent, std::ostream& os, Decl_stmt* s)
{
	indent_func(indent,os);

	os << "decl_stmt: " << (void*)s;

	++indent;
	skipl(os);
	debug(os,s->get_decl(),indent);
}


//Debug Statements
void debug(std::ostream& os, Stmt* s, int indent)
{
	switch(s->get_kind()){

		case Stmt::break_stmt:
			os << "break_stmt: " << (void*)s;
			skipl(os);
			break;
		case Stmt::continue_stmt:
			os << "continue_stmt: " << (void*)s;
			skipl(os);
			break;
		case Stmt::while_stmt:
			return debug_while(indent,os,static_cast<While_stmt*>(s));
		case Stmt::compound_stmt:
			return debug_cmp_stmt(indent,os,static_cast<Compound_stmt*>(s));
		case Stmt::if_stmt:
			return debug_if_stmt(indent,os,static_cast<If_stmt*>(s));
		case Stmt::return_stmt:
			return debug_return(indent,os,static_cast<Return_stmt*>(s));
		case Stmt::expr_stmt:
			return debug_expr_stmt(indent,os,static_cast<Expr_stmt*>(s));
		case Stmt::decl_stmt:
			return debug_decl_stmt(indent,os,static_cast<Decl_stmt*>(s));
	}
}