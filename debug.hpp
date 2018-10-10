#pragma once

#include <iosfwd>
#include "decl.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "stmt.hpp"

class Decl;
class Expr;
class Stmt;
class Type;


class Debugger
{
private:
	std::ostream& m_os;

public:
	Debugger(std::ostream& os)
	: m_os(os)
	{}

	void debug(Type*);
	void debug(const Expr*);
	void debug(Decl*);
	void debug(Stmt*);

	std::ostream& get_outstream() const
	{return m_os;}
};

