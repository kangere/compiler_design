#include "../decl.hpp"
#include "catch.hpp"
#include <iostream>


TEST_CASE("Declarations tests","[Declaration]"){

	Var_decl* var = new Var_decl("x", new Int_type(), new Int_expr(9));
	Ref_decl* ref = new Ref_decl("y", new Ref_type(new Float_type()), new Float_expr(8.8));

	
	REQUIRE((var->get_type())->get_kind() == Type::int_type);
	REQUIRE(var->get_name() == "x");
	REQUIRE((var->get_expr())->get_kind() == Expr::int_expr);

	

	REQUIRE((ref->get_type())->get_kind() == Type::ref_type);
	REQUIRE(ref->get_name() == "y");
	REQUIRE((ref->get_expr())->get_kind() == Expr::float_expr);

	Ref_type *ref_type = static_cast<Ref_type*>(ref->get_type());
	REQUIRE( (ref_type->get_ref_type())->get_kind() == Type::float_type);


	std::cout << "\nDeclarations Pretty Print" <<std::endl;
	print(var);
	print(ref);
	
}

TEST_CASE("Function Declaraion tests","[Function Declaraion]"){

	/*
		func foo (x:int, y:int){
			return x+y;
		}
	*/

	Return_stmt* ret = new Return_stmt(new Add_expr(new Int_expr(3),new Int_expr(4),new Int_type()));

	Func_type* func_type = new Func_type();
	func_type->add_param(new Int_type());
	func_type->add_param(new Int_type());

	func_type->set_return_type(new Int_type());

	Func_decl* func = new Func_decl("foo",func_type,ret);

	func->add_param(new Var_decl("x",new Int_type(),new Int_expr(3)));
	func->add_param(new Var_decl("y",new Int_type(),new Int_expr(4)));

	REQUIRE((func->get_type())->get_kind() == Type::func_type);
	REQUIRE(func->get_name() == "foo");
	REQUIRE((func->get_stmt())->get_kind() == Stmt::return_stmt);
	REQUIRE(func->num_params() == func_type->num_params());

	std::cout << "\nFunction Declaration Pretty Print" << std::endl;
	print(func);
}