#include "decl.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "type.hpp"

#include <iostream>


int 
main()
{
	
	//debugging tools demos

	//literals
	Float_expr* f = new Float_expr(8.9);
	Int_expr* i = new Int_expr(5);
	Bool_expr* b = new Bool_expr(true);

	//unary operations
	Negation_expr* neg = new Negation_expr(i,new Int_type());
	Logneg_expr* log_neg = new Logneg_expr(f,new Float_type());

	//binary operations expressions
	And_expr* an = new And_expr(new Bool_expr(true),new Bool_expr(true));
	Add_expr* add = new Add_expr(new Int_expr(4),new Int_expr(7),new Int_type());

	debug(std::cerr,f);
	debug(std::cerr,i);
	debug(std::cerr,b);
	debug(std::cerr,neg);
	debug(std::cerr,log_neg);
	debug(std::cerr,an);
	debug(std::cerr,add);

	
	return 0;
}