#include "PMergeMe.hpp"

/* Constructors */

PMergeMe::PMergeMe( void ) { }

PMergeMe::PMergeMe( const PMergeMe &copy ) {
	*this = copy;
}

PMergeMe &PMergeMe::operator=( const PMergeMe &assign ) {
	return *this;
}

PMergeMe::~PMergeMe( void ) { }

/* Utilities */

template< typename T >
bool PMergeMe::checkIfOdd( T container ) {
	if (container.size() % 2 == 0)
		_isOdd = false;
	else
		_isOdd = true;
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

void insertionSort( std::vector<std::pair<int,int>> &pairs, int size ) {
	if (size <= 1)
		return ;

	insertionSort(pairs. size - 1);

	std::pair< int, int > last = pairs.back();
	int i = size - 2;

	while (i >= 0 && pairs[i].second > last.second) {
		pairs[i + 1] = pairs[i];
		i--;
	}

	pairs[i + 1] = last;
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
			S.insert(S.begin() + (it - S.begin()), pend[i]);
			tmp.push_back(pend[i]);
		}
	}
}

void insertionSort( std::list<std::pair<int,int>> &pairs, int size ) {
	std::list<std::pair<int,int>>::iterator curr = pairs.begin();
	std::list<std::pair<int,int>>::iterator sorted = pairs.begin();

	for (int i = 0; i < size; i++) {
		std::pair< int, int > val = *curr;
		std::list<std::pair<int,int>>::iterator correct = pairs.begin();

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
	for (typename Pair::iterator it = pairs.begin();i t != pairs.end(); it++) {
		pend.push_back(it->first);
		S.push_back(it->second);
	}

	S.insert(S.begin(), pend.first());
	if (!pend.empty())
		pend.erase(pend.begin());

	mergeSort(pend, S);
}

/* Ford Johnson algorithm */

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

	pairs = storePairs< std::vector<std::pair<int, int>>, std::vector<int> > (vector);
	insertionSort(pairs, pairs.size());
	mergeSort< std::vector<std::pair<int,int>>, std::vector<int> > (pairs, pend, S);

	if (isOdd) {
		std::vector< int >::iterator it = std::lower_bound(S.begin(), S.end(), oddValue);
		if (it == S.end())
			S.push_back(oddValue);
		else
			S.insert(it, oddValue);
	}

	vector = S;
	if (!std::is_sorted(vector.begin(), vector.end()))
		throw std::logic_error("Vector is not sorted");
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

	pairs = storePairs< std::list<std::pair<int, int>>, std::list<int> > (list);
	insertionSort(pairs, pairs.size());
	mergeSort< std::list<std::pair<int,int>>, std::list<int> > (pairs, pend, S);

	if (isOdd) {
		std::list< int >::iterator it = std::lower_bound(S.begin(), S.end(), oddValue);
		if (it == S.end())
			S.push_back(oddValue);
		else
			S.insert(it, oddValue);
	}

	list = S;
	if (!std::is_sorted(list.begin(), list.end()))
		throw std::logic_error("List is not sorted");
}