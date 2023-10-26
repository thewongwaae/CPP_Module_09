#include "PMergeMe.hpp"
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>

static bool isValidNum(const std::string& num) {
	return num.find_first_not_of("0123456789") == std::string::npos;
}

template <typename T>
static void checkDup(T container) {
	typename T::iterator it1;
	typename T::iterator it2;

	for (it1 = container.begin(); it1 != container.end(); it1++) {
		it2 = it1;
		it2++;
		while (it2 != container.end()) {
			if (*it1 == *it2) {
				throw std::logic_error("Input contains duplicate values");
			}
			it2++;
		}
	}
}

int main(int ac, char** av) {
	struct timeval start;
	struct timeval end;

	PMergeMe PMergeMe;
	std::vector<int> vector;
	std::list<int> list;
	std::vector<int> vector_copy;

	if (ac == 1) {
		std::cerr << "Error: no arguments given" << std::endl;
		return 1;
	}

	try {
		for (int i = 1; i < ac; i++) {
			if (!isValidNum(av[i]))
				throw std::logic_error("Input contains non-numeric values");
			vector.push_back(atoi(av[i]));
			list.push_back(atoi(av[i]));
			vector_copy.push_back(atoi(av[i]));
		}

		checkDup(vector);
		checkDup(list);

		gettimeofday(&start, NULL);
		PMergeMe.fordJohnson(vector);
		gettimeofday(&end, NULL);
		int vec_elapsed = end.tv_usec - start.tv_usec;

		gettimeofday(&start, NULL);
		PMergeMe.fordJohnson(list);
		gettimeofday(&end, NULL);
		int lst_elapsed = end.tv_usec - start.tv_usec;

		std::cout << "Input\t\t:";
		for (std::vector<int>::const_iterator it = vector_copy.begin(); it != vector_copy.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		std::cout << "Output (vector)\t:";
		for (std::vector<int>::const_iterator it = vector.begin(); it != vector.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		std::cout << "Output (list)\t:";
		for (std::list<int>::const_iterator it = list.begin(); it != list.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		std::cout << "Time to process a range of " << vector_copy.size() << " elements (vector) : "
				<< vec_elapsed << " microseconds" << std::endl;
		std::cout << "Time to process a range of " << vector_copy.size() << " elements (list) : "
				<< lst_elapsed << " microseconds" << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
