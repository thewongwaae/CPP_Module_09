#include "PmergeMe.hpp"
#include <sys/time.h>

bool isValidNum( std::string num ) {
	return (num.find_first_not_of("0123456789") == std::string::npos);
}

int main( int ac, char **av ) {
	struct timeval start;
	struct timeval end;

	PmergeMe pmergeMe;
	std::vector< int > vector;
	std::list< int > list;
	std::vector< int > vector_copy;

	if (ac == 1) {
		std::cerr << "Error: no arguments given" << std::endl;
		return (1);
	}

	for (int i = 1; i < ac; i++) {
		if (!isValidNum(av[i])) {
			std::cerr << "Error: invalid argument" << std::endl;
			return (1);
		}
		vector.push_back(std::stoi(av[i]));
		list.push_back(std::stoi(av[i]));
		vector_copy.push_back(std::stoi(av[i]));
	}

	gettimeofday(&start, NULL);
	pmergeMe.fordJohnson(vector);
	gettimeofday(&end, NULL);
	int vec_elapsed = end.tv_usec - start.tv_usec;
	
	gettimeofday(&start, NULL);
	pmergeMe.fordJohnson(list);
	gettimeofday(&end, NULL);
	int lst_elapsed = end.tv_usec - start.tv_usec;

	std::cout << "Input :" << vector_copy << std::endl;
	std::cout << "Output (vector) :" << vector << std::endl;
	std::cout << "Output (list) :" << list << std::endl;

	std::cout	<< "Time to process a range of " << vector_copy.size() << " elements (vector) : "
				<< vec_elapsed << " microseconds" << std::endl;
	std::cout	<< "Time to process a range of " << vector_copy.size() << " elements (list) : "
				<< lst_elapsed << " microseconds" << std::endl;
}