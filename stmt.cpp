#include "stmt.hpp"
#include <iostream>

static void 
print_expr(Expr_stmt* e)
{
	std::cout << "expr_stmt:";
	print(e->get_expr());
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
	}
}