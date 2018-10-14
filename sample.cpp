#include "decl.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "type.hpp"

#include <iostream>
#include <iomanip>

void debug_example();
void sample_program();

void skipl()
{ std::cout << std::endl;}

int 
main()
{
	
	//sample program
	sample_program();

	//debugging
	debug_example();

	return 0;
}

void
sample_program()
{
	/*
		func main() 
		{
			var x:int = 3;
			var y:int = 4;

			

			return x+y;
		}

	*/

	Func_type* func_type = new Func_type();

	Expr_stmt* s1 = new Expr_stmt(new Id_expr(new Var_decl("x", new Int_type(), new Int_expr(3))
					,new Ref_type(new Int_type())));
	Expr_stmt* s2 = new Expr_stmt(new Id_expr(new Var_decl("y", new Int_type(), new Int_expr(4))
					,new Ref_type(new Int_type())));

	Return_stmt* s3 = new Return_stmt(new Add_expr(s1->get_expr(),s2->get_expr(),new Int_type()));

	Compound_stmt* s_cmp = new Compound_stmt();
	s_cmp->add_stmt(s1);
	s_cmp->add_stmt(s2);
	s_cmp->add_stmt(s3);

	Func_decl* func = new Func_decl("main",func_type,s_cmp);

	print(func);


}

void 
debug_example()
{
	//debugging tools demos

	//literals
	Float_expr* f = new Float_expr(8.9);
	Int_expr* i = new Int_expr(5);
	Bool_expr* b = new Bool_expr(true);



	//unary operations expressions
	Negation_expr* neg = new Negation_expr(i,new Int_type());
	Logneg_expr* log_neg = new Logneg_expr(f,new Float_type());

	//binary operations expressions
	And_expr* an = new And_expr(new Bool_expr(true),new Bool_expr(true));
	Add_expr* add = new Add_expr(new Int_expr(4),new Int_expr(7),new Int_type());

	//Declarations
	Var_decl* var = new Var_decl("x", new Int_type(), new Int_expr(9));
	Id_expr* id = new Id_expr(var,new Ref_type(new Int_type()));
	Ref_decl* ref = new Ref_decl("y", new Ref_type(new Int_type()), id);

	//function declaration
	Return_stmt* ret = new Return_stmt(new Add_expr(new Int_expr(3),new Int_expr(4),new Int_type()));

	Func_type* func_type = new Func_type();
	func_type->add_param(new Int_type());
	func_type->add_param(new Int_type());

	func_type->set_return_type(new Int_type());

	Func_decl* func = new Func_decl("foo",func_type,ret);

	func->add_param(new Var_decl("x",new Int_type(),new Int_expr(3)));
	func->add_param(new Var_decl("y",new Int_type(),new Int_expr(4)));

	//Statements
	Break_stmt* br = new Break_stmt();
	Continue_stmt* ct = new Continue_stmt();
	Expr_stmt* expr_stmt = new Expr_stmt(new Bool_expr(false));
	Decl_stmt* decl_stmt = new Decl_stmt(new Var_decl("x", new Int_type(), new Int_expr(9)));
	While_stmt* wh_s = new While_stmt(new Bool_expr(true),new Expr_stmt(new Add_expr(new Int_expr(3),new Int_expr(2),new Int_type())));
	If_stmt* if_s = new If_stmt(new Eq_expr(new Int_expr(5),new Int_expr(5))
							,new Return_stmt(new Float_expr(4.5))
							, new Return_stmt(new Float_expr(5.6)));

	Compound_stmt* cmp = new Compound_stmt();
	cmp->add_stmt(wh_s);
	cmp->add_stmt(if_s);


	debug(std::cerr,f);
	debug(std::cerr,i);
	debug(std::cerr,b);
	skipl();
	debug(std::cerr,id);
	debug(std::cerr,neg);
	debug(std::cerr,log_neg);
	skipl();
	debug(std::cerr,an);
	debug(std::cerr,add);
	skipl();
	debug(std::cerr,var);
	debug(std::cerr,ref);
	skipl();
	debug(std::cerr,func);
	skipl();
	debug(std::cerr, br);
	debug(std::cerr, ct);
	skipl();
	debug(std::cerr, expr_stmt);
	debug(std::cerr, decl_stmt);
	debug(std::cerr, wh_s);
	debug(std::cerr, if_s);
	skipl();
	debug(std::cerr, cmp);
}