#pragma once 

#include "expr.hpp"
#include "decl.hpp"
#include <vector>
#include <iosfwd>

class Expr;
class Decl;

class Stmt
{
public:
	enum kind
	{
		break_stmt,
		continue_stmt,
		compound_stmt,
		while_stmt,
		if_stmt,
		return_stmt,
		expr_stmt,
		decl_stmt,
		skip_stmt
	};

	Stmt(kind k)
	:m_kind(k)
	{}

	kind get_kind() const{ return m_kind;}

protected:
	kind m_kind;

};

class Break_stmt : public Stmt
{
public:
	Break_stmt()
	:Stmt(break_stmt)
	{}

};

class Continue_stmt: public Stmt
{
public:
	Continue_stmt()
	:Stmt(continue_stmt)
	{}

};

class While_stmt : public Stmt
{
private:
	Expr* m_exp;
	Stmt* m_stmt;

public:
	While_stmt(Expr* e, Stmt* s)
	:Stmt(while_stmt), m_exp(e), m_stmt(s)
	{}

	Stmt* get_stmt() const{ return m_stmt;}
	Expr* get_expr() const{ return m_exp;}

};

class Compound_stmt : public Stmt
{
private:
	std::vector<Stmt*> stmt_list;

public:
	Compound_stmt()
	:Stmt(compound_stmt)
	{}

	Compound_stmt(std::initializer_list<Stmt*> l)
	:Compound_stmt(std::vector<Stmt*>(l))
	{}

	Compound_stmt(std::vector<Stmt*> v)
	:Stmt(compound_stmt), stmt_list(v)
	{}

	void add_stmt(Stmt* s)
	{stmt_list.push_back(s);}

	int num_stmts() const 
	{return stmt_list.size();}

	std::vector<Stmt*> get_stmts() const
	{return stmt_list;}

};

class If_stmt : public Stmt
{
private:
	Expr* m_exp;
	Stmt *m_stmt_1,*m_stmt_2;

public:
	If_stmt(Expr* e, Stmt* s1, Stmt* s2)
	:Stmt(if_stmt), m_exp(e), m_stmt_1(s1),
		m_stmt_2(s2)
	{}

	Expr* get_expr() const {return m_exp;}
	Stmt* get_stmt_1() const {return m_stmt_1;}
	Stmt* get_stmt_2() const { return m_stmt_2;} 
};

class Return_stmt : public Stmt
{
private:
	Expr* m_exp;

public:
	Return_stmt(Expr* e)
	:Stmt(return_stmt), m_exp(e)
	{}

	Expr* get_expr() const {return m_exp;}
};

class Expr_stmt : public Stmt
{
private:
	Expr* m_exp;

public:
	Expr_stmt(Expr* e)
	:Stmt(expr_stmt), m_exp(e)
	{}

	Expr* get_expr() const {return m_exp;}
};

class Decl_stmt : public Stmt
{
private:
	Decl* m_decl;

public:
	Decl_stmt(Decl* d)
	:Stmt(decl_stmt), m_decl(d)
	{}

	Decl* get_decl() const { return m_decl;}
};

class Skip_stmt : public Stmt
{
public:
	Skip_stmt()
	:Stmt(skip_stmt)
	{}
};




void debug(std::ostream& os, Stmt* s,int indent = 0);

void s_expr(std::ostream &os, Stmt* s);

void print(Stmt* s);