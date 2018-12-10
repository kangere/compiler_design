#pragma once

#include "type.hpp"
#include "decl.hpp"
#include <vector>
#include <iosfwd>
#include <cassert>

class Decl;

//base classes for classes that contain member objects of the same type
template<typename T, int n>
class tuple
{
private:
	std::vector<T*> list;

public:
	tuple()
	{list.reserve(n);}

	void set_m(int index, T* value)
	{
		assert(index < n);
		list[index] = value;
	}

	int num_mems() const {return n;}

	T* get_m(int index)
	{
		assert(index < n);
		return list[index];}
};



class Expr
{
public:
	enum kind
	{
		bool_expr,
		int_expr,
		float_expr,
		id_expr,
		unop_expr,
		binop_expr,
		cond_expr,
		func_expr
	};
	
private:
	kind m_kind;
	Type *m_type;

public:
	
	kind get_kind() const { return m_kind; }
	Type* get_type() const {return m_type; }
	void set_type(Type* t) { m_type = t;}

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
	Bool_expr(bool b): Expr(bool_expr, new Bool_type()), val(b) 
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
	Int_expr(int v)
	: Expr(int_expr,new Int_type()), val(v)
	{}

	int get_value() const {return val;}
};


class Float_expr : public Expr
{
private:
	float val;

public:
	Float_expr(float f)
	: Expr(float_expr,new Float_type()) , val(f)
	{}

	float get_value() const {return val;}
};

class Id_expr : public Expr
{
private:
	Decl* m_decl;

public:
	Id_expr(Decl* d, Type* t):
	Expr(id_expr,t), m_decl(d)
	{}

	Decl* get_decl() const { return m_decl;}
};

class Func_expr : public Expr
{
private:
	std::vector<Expr*> mems;
	

public:
	Func_expr(std::initializer_list<Expr*> l ,Type* t)
	: Expr(func_expr,t), mems(l)
	{}

	Func_expr(std::vector<Expr*> l ,Type* t)
	: Expr(func_expr,t), mems(l)
	{}

	Expr* get_function() const
	{ return mems.front();}

	std::vector<Expr*> get_args()
	{return std::vector<Expr*>(mems.begin() + 1, mems.end());}


}; 





//base unary operation expression class
class Unop_expr : public Expr, public tuple<Expr,1>
{
public:
	enum unop
	{
		logneg_unop,
		neg_unop,
		rec_unop,
		val_unop
	};	
	unop get_operator() const { return m_type;}

protected:
	Unop_expr(unop u, Type* t, Expr* e): 
	Expr(unop_expr,t), m_type(u)
	{ set_m(0,e);}

private:
	unop m_type;
};



//Base binary operation expression class
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
		rem_binop,
		assign_binop

	};

	binop get_operator() const { return m_op;}

protected:
	Binop_expr(binop b, Type* t, Expr* e1, Expr* e2): 
	Expr(binop_expr,t), m_op(b)
	{ set_m(0,e1); set_m(1,e2);}

private:
	binop m_op;
};

//Only ternary expression
class Cond_expr : public Expr, public tuple<Expr,3>
{
public:
	Cond_expr(Expr* e1, Expr* e2, Expr* e3,Type* t)
	:Expr(cond_expr,t)
	{ 	
		set_m(0,e1);
		set_m(1,e2);
		set_m(2,e3);
	}
};

//Unary Operations Expressions
class Logneg_expr : public Unop_expr 
{
public:
	Logneg_expr(Expr* e,Type* t)
		:Unop_expr(logneg_unop,t,e) {}
};

class Negation_expr : public Unop_expr
{
public:
	Negation_expr(Expr* e,Type* t)
		:Unop_expr(neg_unop,t,e) {}
};

class Reciprocal_expr : public Unop_expr
{
public:
	Reciprocal_expr(Expr* e,Type* t)
		:Unop_expr(rec_unop,t,e) {}
};

class Value_expr : public Unop_expr
{
public:
	Value_expr(Expr* e, Type* t)
		:Unop_expr(val_unop,t,e) {}
};



//Binary Operations Expression
class And_expr : public Binop_expr
{
public:
	And_expr(Expr* e1, Expr* e2)
		:Binop_expr(and_binop,new Bool_type(),e1,e2) {}
	
};

class Or_expr : public Binop_expr
{
public:
	Or_expr(Expr* e1, Expr* e2)
		:Binop_expr(or_binop,new Bool_type(),e1,e2) {}
	
};

class Eq_expr : public Binop_expr
{
public:
	Eq_expr(Expr* e1, Expr* e2)
		:Binop_expr(eq_binop,new Bool_type(),e1,e2) {}
	
};


class Neq_expr : public Binop_expr
{
public:
	Neq_expr(Expr* e1, Expr* e2)
		:Binop_expr(neq_binop,new Bool_type(),e1,e2) {}
	
};

class Lt_expr : public Binop_expr
{
public:
	Lt_expr(Expr* e1, Expr* e2)
		:Binop_expr(lt_binop,new Bool_type(),e1,e2) {}
	
};
class Gt_expr : public Binop_expr
{
public:
	Gt_expr(Expr* e1, Expr* e2)
		:Binop_expr(gt_binop,new Bool_type(),e1,e2) {}
	
};

class Lteq_expr : public Binop_expr
{
public:
	Lteq_expr(Expr* e1, Expr* e2)
		:Binop_expr(lt_eq_binop,new Bool_type(),e1,e2) {}
	
};

class Gteq_expr : public Binop_expr
{
public:
	Gteq_expr(Expr* e1, Expr* e2)
		:Binop_expr(gt_eq_binop,new Bool_type(),e1,e2) {}
	
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

class Assignment_expr : public Binop_expr
{
public:
	Assignment_expr(Expr* e1, Expr* e2, Type* t)
		:Binop_expr(assign_binop,t,e1,e2) {}	
};

void print(Expr* e);

void debug(std::ostream &os,  Expr* e,int indent = 0);

void s_expr(std::ostream &os, Expr* e);