#include "PMergeMe.hpp"

/* Constructors */

PMergeMe::PMergeMe( void ) { }

PMergeMe::PMergeMe( const PMergeMe &copy ) {
	*this = copy;
}

PMergeMe &PMergeMe::operator=( const PMergeMe &assign ) {
	(void) assign;
	return *this;
}

PMergeMe::~PMergeMe( void ) { }

/* Utilities */

template< typename T >
bool PMergeMe::checkIfOdd( T container ) {
	if (container.size() % 2 == 0)
		return false;
	return true;
}

template< typename Pair, typename T >
Pair storePairs( T container ) {
	typename T::iterator it;
	int n1, n2;
	Pair res;

	for (it = container.begin(); it != container.end(); it++) {
		std::pair< int, int > pair;

		n1 = *it;
		it++;
		n2 = *it;
		
		if (n1 > n2)
			pair = std::make_pair(n2, n1);
		else
			pair = std::make_pair(n1, n2);

		res.push_back(pair);
	}

	return (res);
}

static int jacobsthal( int i ) {
	if (i == 0)
		return 0;
	if (i == 1)
		return 1;

	return (jacobsthal(i - 1) + 2 * jacobsthal(i - 2));
}

/* Sorters */

void insertionSort( std::vector< std::pair<int, int> > &pairs, int size ) {
    if (size == 1)
		return ;

	insertionSort(pairs, size - 1);

	std::pair< int, int > val = pairs[size - 1];
	int i = size - 2;
	while (i >= 0 && pairs[i].second > val.second) {
		pairs[i + 1] = pairs[i];
		i--;
	}

	pairs[i + 1] = val;
}

void mergeSort( std::vector< int > &pend, std::vector< int > &S ) {
	std::vector< int > tmp;
	int pendSize = pend.size();

	for (int i = 2; i < pendSize; i++) {
		int jct = jacobsthal(i);
		if (jct > pendSize)
			break ;

		tmp.push_back(pend[jct - 1]);
		std::vector< int >::iterator it = std::lower_bound(S.begin(), S.end(), pend[jct - 1]);
		S.insert(S.begin(), + (it - S.begin()), pend[jct - 1]);
		pend[jct - 1] = -1;
	}

	for (int i = 0; i < pendSize; i ++) {
		if (pend[i] != -1) {
			std::vector< int >::iterator it = std::lower_bound(S.begin(), S.end(), pend[i]);
			S.insert(it, pend[i]);
			tmp.push_back(pend[i]);
		}
	}
}

void insertionSort( std::list< std::pair<int,int> > &pairs, int size ) {
	std::list< std::pair<int,int> >::iterator curr = pairs.begin();
	std::list< std::pair<int,int> >::iterator sorted = pairs.begin();

	for (int i = 0; i < size; i++) {
		std::pair< int, int > val = *curr;
		std::list< std::pair<int,int> >::iterator correct = pairs.begin();

		while (correct != curr && correct->second < val.second)
			correct++;

		if (correct != curr) {
			pairs.erase(curr);
			pairs.insert(correct, val);
			curr = sorted;
		}

		sorted = curr;
		curr++;
	}
}

void mergeSort( std::list< int > &pend, std::list< int > &S ) {
	std::list< int > tmp;
	int pendSize = pend.size();

	for (int i = 2; i < pendSize; i++) {
		int jct = jacobsthal(i);
		if (jct > pendSize)
			break ;

		std::list< int >::iterator jctPos = pend.begin();
		std::advance(jctPos, jct - 1);
		tmp.push_back(*jctPos);

		std::list< int >::iterator lower;
		for (lower = S.begin(); lower != S.end(); lower++) {
			if (*lower > *jctPos)
				break ;
		}
		tmp.insert(lower, *jctPos);
		*jctPos = -1;
	}

	for (std::list< int >::iterator it = pend.begin(); it != pend.end(); it++) {
		if (*it != -1) {
			tmp.push_back(*it);
			std::list< int >::iterator lower;
			for (lower = S.begin(); lower != S.end(); lower++) {
				if (*lower > *it)
					break ;
			}
			tmp.insert(lower, *it);
		}
	}

	pend.clear();
	pend = tmp;
}

template< typename Pair, typename T >
void mergeSort( Pair &pairs, T &pend, T &S ) {
	for (typename Pair::iterator it = pairs.begin(); it != pairs.end(); it++) {
		pend.push_back(it->first);
		S.push_back(it->second);
	}

	S.insert(S.begin(), pend.front());
	if (!pend.empty())
		pend.erase(pend.begin());

	mergeSort(pend, S);
}

/* Ford Johnson algorithm */

template <typename T>
static bool isSorted( const T& container ) {
	if (container.empty())
		return true;

	typename T::const_iterator it = container.begin();
	typename T::const_iterator next = it;
	next++;

	while (next != container.end()) {
		if (*next < *it)
			return false;

		it++;
		next++;
	}

	return true;
}

void PMergeMe::fordJohnson( std::vector< int > &vector ) {
	bool isOdd;
	int oddValue;
	std::vector< std::pair< int, int > > pairs;
	std::vector< int > pend;
	std::vector< int > S;

	isOdd = checkIfOdd(vector);
	if (isOdd) {
		oddValue = vector.back();
		vector.pop_back();
	}

	pairs = storePairs< std::vector< std::pair< int, int > >, std::vector< int > > (vector);
	insertionSort(pairs, pairs.size());
	mergeSort< std::vector< std::pair< int, int > >, std::vector< int > > (pairs, pend, S);

	if (isOdd) {
		std::vector< int >::iterator it = std::lower_bound(S.begin(), S.end(), oddValue);
		if (it == S.end())
			S.push_back(oddValue);
		else
			S.insert(it, oddValue);
	}

	vector = S;
	// if (!isSorted(vector))
	// 	throw std::logic_error("Vector is not sorted");
}

void PMergeMe::fordJohnson( std::list< int > &list ) {
	bool isOdd;
	int oddValue;
	std::list< std::pair< int, int > > pairs;
	std::list< int > pend;
	std::list< int > S;

	isOdd = checkIfOdd(list);
	if (isOdd) {
		oddValue = list.back();
		list.pop_back();
	}

	pairs = storePairs< std::list< std::pair< int, int > >, std::list< int > > (list);
	insertionSort(pairs, pairs.size());
	mergeSort< std::list< std::pair< int, int > >, std::list< int > > (pairs, pend, S);

	if (isOdd) {
		std::list< int >::iterator it = std::lower_bound(S.begin(), S.end(), oddValue);
		if (it == S.end())
			S.push_back(oddValue);
		else
			S.insert(it, oddValue);
	}

	list = S;
	// if (!isSorted(list))
	// 	throw std::logic_error("List is not sorted");
}

/* Operators */

std::ostream &operator<<( std::ostream &o, std::vector< int > &vector ) {
	for (std::vector< int >::iterator it = vector.begin(); it != vector.end(); it++) {
		if (it != vector.begin())
			o << ", ";
		o << *it;
	}

	return (o);
}

std::ostream &operator<<( std::ostream &o, std::list< int > &list ) {
	for (std::list< int >::iterator it = list.begin(); it != list.end(); it++) {
		if (it != list.begin())
			o << ", ";
		o << *it;
	}

	return (o);
}