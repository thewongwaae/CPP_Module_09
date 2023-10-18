#pragma once

// https://en.cppreference.com/w/cpp/container/vector
// https://en.cppreference.com/w/cpp/container/list

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

class PMergeMe {
	public:
		PMergeMe( void );
		PMergeMe( const PMergeMe &copy );
		PMergeMe &operator=( const PMergeMe &assign );
		~PMergeMe( void );

		template< typename T >
		bool	checkIfOdd( T container );

		void	fordJohnson( std::vector< int > &vector );
		void	fordJohnson( std::list< int > &list );
};

std::ostream &operator<<( std::ostream &o, std::vector< int > &vector );
std::ostream &operator<<( std::ostream &o, std::list< int > &list );