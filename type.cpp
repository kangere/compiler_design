#include "type.hpp"
#include <iostream>
#include <string>

static void
print_str(std::ostream& os, char const* str)
{
	os << str;
}

static void 
print_ref(std::ostream& os, Ref_type const* ref)
{
	os << "ref:" << *(ref->get_ref_type());
}

void print(std::ostream &os, Type const* t)
{
	switch(t->get_kind()){

		case Type::bool_type:
			return print_str(os,"bool ");

		case Type::int_type:
			return print_str(os,"int ");


		case Type::float_type:
			return print_str(os,"float ");

		case Type::ref_type:
			return print_ref(os,static_cast<Ref_type const*>(t));
	}
}

std::ostream& operator<<(std::ostream& os, Type const& t)
{	
	print(os, &t);
	return os;
}


bool
Type::is_same_as(Type* that)
{
	return m_kind == that->get_kind();
}