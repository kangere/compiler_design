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
	Expr(kind k, Type* t): m_kind(k), m_type(t)
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

//base classes for expression that contain expression lists
class Tuple : public Expr
{
protected:
	//number of member expressions
	int size; 
	std::vector<Expr*> expr_list;

public:
	Tuple(int s,kind k): Expr(k), size(s)
	{ expr_list.reserve(size);}

	void set_m_expr(int index, Expr* e)
	{expr_list[index] = e; }

	Expr* get_m_expr(int index)
	{return expr_list[index];}
};

enum unop
{
	logneg_uop,
	neg_uop
};

class Unop_expr : public Tuple
{
public:	
	unop get_operator() const { return m_type;}

protected:
	Unop_expr(unop t): 
	Tuple(1,unop_kind), m_type(t)
	{}

private:
	unop m_type;
};

class Binary_expr : public Tuple 
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
	Binary_expr(binop t): 
	Tuple(2,binop_kind), m_type(t)
	{}

private:
	binop m_type;
};

class Cond_expr : public Tuple
{
public:
	Cond_expr():Tuple(3, cond_kind)
	{}
};


class Logneg_expr : public Unop_expr 
{
public:
	Logneg_expr(Expr* e):Unop_expr(logneg_uop)
	{set_m_expr(0,e);}
};

class Negation_expr : public Unop_expr
{
public:
	Negation_expr(Expr* e):Unop_expr(neg_uop)
	{set_m_expr(0,e);}
};



void print(Expr* e);