#pragma once

#include <iosfwd>

class Type {

public:
	enum Kind
	{
		bool_type,
		int_type,
		float_type,
		ref_type
	};

	Kind get_kind() const { return m_kind;}

protected:
	Type(Kind k): m_kind(k) {}


private:
	Kind m_kind;
};

class Bool_type : public Type {
public:
	Bool_type(): Type(bool_type) 
	{}
};


class Int_type : public Type {

public:
	Int_type(): Type(int_type)
	{}
};

class Float_type : public Type {

public:
	Float_type(): Type(float_type)
	{}
};

class Ref_type : public Type {
private:
	Type* m_ref;

public:
	Ref_type(Type* t)
		:Type(ref_type), m_ref(t)
		{}
	
	Type* get_ref_type () const { return m_ref;}
};


//Check equality of types
bool equal(Type const* t1, Type const* t2);

std::ostream& operator<<(std::ostream& os, Type const& t);