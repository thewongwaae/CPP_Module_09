#include "PmergeMe.hpp"

/* Constructs */

PmergeMe::PmergeMe( void ) {}

PmergeMe::PmergeMe( PmergeMe const &copy ) {
	*this = copy;
}

PmergeMe &PmergeMe::operator=( PmergeMe const &assign ) {
	if (this == &assign)
		return *this;

	_vector = assign.getVector();
	_list = assign.getList();
	return *this;
}

PmergeMe::~PmergeMe( void ) {}

/* Members */

void PmergeMe::queueNumbers( std::list<int>::iterator begin, std::list<int>::iterator end ) {
	_list.insert( _list.end(), begin, end );
}

template <typename Container>
bool PmergeMe::isSorted(const Container& cont)
{
    return std::is_sorted(cont.begin(), cont.end());
}

/* Getters */

const std::vector< int > &PmergeMe::getVector( void ) const {
	return _vector;
}

const std::list< int > &PmergeMe::getList( void ) const {
	return _list;
}