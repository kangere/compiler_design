#pragma once

#include "type.hpp"
#include <vector>

enum kind
{
	bool_kind,
	int_kind,
	float_kind,
	id_kind,
	unop_kind,
	binop_kind,
	cond_kind,
};


class Expr
{
private:
	kind m_kind;
	Type *m_type;

public:
	kind get_kind() const { return m_kind; }
	Type* get_type() const {return m_type; }

protected:
	Expr(kind k) : m_kind(k) 
	{}
	Expr(kind k, Type* t): 
	m_kind(k), m_type(t)
	{}


};

class Bool_expr: public Expr 
{
public:
	Bool_expr(Type* t, bool b): Expr(bool_kind, t), val(b) 
	{}

	bool get_value() const {return val;}
private:

	bool val;

};


class Int_expr: public Expr
{
private:
	int val;

public:
	Int_expr(Type* t,int v): Expr(int_kind,t), val(v)
	{}

	int get_value() const {return val;}
};


class Float_expr : public Expr
{
private:
	float val;

public:
	Float_expr(Float_type* t, float f): Expr(float_kind,t) , val(f)
	{}

	float get_value() const {return val;}
};


//base classes for expression that contain expressions as class members
template<class T, int n>
class tuple
{
private:
	std::vector<T*> list;

public:
	tuple()
	{list.reserve(n);}

	void set_m(int index, T* value)
	{list[index] = value;}

	T* get_m(int index)
	{return list[index];}
};



enum unop
{
	logneg_uop,
	neg_uop
};

class Unop_expr : public Expr, public tuple<Expr,1>
{
public:	
	unop get_operator() const { return m_type;}

protected:
	Unop_expr(unop u, Type* t, Expr* e): 
	Expr(unop_kind,t), m_type(u)
	{ set_m(0,e);}

private:
	unop m_type;
};

class Binop_expr : public Expr, public tuple<Expr,2> 
{
public:
	enum binop
	{
		and_binop,
		or_binop,
		eq_binop,
		neq_binop,
		lt_binop,
		gt_binop,
		lt_eq_binop,
		gt_eq_binop,
		add_binop,
		sub_binop,
		mult_binop,
		div_binop,
		rem_binop
	};

	binop get_type() const { return m_type;}

protected:
	Binop_expr(binop b, Type* t, Expr* e1, Expr* e2): 
	Expr(binop_kind,t), m_type(b)
	{ set_m(0,e1); set_m(1,e2);}

private:
	binop m_type;
};

class Cond_expr : public Expr, public tuple<Expr*,3>
{
public:
	Cond_expr(Type* t):Expr(cond_kind,t)
	{}
};

//Unary Operations Expressions
class Logneg_expr : public Unop_expr 
{
public:
	Logneg_expr(Expr* e,Type* t)
		:Unop_expr(logneg_uop,t,e) {}
};

class Negation_expr : public Unop_expr
{
public:
	Negation_expr(Expr* e,Type* t)
		:Unop_expr(neg_uop,t,e) {}
};

//Binary Operattions Expression
class And_expr : public Binop_expr
{
public:
	And_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(and_binop,t,e1,e2) {}
	
};

class Or_expr : public Binop_expr
{
public:
	Or_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(or_binop,t,e1,e2) {}
	
};

class Eq_expr : public Binop_expr
{
public:
	Eq_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(eq_binop,t,e1,e2) {}
	
};


class Neq_expr : public Binop_expr
{
public:
	Neq_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(neq_binop,t,e1,e2) {}
	
};

class Lt_expr : public Binop_expr
{
public:
	Lt_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(lt_binop,t,e1,e2) {}
	
};
class Gt_expr : public Binop_expr
{
public:
	Gt_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(gt_binop,t,e1,e2) {}
	
};

class Lteq_expr : public Binop_expr
{
public:
	Lteq_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(lt_eq_binop,t,e1,e2) {}
	
};

class Gteq_expr : public Binop_expr
{
public:
	Gteq_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(gt_eq_binop,t,e1,e2) {}
	
};

class Add_expr : public Binop_expr
{
public:
	Add_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(add_binop,t,e1,e2) {}
	
};
class Sub_expr : public Binop_expr
{
public:
	Sub_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(sub_binop,t,e1,e2) {}
	
};
class Mult_expr : public Binop_expr
{
public:
	Mult_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(mult_binop,t,e1,e2) {}
	
};
class Div_expr : public Binop_expr
{
public:
	Div_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(div_binop,t,e1,e2) {}
	
};
class Rem_expr : public Binop_expr
{
public:
	Rem_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(rem_binop,t,e1,e2) {}
	
};


void print(Expr* e);