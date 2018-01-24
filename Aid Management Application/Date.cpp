/**********************************************************************
OOP244 Milestone 1: Compiling modular source code
File: Date.cpp
Date: Jul 6, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Date.h"
#include "general.h"
using namespace std;

namespace sict {
	int Date::value()const {
		return year_ * 372 + mon_ * 31 + day_;
	}

	// Sets the readErrorCode_ member-variable to one of the values mentioned
	void Date::errCode(int errorCode) {
		switch (errorCode) {
		case 0:
			readErrorCode_ = NO_ERROR;
			break;
		case 1:
			readErrorCode_ = CIN_FAILED;
			break;
		case 2:
			readErrorCode_ = YEAR_ERROR;
			break;
		case 3:
			readErrorCode_ = MON_ERROR;
			break;
		case 4:
			readErrorCode_ = DAY_ERROR;
			break;
		}
	}

	// Default constructor
	Date::Date() {
		readErrorCode_ = 0;
		year_ = 0;
		mon_ = 0;
		day_ = 0;
	}

	// Constructor with three arguments
	Date::Date(int y, int m, int d) {
		readErrorCode_ = 0;
		year_ = y;
		mon_ = m;
		day_ = d;
	}

	// Destructor
	Date::~Date() {

	}

	// Comparison Logical operator overloads: 
	bool Date::operator==(const Date& D)const {
		// enhanced: directly return rather than set extra variable
		return value() == D.value();
	}

	bool Date::operator!=(const Date& D)const {
		// enhanced: directly return rather than set extra variable
		return this->value() != D.value();
	}

	bool Date::operator<(const Date& D)const {
		// enhanced: directly return rather than set extra variable
		return this->value() < D.value();
	}

	bool Date::operator>(const Date& D)const {
		// enhanced: directly return rather than set extra variable
		return this->value() > D.value();
	}

	bool Date::operator<=(const Date& D)const {
		// enhanced: directly return rather than set extra variable
		return this->value() <= D.value();
	}

	bool Date::operator>=(const Date& D)const {
		// enhanced: directly return rather than set extra variable
		return this->value() >= D.value();
	}

	// Returns the number of days in a month
	int Date::mdays(int mon)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;
		int d = days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
		return d;
	}

	// Returns the readErrorCode_ value
	int Date::errCode()const {
		return this->readErrorCode_;
	}

	// Returns true if readErrorCode_ is not equal to zero
	bool Date::bad()const {
		return (this->readErrorCode_ != 0 ? true : false);
	}

	// istream  and ostream read and write methods
	std::istream& Date::read(std::istream& istr) {
		int yy = 0, mm = 0, dd = 0;
		char dummy = '0';

		// read input
		istr >> yy >> dummy >> mm >> dummy >> dd;
		if (istr.fail()) {
			// enhanced: add clear and ignor function
			cin.clear();
			cin.ignore();
			this->readErrorCode_ = CIN_FAILED;			
		}
		else { // Enhanced: create a temp Date object to hold the input
			   // set input data as instance variables of temp Date object
			Date temp(yy, mm, dd);
			*this = temp;
			if (year_ < MIN_YEAR || year_ > MAX_YEAR) {
				this->readErrorCode_ = YEAR_ERROR;
			}
			else {
				if (mon_ < 1 || mon_ >12) {
					this->readErrorCode_ = MON_ERROR;
				}
				else {
					if (day_ < 0 || day_ > mdays(mm)) {
						this->readErrorCode_ = DAY_ERROR;
					}
					else {
						readErrorCode_ = NO_ERROR;
						// enhanced assign temp to current object
						*this = temp;
					}
				}
			}
		}
		return istr;
	}


	std::ostream& Date::write(std::ostream& ostr)const {
		// Enhanced: using iomanip.h
		ostr << year_ << "/" << setfill('0')
			<< setw(2) << mon_ << "/"
			<< setw(2) << day_;
		return ostr;
	}

	// data enter
	std::istream& operator>>(std::istream& is, Date& d) {
		return d.read(is);
	}

	// display function
	std::ostream& operator<<(std::ostream& os, const Date& d) {
		d.write(os);
		return os;
	}
}