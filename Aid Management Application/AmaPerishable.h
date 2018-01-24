/**********************************************************************
OOP244 Milestone 5: Compiling modular source code
File: AmaPerishable.h
Date: Jul 18, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#ifndef SICT_AMAPERISHABLE_H__
#define SICT_AMAPERISHABLE_H__
#include "AmaProduct.h"
#include "Date.h"

namespace sict {
	class AmaPerishable : public AmaProduct {
		// holds expire date
		Date expiry_;
	public:
		// default constructor
		AmaPerishable(char fileTag = 'P');
		// distructor
		~AmaPerishable();
		// Returns a constant reference to expiry_ member variable
		const Date& expiry()const;
		// Sets the expiry_ attribute to the incoming value
		void expiry(const Date& value);
		// output a product from file to the compiler
		std::fstream& store(std::fstream& file, bool addNewLine = true)const;
		// read data member of a product from buffer
		std::fstream& load(std::fstream& file);
		// output data from file to the compiler
		std::ostream& write(std::ostream& os, bool linear)const;
		// read data members from the buffer
		std::istream& read(std::istream& is);
	};
}
#endif