#include "catch.hpp"
#include "parser.hpp"
#include <fstream>
#include <string>
#include <iostream>

TEST_CASE("Expression Tests","[Expression]"){

	std::fstream file("expressions.mc",std::ios::in);

	if(file.is_open()){

		std::istreambuf_iterator<char> first(file);
		std::istreambuf_iterator<char> limit;
		std::string input(first, limit);

		symbol_table syms;

		parser parse(syms,input);

		Expr* true_kw = parse.parse_expression();
		Expr* false_kw = parse.parse_expression();
		Expr* int_lit = parse.parse_expression();
		Expr* float_lit = parse.parse_expression();
		Expr* cond = parse.parse_expression();
		Expr* lneg = parse.parse_expression();
		Expr* not_e = parse.parse_expression();
		Expr* gt = parse.parse_expression();
		Expr* lt = parse.parse_expression();
		Expr* gt_eq = parse.parse_expression();
		Expr* lt_eq = parse.parse_expression();
		Expr* add = parse.parse_expression();
		Expr* minus = parse.parse_expression();
		Expr* mult = parse.parse_expression();
		Expr* div = parse.parse_expression();
		Expr* percent = parse.parse_expression();
		Expr* or_exp = parse.parse_expression();
		Expr* and_exp = parse.parse_expression();
		Expr* eq_exp = parse.parse_expression();

		CHECK(true_kw->get_kind() == Expr::bool_expr);
		CHECK(false_kw->get_kind() == Expr::bool_expr);
		CHECK(int_lit->get_kind() == Expr::int_expr);
		CHECK(float_lit->get_kind() == Expr::float_expr);
		CHECK(cond->get_kind() == Expr::cond_expr);
		CHECK(lneg->get_kind() == Expr::unop_expr);
		CHECK(not_e->get_kind() == Expr::binop_expr);
		CHECK(gt->get_kind() == Expr::binop_expr);
		CHECK(lt->get_kind() == Expr::binop_expr);
		CHECK(gt_eq->get_kind() == Expr::binop_expr);
		CHECK(lt_eq->get_kind() == Expr::binop_expr);
		CHECK(add->get_kind() == Expr::binop_expr);
		CHECK(minus->get_kind() == Expr::binop_expr);
		CHECK(mult->get_kind() == Expr::binop_expr);
		CHECK(div->get_kind() == Expr::binop_expr);
		CHECK(percent->get_kind() == Expr::binop_expr);
		CHECK(or_exp->get_kind() == Expr::binop_expr);
		CHECK(and_exp->get_kind() == Expr::binop_expr);
		CHECK(eq_exp->get_kind() == Expr::binop_expr);


	} else {
		std::cout << "Could Not ope file" << std::endl;
	}

	file.close();

}


TEST_CASE("Declaration Tests","[Declarations]"){

	std::fstream file("declarations.mc",std::ios::in);

	if(file.is_open()){

		std::istreambuf_iterator<char> first(file);
		std::istreambuf_iterator<char> limit;
		std::string input(first, limit);

		symbol_table syms;

		parser parse(syms,input);

		std::vector<Decl*> decls = parse.parse_program();


	} else {
		std::cout << "Could not open file" << std::endl;
	}

	file.close();
}