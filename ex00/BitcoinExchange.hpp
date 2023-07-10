#pragma once

#include <iostream>
#include <fstream>
#include <map>

class BitcoinExchange {
	private:
		std::map< std::string, float > _data;

	public:
		BitcoinExchange( void );
		BitcoinExchange( BitcoinExchange const &copy );
		BitcoinExchange &operator=( BitcoinExchange const &copy );
		~BitcoinExchange( void );

		void push( std::string const date, float price );
		void pop( std::string const date );
}

bool validDate( std::string const date );
bool validPrice( std::string const price );