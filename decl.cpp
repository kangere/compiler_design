#include "decl.hpp"

static void
print_var(Var_decl* d)
{

}

static void
print_ref(Ref_decl* d)
{

}

static void
print_func(Func_decl* d)
{

}

void
print(Decl* d)
{
	switch(d->get_kind())
	{
		case Decl::var_decl:
			return print_var(static_cast<Var_decl*>(d));
		case Decl::ref_decl:
			return print_ref(static_cast<Ref_decl*>(d));
		case Decl::func_decl:
			return print_func(static_cast<Func_decl*>(d));
	}

};