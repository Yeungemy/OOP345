/**********************************************************************
OOP345 Workshop 1: Compiling modular source code
File: CString.cpp
Date: Sept 12, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "CString.h"

using namespace std;

// embed the implementatio of class CSting  in namespace w1
namespace w1 {
	char * strncpy(char *dest, const char *src, size_t n) {
		size_t i;
		for (i = 0; i<n && src[i] != '\0'; i++) {
			dest[i] = src[i];
		}
		for (; i<n; i++) {
			dest[i] = '\0';
		}
		return dest;
	}

	// constructor for safe empty state
	CString::CString() {
		myString_[0] = '\0';
	}

	// constructor that receives the address of a C-style null-terminated string
	CString::CString(char* str) {
		// Check for receipt of the null address
		if (str != nullptr) {
			// stores the first MAX characters of the string			
			strncpy(myString_, str, MAX);
			myString_[MAX] = '\0';
		}
		else {
			// Store an empty string in that case
			myString_[0] = '\0';
		}			
	}

	// distructor
	CString::~CString() {

	}

	// display the string as stored in CString
	void CString::display(std::ostream& ostr)const {
		ostr << myString_;
	}

	// a helper non-friend operator that inserts the stored string into the left ostream operand
	std::ostream& operator<<(std::ostream& os, const CString& str) {
		static int count = 0;
		os << count << ": ";
		count++;
		str.display(os);		
		return os;
	}	
}