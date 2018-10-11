#include "../stmt.hpp"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Statement tests","[Statement]"){

	Break_stmt* br = new Break_stmt();
	Continue_stmt* c = new Continue_stmt();
	Expr_stmt* e = new Expr_stmt(new Bool_expr(false));

	REQUIRE(br->get_kind() == Stmt::break_stmt);
	REQUIRE(c->get_kind() == Stmt::continue_stmt);
	REQUIRE(e->get_kind() == Stmt::expr_stmt);

	REQUIRE((e->get_expr())->get_kind() == Expr::bool_expr);

	std::cout << "\nStatements pretty print" << std::endl;
	print(br);
	print(c);
	print(e);

}