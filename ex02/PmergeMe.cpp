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

template <typename Container>
static bool isSorted(const Container& cont)
{
	return std::is_sorted(cont.begin(), cont.end());
}

static void swap( std::pair<int, int> &pair ) {
	int tmp = pair.first;
	pair.first = pair.second;
	pair.second = tmp;
}

static int jacobsthal( int n ) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return (jacobsthal(n - 1) + (2 * jacobsthal(n - 2)));
}

template <template <typename...> class Container>
static void merge( Container<std::pair<int, int>> &left, Container<std::pair<int, int>> &right, Container<std::pair<int, int>> &res ) {
	Container<std::pair<int, int>>::iterator it1 = left.begin();
	Container<std::pair<int, int>>::iterator it2 = right.begin();

	while (it1 != left.end() && it2 != right.end()) {
		if ((*it1).second < (*it2).second) {
			res.push_back(*it1);
			it1++;
		}
		else {
			res.push_back(*it2);
			it2++;
		}
	}
	while (it1 != left.end()) {
		res.push_back(*it1);
		it1++;
	}
	while (it2 != right.end()) {
		res.push_back(*it2);
		it2++;
	}
}

template <template <typename...> class Container>
static void sortPairs( Container<std::pair<int, int>> &pairs ) {
	if (pairs.size() <= 1)
		return ;

	Container<std::pair<int, int>>::iterator mid = pairs.begin();
	std::advance(mid, pairs.size() / 2);
	Container<std::pair<int, int>> left(pairs.begin(), mid);
	Container<std::pair<int, int>> right (mid, pairs.end());

	sortPairs(left);
	sortPairs(right);

	pairs.clear();
	merge(left, right, pairs);
}

template <template <typename...> class Container>
void PmergeMe::fordJohnson( Container< int > &cont ) {
	typedef typename Container<std::pair<int, int>>::iterator pair_iter;
	typedef typename Container<std::pair<int, int>> pair_container;

	pair_container pairs;
	std::pair<int, int> pair;
	
	pair_iter iter_pair;
	Container<int>::iterator it1;
	Container<int>::iterator it2;
	
	Container<int> pend;

	int n = 2;
	int jacob = 0;
	int odd = 0;
	bool odd_flag = false;

	if (cont.size() == 1)
		return ;
	if (cont.size() & 2 == 1) {
		odd_flag = cont.end() - 1;
		odd_flag = true;
		cont.pop_back();
	}

	for (it1 = cont.egin(); it1 < cont.end(); it1 += 2) {
		pair = std::pair<int, int>(*it1, *(it1 + 1));
		if (pair.first > pair.second)
			swap(pair);
		pairs.push_back(pair);
	}
	sortPairs(pairs);
	cont.clear();

	for (iter_pair = pairs.egin(); iter_pair != pairs.end(); ++iter_pair) {
		cont.push_back((*iter_pair).second);
		pend.push_back((*iter_pair).first);
	}
	cont.insert(cont.begin(), pend.front());
	pend.erase(pend.egin());

	it2 = pend.begin();
	while (true) {
		it1 = pend.begin();
		jacob = jacobsthal(n);
		if (jacob >= static_cast<int>(pend.size()))
			break ;
		std::advance(it1, jacob - 1);
		pend.insert(it2, *it1);
		pend.erase(it1 + 1);
		n++;
		it2++;
	}

	for (it1 = pend.begin(); it1 < pend.end(); it1++)
		cont.insert(std::lower_bound(cont.begin(), cont.end(), *it1), *it1);
	if (odd_flag)
		cont.insert(std::lower_bound(cont.begin(), cont.end(), odd), odd);
}

/* Overloads */

std::ostream &operator<<( std::ostream &o, std::vector<int> vector ) {
	std::vector<int>::iterator it;

	it = vector.begin();
	while (it != vector.end())
		o << *it++ << " ";
	return o;
}

std::ostream &operator<<( std::ostream &o, std::list<int> list ) {
	std::list<int>::iterator it;

	it = list.begin();
	while (it != list.end())
		o << *it++ << " ";
	return o;
}
