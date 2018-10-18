#include <iostream>
#include "../expr.hpp"
#include "catch.hpp"


TEST_CASE("Literal Expression Tests","[Literal]"){
	Bool_expr* exp1 = new Bool_expr(false);
	Int_expr* exp2 = new Int_expr(5);
	Float_expr* exp3 = new Float_expr(6.7);

	Var_decl* decl = new Var_decl("y",new Int_type(),exp2);

	Id_expr* id = new Id_expr(decl, new Ref_type(new Int_type()));

	REQUIRE( exp1->get_value() == false);
	REQUIRE( exp2->get_value() == 5);
	REQUIRE( exp3->get_value() == 6.7f);

	REQUIRE( (id->get_type())->get_kind() == Type::ref_type);
	REQUIRE( (id->get_decl())->get_name() == "y");
	

	std::cout << "\nLiteral Expression Print output" << std::endl;
	print(exp1);
	std::cout << std::endl;
	print(exp2);
	std::cout << std::endl;
	print(exp3);
	std::cout << std::endl;
}

TEST_CASE("Unary Operations Expression Tests","[Unary]"){

	Negation_expr* exp1 = new Negation_expr(new Int_expr(4), new Int_type());
	Logneg_expr* exp2 = new Logneg_expr(new Float_expr(4.1), new Float_type());
	Reciprocal_expr* rec = new Reciprocal_expr(new Int_expr(8),new Int_type());



	REQUIRE( exp1->get_kind() == Expr::unop_expr);
	REQUIRE( exp2->get_kind() == Expr::unop_expr);
	REQUIRE( rec->get_kind() == Expr::unop_expr);

	REQUIRE( exp1->get_operator() == Unop_expr::neg_unop);
	REQUIRE( exp2->get_operator() == Unop_expr::logneg_unop);
	REQUIRE( rec->get_operator() == Unop_expr::rec_unop);

	REQUIRE( (exp1->get_type())->get_kind() == Type::int_type);
	REQUIRE( (exp2->get_type())->get_kind() == Type::float_type);
	REQUIRE( (rec->get_type())->get_kind() == Type::int_type);

	std::cout << "\nUnary Operation Expression Print output" << std::endl;
	print(exp1);
	print(exp2);
	print(rec);
	s_expr(std::cout,exp1);

}

TEST_CASE("Binary Operation Expression Tests","[Binary]"){

	//bool type expressions
	Eq_expr* eq = new Eq_expr(new Int_expr(5),new Int_expr(5));
	Lt_expr* lt = new Lt_expr(new Int_expr(5),new Int_expr(6));
	Gt_expr* gt = new Gt_expr(new Int_expr(5),new Int_expr(4));
	Gteq_expr* gteq = new Gteq_expr(new Int_expr(7),new Int_expr(4));
	Lteq_expr* lteq = new Lteq_expr(new Int_expr(8),new Int_expr(9));

	Add_expr* add = new Add_expr(new Int_expr(3),new Int_expr(2),new Int_type());
	Sub_expr* sub = new Sub_expr(new Int_expr(4),new Int_expr(5),new Int_type());
	Mult_expr* mult = new Mult_expr(new Int_expr(7),new Int_expr(6),new Int_type());
	Div_expr* div = new Div_expr(new Int_expr(24),new Int_expr(4),new Int_type());


	Var_decl* decl = new Var_decl("y",new Int_type(),new Int_expr(9));
	Id_expr* id = new Id_expr(decl, new Ref_type(new Int_type()));
	Assignment_expr* assign  = new Assignment_expr(id,new Int_expr(5),new Int_type());

	REQUIRE( (eq->get_type())->get_kind() == Type::bool_type);
	REQUIRE( (lt->get_type())->get_kind() == Type::bool_type);
	REQUIRE( (gt->get_type())->get_kind() == Type::bool_type);
	REQUIRE( (gteq->get_type())->get_kind() == Type::bool_type);
	REQUIRE( (lteq->get_type())->get_kind() == Type::bool_type);

	REQUIRE( (add->get_type())->get_kind() == Type::int_type);
	REQUIRE( add->get_operator() == Binop_expr::add_binop);
	REQUIRE( (add->get_m(0))->get_kind() == Expr::int_expr);
	REQUIRE( (add->get_m(1))->get_kind() == Expr::int_expr);	

	REQUIRE( (eq->get_m(0))->get_kind() == Expr::int_expr);
	REQUIRE( (eq->get_m(1))->get_kind() == Expr::int_expr);

	REQUIRE( assign->get_kind() == Expr::binop_expr);
	REQUIRE(assign->get_operator() == Binop_expr::assign_binop);
	REQUIRE((assign->get_type())->get_kind() == Type::int_type);
	REQUIRE((assign->get_m(0))->get_kind() == Expr::id_expr);
	REQUIRE((assign->get_m(1))->get_kind() == Expr::int_expr);

	std::cout << "\nBinary Operation Expression Print output" << std::endl;
	print(eq);
	print(lt);
	print(gt);
	print(gteq);
	print(lteq);
	print(add);
	print(sub);
	print(mult);
	print(div);
	print(assign);

	s_expr(std::cout,eq);
}

TEST_CASE("Conditional Expression","[Conditional]"){


}