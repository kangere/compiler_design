#pragma once

#include "type.hpp"
#include <vector>

class Expr
{
public:
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

protected:
	Expr(kind k) : m_kind(k) 
	{}
	Expr(kind k, Type* t)
	{}

private:
	kind m_kind;
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
	Int_expr(Int_type* t,int v): Expr(int_kind,t), val(v)
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

	float get_val() const {return val;}
};

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

class Unary_expr : public Tuple
{
public:
	enum unary_type
	{
		not_unary,
		negation_unary
	};
	
	unary_type get_type() const { return m_type;}

protected:
	Unary_expr(unary_type t): 
	Tuple(1,unary_kind), m_type(t)
	{}

private:
	unary_type m_type;
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

void print(Expr e);