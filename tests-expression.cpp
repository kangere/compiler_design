#include <iostream>
#include "expr.hpp"
#include "type.hpp"
#include "catch.hpp"


TEST_CASE("Unary Expression Tests","[Unary]"){

	Negation_expr* exp1 = new Negation_expr(new Int_expr(new Int_type(),4), new Int_type());
	Logneg_expr* exp2 = new Logneg_expr(new Float_expr(new Float_type(),4.1), new Float_type());

	REQUIRE( exp1->get_kind() == unop_kind);
	REQUIRE( exp2->get_kind() == unop_kind);
	REQUIRE( (exp1->get_type())->get_kind() == Type::int_type);
	REQUIRE( (exp2->get_type())->get_kind() == Type::float_type);


	print(exp1);
	print(exp2);

}