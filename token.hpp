#pragma once

#include "symbol.hpp"
#include "location.hpp"

#include <iosfwd>

class token{

public:
	enum type{
		//misc
		eof,


		identifier,

		//punctuators
		lparen,
		rparen,
		lbrack,
		rbrack,
		comma,
		semi_colon,
		colon,
		arrow,

		//keywords
		bool_kw,
		break_kw,
		continue_kw,
		fun_kw,
		else_kw,
		false_kw,
		float_kw,
		if_kw,
		int_kw,
		let_kw,
		not_kw, //logical operators
		or_kw,	//logical operators
		and_kw,	//logical operators
		ref_kw,
		return_kw,
		true_kw,
		var_kw,
		while_kw,

		//relational operator
		eq_eq,
		n_eq,
		lt,
		gt,
		lt_eq,
		gt_eq,

		//arithmetic operators
		plus,
		minus,
		mult,
		div,
		percent,

		qmark, //conditional operator
		equal, //assignment operator

		//literals
		bool_lit,
		int_lit,
		float_lit,
		invalid_num
			
	};
private:
	symbol  m_lexme;
	location m_loc;
	type m_type;

public:
	token(symbol s, location l, type t)
	:m_lexme(s), m_loc(l), m_type(t)
	{}

	explicit operator bool() const { return m_type != eof; }

	type get_type() const
	{return m_type;}

	symbol get_lexme() const
	{return m_lexme;}

	location get_location() const
	{return m_loc;}

	bool is_eof() const
	{return m_type == eof;}
	
	bool is_arithmetic() const;

	bool is_relational() const;

	bool is_logical() const;

	bool is_literal() const;

	bool is_punctuation() const;

	bool is_invalid_num() const { return m_type == invalid_num;} 

	int line_number() const
	{return m_loc.row();}

	int column() const
	{return m_loc.column();}
};

std::ostream& operator<<(std::ostream&,token const&);