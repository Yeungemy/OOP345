/**********************************************************************
OOP345 Workshop 1: Compiling modular source code
File: process.cpp
Date: Sept 12, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#include <iostream>
#include "process.h"

using namespace std;

namespace w1 {
	/* function receives the address of a C-style null-terminated string
	and uses an object of your CString class to store a possibly
	truncated version of the string
	*/
	void process(char* s){
		// construct a CString object from the string received
		w1::CString temp(s);	
		// insert the CString object into the std::cout object and terminate with a newline
		cout << temp << endl;
	}
}
