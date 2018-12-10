#pragma once

#include <vector>
#include <unordered_map>
#include "decl.hpp"
#include "symbol.hpp"
#include <stdexcept>
#include <iostream>


struct scope : std::unordered_map<symbol,Decl*> {

	Decl* lookup(symbol sym)
	{
		auto iter = find(sym);

		if(iter == end())
			return nullptr;

		return iter->second;		
	}

	void declare(symbol sym, Decl* d){
		if(count(sym) != 0)
			throw std::runtime_error(d->get_name() + " has already been declared");

		insert(std::make_pair(sym,d));
	}
};

struct scope_stack : std::vector<scope>
{

	Decl* lookup(symbol sym){

		for(auto iter = rbegin(); iter != rend();++iter){
			if(Decl* d = iter->lookup(sym))
				return d;
		}

		return nullptr;
	}


};