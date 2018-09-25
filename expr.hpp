#pragma once

#include "type.hpp"

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