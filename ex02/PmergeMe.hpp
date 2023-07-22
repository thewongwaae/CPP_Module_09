#pragma once

// https://en.cppreference.com/w/cpp/container/list
// https://en.cppreference.com/w/cpp/container/vector  

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

class PmergeMe {
	private:
		std::vector< int > _vector;
		std::list< int > _list;

	public:
		PmergeMe( void );
		PmergeMe( PmergeMe const &copy );
		PmergeMe &operator=( PmergeMe const &assign );
		~PmergeMe( void );

		void queueNumbers( std::list<int>::iterator begin, std::list<int>::iterator end );

		template <template <typename...> class Container>
		void fordJohnson( void );

		const std::vector< int > &getVector( void ) const;
		const std::list< int > &getList( void ) const;
};

std::ostream &operator<<( std::ostream &o, std::vector<int> vector );
std::ostream &operator<<( std::ostream &o, std::list<int> list );