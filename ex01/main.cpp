#include "RPN.hpp"

int main( int ac, char **av ) {
	if (ac != 2) {
		std::cerr << "Usage: ./RPN '... input ...'" << std::endl;
		return 1;
	}

	try {
		RPN calculator;
		calculator.calculate(av[1]);
		std::cout << calculator.result() << std::endl;
	}
	catch (std::exception const &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}