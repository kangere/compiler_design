#include "builder.hpp"
#include <iostream>

//util functions
Expr*
Builder::convert_value(Expr* e)
{
	Type* t = e->get_type();

	if(t->get_kind() == Type::ref_type)
	{
		Ref_type* ref = static_cast<Ref_type*>(t);
		return new Value_expr(e,ref->get_ref_type());
	}

	return e;
}

void 
Builder::require_bool(Expr* e)
{
	e = convert_value(e);

	Type* t = e->get_type();

	if(t->get_kind() != Type::bool_type)
		std::cerr << "type bool required"<< std::endl;
}

void 
Builder::require_same(Expr* e1, Expr* e2)
{
	e1 = convert_value(e1);
	e2 = convert_value(e2);

	if(!((e1->get_type())->same_as(e2->get_type())))
		std::cerr << "Type: " << *(e1->get_type()) << " is not same as " << *(e2->get_type()) << std::endl;
}

Expr*
Builder::require_arithmetic(Expr* e)
{
	if(!(e->get_type())->is_arithmetic())
		std::cerr << "Arithmetic type expected, actual: " << *(e->get_type()) << std::endl;

	return e;
}
void
Builder::is_same_arithmetic(Expr* e1, Expr* e2)
{
	//convert values
	e1 = convert_value(e1);
	e2 = convert_value(e2);

	//ensure both are arithmetic
	e1 = require_arithmetic(e1);
	e2 = require_arithmetic(e2);

	//TODO convert values
	//i.e promote int to floats


	//ensure same type
	require_same(e1,e2);
}