#pragma once

// https://en.cppreference.com/w/cpp/container/list
// https://en.cppreference.com/w/cpp/container/vector  

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

class PmergeMe {
	public:
		PmergeMe( void );
		PmergeMe( PmergeMe const &copy );
		PmergeMe &operator=( PmergeMe const &assign );
		~PmergeMe( void );
		
		template <template <typename...> class Container>
		void fordJohnson( Container< int > &cont );
};

std::ostream &operator<<( std::ostream &o, std::vector<int> vector );
std::ostream &operator<<( std::ostream &o, std::list<int> list );