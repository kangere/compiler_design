#pragma once

class location{
private:
	unsigned int m_row;
	unsigned int m_column;

public:
	location()
	{}
	
	location(unsigned int row, unsigned int col)
	:m_row(row), m_column(col)
	{}

	unsigned int row() const
	{return m_row;}

	unsigned int column() const
	{return m_column;}
};