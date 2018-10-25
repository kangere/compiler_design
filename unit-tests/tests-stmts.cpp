#include "../stmt.hpp"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Statement tests","[Statement]"){

	Break_stmt* br = new Break_stmt();
	Continue_stmt* c = new Continue_stmt();
	Expr_stmt* e = new Expr_stmt(new Bool_expr(false));
	Decl_stmt* d = new Decl_stmt(new Var_decl("x", new Int_type(), new Int_expr(9)));

	REQUIRE(br->get_kind() == Stmt::break_stmt);
	REQUIRE(c->get_kind() == Stmt::continue_stmt);
	REQUIRE(e->get_kind() == Stmt::expr_stmt);
	REQUIRE(d->get_kind() == Stmt::decl_stmt);

	REQUIRE((e->get_expr())->get_kind() == Expr::bool_expr);
	REQUIRE((d->get_decl())->get_kind() == Decl::var_decl);

	std::cout << "\nStatements pretty print" << std::endl;
	print(br);
	print(c);
	print(e);
	print(d);
	s_expr(std::cout, br);
	s_expr(std::cout, d);

}

TEST_CASE("Complex Statements","[Statements"){

	Return_stmt* ret = new Return_stmt(new Sub_expr(new Int_expr(4),new Int_expr(5),new Int_type()));

	While_stmt* wh = new While_stmt(new Bool_expr(true),new Expr_stmt(new Add_expr(new Int_expr(3),new Int_expr(2),new Int_type())));
	If_stmt* if_s = new If_stmt(new Eq_expr(new Int_expr(5),new Int_expr(5))
							,new Return_stmt(new Float_expr(4.5))
							, new Return_stmt(new Float_expr(5.6)));

	Compound_stmt* cmp = new Compound_stmt();
	cmp->add_stmt(wh);
	cmp->add_stmt(if_s);


	REQUIRE( wh->get_kind() == Stmt::while_stmt);
	REQUIRE( (wh->get_stmt())->get_kind() == Stmt::expr_stmt);
	REQUIRE( (wh->get_expr())->get_kind() == Expr::bool_expr);

	REQUIRE( if_s->get_kind() == Stmt::if_stmt);
	REQUIRE( (if_s->get_expr())->get_kind() == Expr::binop_expr);
	REQUIRE( (if_s->get_stmt_1())->get_kind() == Stmt::return_stmt);
	REQUIRE( (if_s->get_stmt_2())->get_kind() == Stmt::return_stmt);

	REQUIRE( ret->get_kind() == Stmt::return_stmt);
	REQUIRE((ret->get_expr())->get_kind() == Expr::binop_expr);
	
	REQUIRE(cmp->get_kind() == Stmt::compound_stmt);
	REQUIRE(cmp->num_stmts() == 2);

	print(wh);
	print(if_s);
	print(cmp);
	s_expr(std::cout,cmp);
}