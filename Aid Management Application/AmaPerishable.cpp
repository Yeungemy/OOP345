/**********************************************************************
OOP244 Milestone 5: Compiling modular source code
File: AmaPerishable.cpp
Date: Jul 18, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include <iomanip>

#include "AmaPerishable.h"
using namespace std;

namespace sict {
	// default constructor
	AmaPerishable::AmaPerishable(char fileTag) : AmaProduct(fileTag) {
		unit("");
	}

	// distructor
	AmaPerishable::~AmaPerishable() {

	}

	// Returns a constant reference to expiry_ member variable
	const Date& AmaPerishable::expiry()const {
		return expiry_;
	}

	// Sets the expiry_ attribute to the incoming value
	void AmaPerishable::expiry(const Date& value) {
		expiry_ = value;
	}

	// output a product from file to the compiler
	std::fstream& AmaPerishable::store(std::fstream& file, bool addNewLine)const {
		AmaProduct::store(file, false);
		file << "," << expiry();
		if (addNewLine == true) {
			file << endl;
		}
		return file;
	}

	// read data member of a product from buffer
	std::fstream& AmaPerishable::load(std::fstream& file) {
		AmaProduct::load(file);
		expiry_.read(file);
		return file;
	}

	// output data from file to the compiler
	std::ostream& AmaPerishable::write(std::ostream& ostr, bool linear)const {
		AmaProduct::write(ostr, linear);
		if (AmaProduct::err_.isClear() && !Product::isEmpty()) {
			linear ? ostr << expiry() : ostr << "Expiry date: " << expiry() << endl;
		}
		return ostr;
	}

	// read data members from the buffer
	std::istream& AmaPerishable::read(std::istream& istr) {
		AmaProduct::read(istr);
		if (AmaProduct::err_.isClear()) {
			std::cout << "Expiry date (YYYY/MM/DD): ";
			Date temp;
			// Enhanced: call overload operator >> from Date.cpp
			istr >> temp;
			if (temp.bad()) {
				switch (temp.errCode()) {
				case CIN_FAILED:
					istr.setstate(ios::failbit);
					err_.message("Invalid Date Entry");
					break;
				case YEAR_ERROR:
					istr.setstate(ios::failbit);
					err_.message("Invalid Year in Date Entry");
					break;
				case MON_ERROR:
					istr.setstate(ios::failbit);
					err_.message("Invalid Month in Date Entry");
					break;
				case DAY_ERROR:
					istr.setstate(ios::failbit);
					err_.message("Invalid Day in Date Entry");
					break;
				}
				istr.setstate(ios::failbit);
				// enhanced: delete set instance variables to zero
			}
			else {
				this->expiry_ = temp;
			}
		}
		return istr;
	}
}