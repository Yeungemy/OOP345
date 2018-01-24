/**********************************************************************
OOP244 Milestone 5: Compiling modular source code
File: ErrorMessage.cpp
Date: Jul 7, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#ifndef SICT_ERRORMESSAGE_H__
#define SICT_ERRORMESSAGE_H__
#include <iostream>

namespace sict {
	class ErrorMessage {
		char* message_;

	public:
		// Empty safety constructor
		ErrorMessage();
		// copy constructor
		ErrorMessage(const char* errorMessage);
		// A deleted copy constructor to prevent an ErrorMessage object to be copied
		ErrorMessage(const ErrorMessage& em) = delete;
		// De-allocates the memory pointed by message_. 
		virtual ~ErrorMessage() { delete[] message_; }
		// A deleted assignment operator overload
		ErrorMessage& operator=(const ErrorMessage& em) = delete;
		// A  assignment operator overload
		ErrorMessage& operator=(const char* errorMessage);
		// De-allocates the memory pointed by message_ and then sets message_ to nullptr
		void clear();
		// Returns true if message_  is nullptr
		bool isClear()const;
		// Sets the message_ of the errorMessage object to a new value
		void message(const char* value);
		// returns the address kept in message_
		const char* message()const;
	};
	// Overload operator<< so the ErrorMessage can be printed using cout
	std::ostream& operator<<(std::ostream& os, const ErrorMessage& err);
}
#endif