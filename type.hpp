#pragma once

#include <iosfwd>
#include <vector>
class Type {

public:
	enum Kind
	{
		bool_type,
		int_type,
		float_type,
		ref_type,
		func_type
	};

	Kind get_kind() const { return m_kind;}
	bool same_as(Type*);

	virtual bool is_arithmetic() = 0;

protected:
	Type(Kind k): m_kind(k) {}


private:
	Kind m_kind;
};

class Bool_type : public Type {
public:
	Bool_type(): Type(bool_type) 
	{}

	bool is_arithmetic()
	{return false;}
};


class Int_type : public Type
{

public:
	Int_type(): Type(int_type)
	{}

	bool is_arithmetic()
	{return true;}

};

class Float_type : public Type
{

public:
	Float_type(): Type(float_type)
	{}

	bool is_arithmetic()
	{return true;}
};

class Ref_type : public Type 
{
private:
	Type* m_ref;

public:
	Ref_type(Type* t)
		:Type(ref_type), m_ref(t)
		{}

	bool is_arithmetic()
	{return false;}

	Type* get_ref_type () const { return m_ref;}
};

class Func_type : public Type
{
private:
	std::vector<Type*> args;
	Type* return_type;

public:
	Func_type()
	: Type(func_type){}

	Func_type(Type* t)
	:Type(func_type), return_type(t)
	{}

	bool is_arithmetic()
	{return false;}
	
	void add_param(Type* p)
	{args.push_back(p);}

	void set_return_type(Type* t)
	{return_type = t;}

	int num_params () const
	{return args.size();}

	std::vector<Type*> get_args () const
	{return args;}
};


void print(std::ostream &os, Type const* t);

std::ostream& operator<<(std::ostream& os, Type const& t);