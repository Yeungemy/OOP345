/**********************************************************************
OOP244 Milestone 5: Compiling modular source code
File: AmaProduct.h
Date: Jul 18, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__
#include <iostream>
#include "Product.h"
#include "ErrorMessage.h"

namespace sict {
	class AmaProduct : public Product {
		// Holds a single character to tag the records as  
		// Perishable or non-Perishable product in a file
		char fileTag_;
		// Unit of Measurement (i.e. Kg, Liters, …) 
		char unit_[11];
	protected:
		ErrorMessage err_;
	public:
		// constructor receives the value for the filetag_
		AmaProduct(char fileTag = 'N');
		// destructor
		~AmaProduct();
		// returns a constant pointer to the unit_ member variable
		const char* unit()const;
		// Copies the incoming value string into the unit_ string
		// Make sure copying does not pass the size of the unit_ array
		void unit(const char* value);

		// ouput the product to the compiler
		std::fstream& store(std::fstream& file, bool addNewLine = true)const;
		// read data member from the buffer
		std::fstream& load(std::fstream& file);
		// prints the prodcut in the format of form or linear
		std::ostream& write(std::ostream& ostr, bool linear)const;
		// Receives the values using istream
		std::istream& read(std::istream& istr);
	};
}

#endif