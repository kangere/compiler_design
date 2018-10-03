#pragma once

#include "type.hpp"
#include <vector>

enum kind
{
	bool_kind,
	int_kind,
	float_kind,
	id_kind,
	unary_kind,
	binary_kind,
	ternary_kind
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
	Expr(kind k, Type* t)
	{}


};

class Bool_expr: public Expr 
{
public:
	Bool_expr(Bool_type* t, bool b): Expr(bool_kind, t), val(b) 
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
	int size;
	std::vector<Expr*> expr_list;

public:
	Tuple(int s,kind k): size(s), Expr(k)
	{ expr_list.reserve(size);}

	void set_m_expr(int index, Expr* e)
	{expr_list[index] = e; }

	Expr* get_m_expr(int index)
	{return expr_list[index];}
};

enum unary_op
{
	logical_neg_uop,
	neg_uop
};

class Unary_expr : public Tuple
{
public:	
	unary_op get_operator() const { return m_type;}

protected:
	Unary_expr(unary_op t): 
	Tuple(1,unary_kind), m_type(t)
	{}

private:
	unary_op m_type;
};

class Binary_expr : public Tuple 
{
public:
	enum bin_type
	{
		and_bin,
		or_bin,
		eq_bin,
		neq_bin,
		lt_bin,
		gt_bin,
		lt_eq_bin,
		gt_eq_bin,
		add_bin,
		sub_bin,
		mult_bin,
		div_bin,
		rem_bin
	};

	bin_type get_type() const { return m_type;}

protected:
	Binary_expr(bin_type t): 
	Tuple(2,binary_kind), m_type(t)
	{}



private:
	bin_type m_type;
};

class Ternary_expr : public Tuple
{
public:
	

	enum tern_type
	{
		if_tern
	};

	tern_type get_type() const { return m_type;}

protected:
	Ternary_expr(tern_type t): 
	Tuple(3,ternary_kind), m_type(t)
	{}

private:
	tern_type m_type;
};

class Logical_neg_expr : public Unary_expr 
{
public:
	Logical_neg_expr(Expr* e):Unary_expr(logical_neg_uop)
	{set_m_expr(0,e);}
};

class Negation_expr : public Unary_expr
{
public:
	Negation_expr(Expr* e):Unary_expr(neg_uop)
	{set_m_expr(0,e);}
};



void print(Expr* e);