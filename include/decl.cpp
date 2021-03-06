#include "decl.hpp"
#include "stmt.hpp"
#include <iostream>

static void
print_var(Var_decl* d)
{
	std::cout << "var " << d->get_name() << ":" << *(d->get_type()) << "= ";
	print(d->get_expr());
	std::cout << std::endl;
}

static void
print_ref(Ref_decl* d)
{
	std::cout << "ref " << d->get_name() << ":" << *(d->get_type()) << "= ";
	print(d->get_expr());
	std::cout << std::endl;

}

static void
print_func(Func_decl* d)
{
	std::cout << "func " << d->get_name() << " (";

	for(auto param : d->get_params()){
		print(param);
		std::cout << " ";
	}

	std::cout << "){\n\t";
	print(d->get_stmt());

	std::cout << "}\n";

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