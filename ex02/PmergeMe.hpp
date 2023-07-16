#pragma once

// https://en.cppreference.com/w/cpp/container/deque

#include <string>
#include <iostream>
#include <deque>

class PmergeMe {
	private:
		std::deque< int > _input;

	public:
		PmergeMe( void );
		PmergeMe( PmergeMe const &copy );
		PmergeMe &operator=( PmergeMe const &assign );
		~PmergeMe( void );

		void		calculate( std::string input );
};