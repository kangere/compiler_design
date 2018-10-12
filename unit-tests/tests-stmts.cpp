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

TEST_CASE("Complex Statements","[Statements"){

	While_stmt* wh = new While_stmt(new Bool_expr(true),new Continue_stmt());
	If_stmt* if_s = new If_stmt(new Eq_expr(new Int_expr(5),new Int_expr(5))
							,new Return_stmt(new Float_expr(4.5))
							, new Return_stmt(new Float_expr(5.6)));

	REQUIRE( wh->get_kind() == Stmt::while_stmt);
	REQUIRE( (wh->get_stmt())->get_kind() == Stmt::continue_stmt);
	REQUIRE( (wh->get_expr())->get_kind() == Expr::bool_expr);

	REQUIRE( if_s->get_kind() == Stmt::if_stmt);


	print(wh);
	print(if_s);
}