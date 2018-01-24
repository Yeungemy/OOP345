/**********************************************************************
OOP345 Workshop 1: Compiling modular source code
File: process.h
Date: Sept 12, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

// header guards
#ifndef PROCESS_H
#define PROCESS_H

#include "CString.h"

namespace w1 {
	/* function receives the address of a C-style null-terminated string
	   and uses an object of your CString class to store a possibly 
	   truncated version of the string
	*/ 
	void process(char* s);
}
#endif // !PROCESS_H