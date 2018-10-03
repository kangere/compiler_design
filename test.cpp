#include <iostream>
#include "expr.hpp"


int main() {

	Int_expr* exp = new Int_expr(new Int_type(),4);

	Float_expr* e = new Float_expr(new Float_type(),1.4);

	print(&exp);

	return 0;
}