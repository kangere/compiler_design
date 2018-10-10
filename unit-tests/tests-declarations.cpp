#include "../decl.hpp"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Declarations tests","[Declaration]"){

	Var_decl* var = new Var_decl("x", new Int_type(), new Int_expr(9));
	Ref_decl* ref = new Ref_decl("y", new Ref_type(new Float_type()), new Float_expr(8.8));

	
	REQUIRE((var->get_type())->get_kind() == Type::int_type);
	REQUIRE(var->get_name() == "x");
	REQUIRE((var->get_expr())->get_kind() == int_kind);

	REQUIRE((ref->get_type())->get_kind() == Type::ref_type);
	REQUIRE(ref->get_name() == "y");
	REQUIRE((ref->get_expr())->get_kind() == float_kind);

	std::cout << "Declarations Pretty Print" <<std::endl;
	print(var);
	print(ref);
	
}