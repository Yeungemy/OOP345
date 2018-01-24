/**********************************************************************
OOP345 Workshop 1: Compiling modular source code
File: main.cpp
Date: Sept 12, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#include <iostream>
#include "CString.h"
#include "process.h"

using namespace std;

int main(int argc, char* argv[]) {
	int flag = 0;
	if (argc == 0) {
		cout << "Insufficient number of arguments (min 1)" << endl;
		flag = 1;
	}
	else if(argc == 1){
		cout << "Command Line : " << argv[0] << endl;
	}
	else {
		cout << "Command Line : ";
		for (int i = 0; i < argc; i++) {
			cout << argv[i] << " ";
		}
		cout << endl << "Maximum number of characters stored : " << w1::MAX << endl;
		for (int i = 1; i < argc; i++) {
				w1::process(argv[i]);					
		}
	}

	return flag;
}