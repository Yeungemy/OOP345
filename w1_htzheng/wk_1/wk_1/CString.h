/**********************************************************************
OOP345 Workshop 1: Compiling modular source code
File: CString.h
Date: Sept 12, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#include <iostream>

// a macro against repeated use
#ifndef  CSTRING_H
#define CSTRING_H

// embed the definition of class CSting  in namespace w1
namespace w1 {
	char * strncpy(char *dest, const char *src, size_t n);

	// initialize a global variable to hold the number of characters stored in class CString
	const int MAX = 3;

	class CString {
		// define a constant integer to hold the number of characters of an object			
		char myString_[MAX + 1];
		
		// constructor for safe empty state
	public:
		CString();
		// constructor that receives the address of a C-style null-terminated string  
		CString(char* str);
		// distructor
		~CString();
		// display the string as stored in CString 
		void display(std::ostream& ostr)const;
	};
	// a helper non-friend operator that inserts the stored string into the left ostream operand
	std::ostream& operator<<(std::ostream& os, const CString& str);
}
#endif // ! CSTRING_H