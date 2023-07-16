#include "RPN.hpp"

/* Constructs */

RPN::RPN( void ) {}

RPN::RPN( RPN const &copy ) {
	*this = copy;
}

RPN &RPN::operator=( RPN const &assign ) {
	if (this != &assign)
		_stack = assign._stack;
	return *this;
}

RPN::~RPN( void ) {}

/* Member functions */

void RPN::do_op( std::string const &op ) {
	if (_stack.size() < 2)
		throw std::runtime_error("Not enough values in stack");
	
	int num2 = _stack.top();
	_stack.pop();
	int num1 = _stack.top();
	_stack.pop();

	if (op == "+")
		_stack.push(num1 + num2);
	else if (op == "-")
		_stack.push(num1 - num2);
	else if (op == "*")
		_stack.push(num1 * num2);
	else if (op == "/") {
		if (num2 == 0)
			throw std::logic_error("Division by zero");
		_stack.push(num1 / num2);
	}
	else
		throw std::runtime_error("Unknown operator");
}

void RPN::calculate( std::string const &input ) {
	std::stringstream	ss(input);
	std::string			token;

	while (std::getline(ss, token, ' ')) {
		if (token == "+" || token == "-" || token == "*" || token == "/")
			do_op(token);
		else
			_stack.push(atoi(token.c_str()));
	}
}

int RPN::result( void ) const {
	if (_stack.size() != 1)
		throw std::runtime_error("Invalid stack size");
	return _stack.top();
}
