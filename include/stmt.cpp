#include "stmt.hpp"
#include "expr.hpp"
#include <iostream>

static void 
print_expr(Expr_stmt* e)
{
	std::cout << "expr_stmt:";
	print(e->get_expr());
	std::cout << std::endl;
}

static void
print_return(Return_stmt* s)
{
	std::cout << "return ";
	print(s->get_expr());
}

static void
print_cmp(Compound_stmt* s)
{
	std::cout << "compound stmts:" << std::endl;

	for(auto st : s->get_stmts())
		print(st);
	
}

static void
print_while(While_stmt* s)
{
	std::cout << "while ";
	print(s->get_expr());
	std::cout << "\ndo" << std::endl;
	print(s->get_stmt());
	
}

static void
print_if(If_stmt* s)
{
	std::cout <<"if ";
	print(s->get_expr());
	std::cout << "then" <<std::endl;
	print(s->get_stmt_1());
	std::cout << "\nelse" << std::endl;
	print(s->get_stmt_2());
	std::cout << std::endl;
}

static void
print_decl(Decl_stmt* s)
{
	std::cout << "decl_stmt: ";
	print(s->get_decl());
	std::cout << std::endl;
}

void
print(Stmt* s)
{
	switch(s->get_kind()){
		case Stmt::break_stmt:
			std::cout << "break" << std::endl;
			break;
		case Stmt::continue_stmt:
			std::cout << "continue" << std::endl;
			break;
		case Stmt::expr_stmt:
			return print_expr(static_cast<Expr_stmt*>(s));
		case Stmt::return_stmt:
			return print_return(static_cast<Return_stmt*>(s));
		case Stmt::compound_stmt:
			return print_cmp(static_cast<Compound_stmt*>(s));
		case Stmt::while_stmt:
			return print_while(static_cast<While_stmt*>(s));
		case Stmt::if_stmt:
			return print_if(static_cast<If_stmt*>(s));
		case Stmt::decl_stmt:
			return print_decl(static_cast<Decl_stmt*>(s));
	}
}