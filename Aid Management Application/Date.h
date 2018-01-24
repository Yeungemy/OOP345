/**********************************************************************
OOP244 Milestone 5: Compiling modular source code
File: Date.h
Date: Jul 6, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>

namespace sict {
#define NO_ERROR		0	// No error the date is valid 
#define CIN_FAILED		1	// istream failed when entering information 
#define YEAR_ERROR		2	// Year value is invalid
#define MON_ERROR		3	// Month value is invalid
#define DAY_ERROR		4	// Day value is invalid 

	class Date {
		//  Holds the year between MIN_YEAR and MAX_YEAR, defined in “general.h”
		int year_;
		//  Month of the year, between 1 to 12 
		int mon_;
		//  Day of the month, note that in a leap year February is 29 days
		int day_;
		//  Holds an error code with which to verify the validation of the date value 
		int readErrorCode_;
		// This function returns a unique integer number based on the date
		int value()const;
		// Sets the readErrorCode_ member-variable to one of the values mentioned above
		void errCode(int errorCode);
	public:
		// Default constructor
		Date();
		// Constructor with three arguments
		Date(int y, int m, int d);
		// Destructor
		~Date();
		// Comparison Logical operator overloads: 
		bool operator==(const Date& D)const;
		bool operator!=(const Date& D)const;
		bool operator<(const Date& D)const;
		bool operator>(const Date& D)const;
		bool operator<=(const Date& D)const;
		bool operator>=(const Date& D)const;
		// Returns the number of days in a month
		int mdays(int mon)const;
		// Returns the readErrorCode_ value
		int errCode()const;
		// Returns true if readErrorCode_ is not equal to zero
		bool bad()const;
		// istream  and ostream read and write methods
		std::istream& read(std::istream& is);
		std::ostream& write(std::ostream&)const;
	};
	// operator<< and >> overload prototypes for cout and cin
	std::istream& operator>>(std::istream& is, Date& d);
	std::ostream& operator<<(std::ostream& os, const Date& d);
}
#endif