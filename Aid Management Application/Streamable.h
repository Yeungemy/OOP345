/**********************************************************************
OOP244 Milestone 5: Compiling modular source code
File: Streamable.h
Date: Jul 11, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#ifndef SICT_STREAMABLE_H__
#define SICT_STREAMABLE_H__

#include <fstream>
#include <iostream>

namespace sict {
	class Streamable {
	public:
		virtual std::fstream& store(std::fstream& file, bool addNewLine = true)const = 0;
		virtual std::fstream& load(std::fstream& file) = 0;
		virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
	};
}
#endif