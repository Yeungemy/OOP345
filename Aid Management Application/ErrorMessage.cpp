/**********************************************************************
OOP244 Milestone 2: Compiling modular source code
File: ErrorMessage.cpp
Date: Jul 6, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "ErrorMessage.h"

namespace sict {
	// Empty safety constructor
	ErrorMessage::ErrorMessage() {
		message_ = nullptr;
	}

	// copy constructor
	ErrorMessage::ErrorMessage(const char* errorMessage) {
		// Enhance: delete "message_ = nullptr"
		// call the message set function
		message(errorMessage);
	}

	// A  assignment operator overload
	ErrorMessage& ErrorMessage::operator=(const char* errorMessage) {
		// Enhance: delete clear() function call
		message(errorMessage);
		return *this;
	}

	// De-allocates the memory pointed by message_ and then sets message_ to nullptr
	void ErrorMessage::clear() {
		delete[] message_;
		message_ = nullptr;
	}

	// Returns true if message_  is nullptr
	bool ErrorMessage::isClear()const {
		return message() == nullptr;
	}

	// Sets the message_ of the errorMessage object to a new value
	void ErrorMessage::message(const char* value) {
		clear();
		int size = strlen(value);
		// enhance: change call empty safty constructor
		message_ = new char[size + 1];
		if (value != nullptr && value[0] != '\0') {
			strncpy(message_, value, size);
			message_[size] = '\0';
		}
	}

	// returns the address kept in message_
	const char* ErrorMessage::message()const {
		return message_;
	}

	// Overload operator<< so the ErrorMessage can be printed using cout
	std::ostream& operator<<(std::ostream& os, const ErrorMessage& err) {
		if (!err.isClear()) {
			os << err.message();
		}		
		return os;
	}
}