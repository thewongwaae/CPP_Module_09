#pragma once

// https://en.cppreference.com/w/cpp/container/list

#include <string>
#include <iostream>
#include <list>

class RPN {
	private:
		std::list< std::string > _input;

	public:
		RPN( void );
		RPN( RPN const &copy );
		RPN &operator=( RPN const &assign );
		~RPN( void );

		void		calculate( std::string input );
};