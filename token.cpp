#include "token.hpp"

#include <iostream>

bool
token::is_arithmetic() const
{
	return (m_type == plus) ||
			(m_type == minus) ||
			(m_type == mult) ||
			(m_type == div) ||
			(m_type == percent);
}

bool
token::is_relational() const
{
	return (m_type == eq_eq) ||
			(m_type == n_eq) ||
			(m_type == lt) ||
			(m_type == gt) ||
			(m_type == lt_eq) ||
			(m_type == gt_eq);
}

bool
token::is_logical() const
{
	return (m_type == not_kw) ||
			(m_type == and_kw) ||
			(m_type == or_kw);
}

bool
token::is_literal() const
{
	return (m_type == int_lit) ||
			(m_type == bool_lit) ||
			(m_type == float_lit);
}

bool
token::is_punctuation() const
{
	return (m_type == lparen) ||
			(m_type == rparen) ||
			(m_type == lbrack) ||
			(m_type == rbrack) ||
			(m_type == comma) ||
			(m_type == semi_colon) ||
			(m_type == colon) ||
			(m_type == arrow);
}

std::ostream&
operator<<(std::ostream& os, token const& t){
	os << t.get_lexme().str();

	return os;
}