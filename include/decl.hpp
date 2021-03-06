#pragma once

#include "expr.hpp"
#include "type.hpp"
#include "stmt.hpp"
#include <string>
#include <iosfwd>
#include <vector>

class Expr;
class Stmt;


class Decl 
{
public:
	enum kind
	{
		var_decl,
		ref_decl,
		func_decl
	};

private:
	std::string m_name;
	Type* m_type;
	kind m_kind;

protected:
	Decl(std::string name, Type* t, kind k):
	m_name(name), m_type(t), m_kind(k)
	{}

public:
	Type* get_type() const { return m_type;}
	std::string get_name() const { return m_name;}
	kind get_kind() const {return m_kind;}

	
};



class Var_decl : public Decl 
{
private:
	Expr* m_exp;

public:
	Var_decl(std::string name, Type* t)
	: Decl(name,t,var_decl)
	{}

	Var_decl(std::string name, Type* t, Expr* e)
	: Decl(name,t,var_decl), m_exp(e) 
	{}

	void set_initializer(Expr* e) { m_exp = e; }

	Expr* get_expr() const {return m_exp;}

	
};

class Ref_decl : public Decl
{
private:
	Expr* m_exp;

public:
	Ref_decl(std::string name, Type* t, Expr* e)
	: Decl(name,t,ref_decl) , m_exp(e)
	{}

	Expr* get_expr() const { return m_exp;}



};

class Func_decl : public Decl
{
private:
	Stmt *m_stmt;
	std::vector<Decl*> param_list;

public:
	Func_decl(std::string name, Type* t)
	:Func_decl(name,t,nullptr)
	{}

	Func_decl(std::string name, Type* t,Stmt* s)
	:Decl(name,t,func_decl) , m_stmt(s)
	{}

	void set_param_list(std::vector<Decl*> list) { param_list = list;}
	void set_block_stmt(Stmt* block){ m_stmt = block; }
	
	void add_param(Decl* d) 
	{param_list.push_back(d);}

	//returns number of parameters
	int num_params()
	{return param_list.size();}

	std::vector<Decl*>   get_params() const
	{return param_list;}

	Stmt* get_stmt () const { return m_stmt;}
};


void debug(std::ostream& os, Decl* s,int indent = 0);
void s_expr(std::ostream &os, Decl* d);
void print(Decl*);