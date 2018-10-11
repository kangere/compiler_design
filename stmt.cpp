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
	}
}