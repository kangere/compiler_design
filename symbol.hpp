#pragma once
#include <string>
#include <unordered_set>
#include <functional>



class symbol{
private:
	std::string m_str;

public:
	symbol()
	:m_str()
	{}
	
	symbol(std::string name)
	:m_str(name)
	{}

	symbol(const char* name)
	:symbol(std::string(name))
	{}

	friend bool operator==(const symbol& lhs, const symbol& rhs)
	{
		return lhs.m_str == rhs.m_str;
	}

	friend bool operator!=(const symbol& lhs, const symbol& rhs)
	{
		return lhs.m_str != rhs.m_str; 
	}

	std::string str() const
	{return m_str;}


};


namespace std
{
	template<> 
	struct hash<symbol>
	{
		typedef std::size_t  result;
		result operator()(symbol const& s) const noexcept
		{
			result const h = std::hash<std::string>{}(s.str());

			return h;
		}
	};
}

class symbol_table: public std::unordered_set<symbol>{
public:
	symbol get(std::string& n)
	{
		return *(emplace(n).first);
	}
};



