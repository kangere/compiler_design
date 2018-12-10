#include "catch.hpp"
#include "factory.hpp"
#include <iostream>

TEST_CASE("Expression factory tests","[Expressions]"){

	Ast_Factory e;

	Bool_expr* b = e.bool_e(true);
	Int_expr* in = e.int_e(7);
	Float_expr* fl = e.float_e(6.7);

	Var_decl* decl = new Var_decl("y",e.int_t(),in);

	Id_expr* id = e.id_e(decl, e.int_t());

	Negation_expr* neg = e.neg_e(new Int_expr(4), e.int_t());
	Logneg_expr* lneg = e.lneg_e(new Float_expr(4.1), e.float_t());
	Reciprocal_expr* rec = e.rec_e(new Int_expr(8),e.int_t());

	Eq_expr* eq = e.eq_e(new Int_expr(5),new Int_expr(5));
	Lt_expr* lt = e.lt_e(new Int_expr(5),new Int_expr(6));
	Gt_expr* gt = e.gt_e(new Int_expr(5),new Int_expr(4));

	Add_expr* add = e.add_e(e.int_e(3),e.int_e(2),e.int_t());
	Sub_expr* sub = e.sub_e(e.int_e(4),e.int_e(5),e.int_t());
	Mult_expr* mult = e.mult_e(e.int_e(7),e.int_e(6),e.int_t());
	Div_expr* div = e.div_e(e.int_e(24),e.int_e(4),e.int_t());

	CHECK( b->get_value());
	CHECK( in->get_value() == 7);
	CHECK( fl->get_value() == 6.7f);

	CHECK( (id->get_type())->get_kind() == Type::int_type);
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

	CHECK( add->get_operator() == Binop_expr::add_binop);
	CHECK( sub->get_operator() == Binop_expr::sub_binop);
	CHECK( mult->get_operator() == Binop_expr::mult_binop);
	CHECK( div->get_operator() == Binop_expr::div_binop);
}

TEST_CASE("Declaration factory tests","[Declarations]"){

	Ast_Factory f;

	std::cout << "\nSize of factory object is " << sizeof(f) << std::endl;

	Var_decl* var = f.var_d("x", new Int_type(), new Int_expr(9));
	Ref_decl* ref = f.ref_d("y", new Ref_type(new Float_type()), new Float_expr(8.8));
	Func_decl* func = f.func_d("foo",f.func_t(),f.break_s());

	CHECK(var->get_kind() == Decl::var_decl);
	CHECK(ref->get_kind() == Decl::ref_decl);
	CHECK(func->get_kind() == Decl::func_decl);
}

TEST_CASE("Statements factory tests","[Statements]"){

	Ast_Factory f;

	Break_stmt* br = f.break_s();
	Continue_stmt* c = f.continue_s();
	Expr_stmt* e = f.expr_s(f.bool_e(false));
	Decl_stmt* d = f.decl_s(f.var_d("x", f.int_t(), f.int_e(9)));

	Return_stmt* ret = f.return_s(f.sub_e(f.int_e(4),f.int_e(5),f.int_t()));

	While_stmt* wh = f.while_s(f.bool_e(true),f.expr_s(
						f.add_e(f.int_e(3),f.int_e(2),f.int_t())));

	If_stmt* if_s = f.if_s(f.eq_e(f.int_e(5),f.int_e(5))
							,f.return_s(f.float_e(4.5))
							, f.return_s(f.float_e(5.6)));

	Compound_stmt* cmp = f.compound_s();

	CHECK(br->get_kind() == Stmt::break_stmt);
	CHECK(c->get_kind() == Stmt::continue_stmt);
	CHECK(e->get_kind() == Stmt::expr_stmt);
	CHECK(d->get_kind() == Stmt::decl_stmt);

	CHECK( wh->get_kind() == Stmt::while_stmt);
	CHECK( if_s->get_kind() == Stmt::if_stmt);
	CHECK( ret->get_kind() == Stmt::return_stmt);
	CHECK(cmp->get_kind() == Stmt::compound_stmt);

}