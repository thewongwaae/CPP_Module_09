#pragma once

// https://en.cppreference.com/w/cpp/container/vector
// https://en.cppreference.com/w/cpp/container/list

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <sys/time.h>
#include <iomanip>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define CLEAR "\033[0m"

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