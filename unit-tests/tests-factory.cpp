#include "catch.hpp"
#include "../factory.hpp"


TEST_CASE("Expression factory tests","[Expressions]"){

	Ast_Factory* e = new Ast_Factory();

	Bool_expr* b = e->make_literal<Bool_expr,bool>(true);
	Int_expr* in = e->make_literal<Int_expr,int>(7);
	Float_expr* fl = e->make_literal<Float_expr,float>(6.7);

	Var_decl* decl = new Var_decl("y",e->int_t(),in);

	Id_expr* id = e->make_id(decl, e->int_t());

	Negation_expr* neg = e->make_unop<Negation_expr>(new Int_expr(4), e->int_t());
	Logneg_expr* lneg = e->make_unop<Logneg_expr>(new Float_expr(4.1), e->float_t());
	Reciprocal_expr* rec = e->make_unop<Reciprocal_expr>(new Int_expr(8),e->int_t());

	Eq_expr* eq = e->make_binop<Eq_expr>(new Int_expr(5),new Int_expr(5));
	Lt_expr* lt = e->make_binop<Lt_expr>(new Int_expr(5),new Int_expr(6));
	Gt_expr* gt = e->make_binop<Gt_expr>(new Int_expr(5),new Int_expr(4));

	CHECK( b->get_value());
	CHECK( in->get_value() == 7);
	CHECK( fl->get_value() == 6.7f);

	CHECK( (id->get_type())->get_kind() == Type::ref_type);
	CHECK( (id->get_decl())->get_name() == "y");

	CHECK( neg->get_kind() == Expr::unop_expr);
	CHECK( lneg->get_kind() == Expr::unop_expr);
	CHECK( rec->get_kind() == Expr::unop_expr);

	CHECK( neg->get_operator() == Unop_expr::neg_unop);
	CHECK( lneg->get_operator() == Unop_expr::logneg_unop);
	CHECK( rec->get_operator() == Unop_expr::rec_unop);

	CHECK( (neg->get_type())->get_kind() == Type::int_type);
	CHECK( (lneg->get_type())->get_kind() == Type::float_type);
	CHECK( (rec->get_type())->get_kind() == Type::int_type);

	CHECK( (eq->get_type())->get_kind() == Type::bool_type);
	CHECK( (lt->get_type())->get_kind() == Type::bool_type);
	CHECK( (gt->get_type())->get_kind() == Type::bool_type);
}