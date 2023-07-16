#pragma once

// https://en.cppreference.com/w/cpp/container/map

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <map>

class BitcoinExchange {
	private:
		std::map< std::string, float > _data;

	public:
		BitcoinExchange( void );
		BitcoinExchange( BitcoinExchange const &copy );
		BitcoinExchange &operator=( BitcoinExchange const &copy );
		~BitcoinExchange( void );

		void push( std::string const date, std::string const price );
		void pop( std::string const date );
		float calculatePrice( std::string date, float amount );
};

bool validDate( std::string const date );
bool validPrice( std::string const price );