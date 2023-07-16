#pragma once

// https://en.cppreference.com/w/cpp/container/list

#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stack>

class RPN {
	private:
		std::stack< int > _stack;

	public:
		RPN( void );
		RPN( RPN const &copy );
		RPN &operator=( RPN const &assign );
		~RPN( void );

		void do_op( std::string const &op );
		void calculate( std::string const &input );
		int result( void ) const;
};