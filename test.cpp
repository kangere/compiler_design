#include <iostream>
#include "expr.hpp"


int main() {


	Negation_expr* exp = new Negation_expr(new Int_expr(new Int_type(),4), new Int_type());

	print(exp);

	return 0;
}