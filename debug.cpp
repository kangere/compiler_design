#include "debug.hpp"
#include "type.hpp"

static void
debug_literal(Expr* e)
{
	

	
	/*
	if(e->get_kind() == bool_kind)
	{
		Bool_expr *b = static_cast<Bool_expr*>(e);
		db.get_printer() << b <<(b->get_value() ? " true" : " false");
	}
	else if(e->get_kind() == int_kind)
	{
		Int_expr* in = static_cast<Int_expr*>(e);
		db.get_printer() << in << 
	}
	else if(e->get_kind() == float_kind)
	{

	}*/
}

static void
debug_unop(std::ostream& os, Unop_expr* e)
{

	
}

void 
Debugger::debug(const Expr* e)
{
	print(m_os,e->get_type());
	
	
}