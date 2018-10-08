#pragma once

#include "expr.hpp"
#include "type.hpp"
#include "stmt.hpp"
#include <string>

class Expr;
class Stmt;

class Decl 
{
private:
	std::string m_name;
	Type* m_type;

protected:
	Decl(std::string name, Type* t):
	m_name(name), m_type(t)
	{}

public:
	Type* get_type() const { return m_type;}
	std::string get_name() const { return m_name;}

};



class Var_decl : public Decl 
{
private:
	Expr* m_exp;

public:
	Var_decl(std::string name, Type* t, Expr* e)
	: Decl(name,t), m_exp(e) 
	{}

	Expr* get_expr() const {return m_exp;}

	
};

class Ref_decl : public Decl
{
private:
	Expr* m_exp;

public:
	Ref_decl(std::string name, Type* t, Expr* e)
	: Decl(name,t) , m_exp(e)
	{}

	Expr* get_expr() const { return m_exp;}

};

class Func_decl : public Decl
{
private:
	Stmt *m_stmt;
	

public:
	Func_decl(std::string name, Type* t,Stmt* s)
	:Decl(name,t) , m_stmt(s)
	{}

	Stmt* get_stmt () const { return m_stmt;}
};

void print(Decl*);