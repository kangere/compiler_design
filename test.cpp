#include <iostream>
#include "expr.hpp"


int main() {


	Negation_expr* exp = new Negation_expr(new Int_expr(new Int_type(),4));

	print(exp);

	return 0;
}