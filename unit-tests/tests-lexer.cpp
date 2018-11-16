#include "catch.hpp"
#include "lexer.hpp"

#include <iterator>
#include <iostream>
#include <string>
#include <fstream>


TEST_CASE("Lexer Tests","[Lexer]"){

	std::ifstream ifs("sam.mc", std::ios::in);

	if(ifs.is_open()){

		std::istreambuf_iterator<char> first(ifs);
		std::istreambuf_iterator<char> limit;
		std::string input(first, limit);

		symbol_table syms;

		lexer lex(syms,input);

		
		while(token t = lex.next_token()){
			
			std::cout << t << " line: " << t.line_number() 
			<< " column: " << t.column() <<std::endl;

		}

	} else {
		std::cout << "unable to open file\n";
	
	}


	ifs.close();	

}

TEST_CASE("Lexer Literals test","[Lexer]"){

	std::ifstream ifs("nums.mc", std::ios::in);

	if(ifs.is_open()){

		std::istreambuf_iterator<char> first(ifs);
		std::istreambuf_iterator<char> limit;
		std::string input(first, limit);

		symbol_table syms;

		lexer lex(syms,input);

		
		CHECK(lex.next_token().get_type() == token::int_lit);
		CHECK(lex.next_token().get_type() == token::int_lit);
		CHECK(lex.next_token().get_type() == token::int_lit);
		CHECK(lex.next_token().get_type() == token::int_lit);
		CHECK(lex.next_token().get_type() == token::int_lit);

		CHECK(lex.next_token().get_type() == token::float_lit);
		CHECK(lex.next_token().get_type() == token::float_lit);
		CHECK(lex.next_token().get_type() == token::float_lit);
		CHECK(lex.next_token().get_type() == token::float_lit);
		CHECK(lex.next_token().get_type() == token::float_lit);
		CHECK(lex.next_token().get_type() == token::float_lit);
		CHECK(lex.next_token().get_type() == token::float_lit);
		CHECK(lex.next_token().get_type() == token::float_lit);
		CHECK(lex.next_token().get_type() == token::float_lit);

	} else {
		std::cout << "unable to open file\n";
	}

	ifs.close();
}