#include "RPN.hpp"

/* Constructs */

RPN::RPN( void ) {}

RPN::RPN( RPN const &copy ) {
	*this = copy;
}

RPN &RPN::operator=( RPN const &assign ) {
	if (this != &assign) {
		// copy
	}
	return *this;
}

RPN::~RPN( void ) {}

/* Member functions */