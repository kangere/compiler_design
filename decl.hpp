#pragma once

#include "expr.hpp"
#include "type.hpp"
#include <string>

class Decl 
{
private:
	std::string m_name;
	Type* m_type;

public:
	Decl(std::string name, Type* t):
	m_name(name), m_type(t)
	{}
};