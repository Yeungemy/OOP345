/**********************************************************************
OOP244 Milestone 6: Compiling modular source code
File: AidApp.h
Date: Jul 29, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#ifndef SICT_AIDAPP_H__
#define SICT_AIDAPP_H__
#include "AmaPerishable.h"
using namespace std;

namespace sict {
	class AidApp {
		// holds the name of the text file used to store the production information
		char filename_[256];
		// An array of Product pointers, MAX_NO_RECS LONG
		Product* product_[MAX_NO_RECS];
		// An fstream instance used to create and access a file
		fstream datafile_;
		// Number of products pointed to the product_array
		int noOfProducts_;
		// copy and assignment prevenstion
		AidApp(const AidApp& source) = delete;
		AidApp& operator= (const AidApp& source) = delete;
	public:
		// The constructor receives a constant char string called filename
		AidApp(const char* filename);
		// distructor
		~AidApp();
		// menu() displays the memu for user to select an option
		// pause
		void pause()const;
		int menu();
		// read data from a data file
		void loadRecs();
		// open the data file for writing
		void saveRecs();
		// display the list of products
		void listProducts()const;
		// locate a item by sku
		int SearchProducts(const char* sku)const;
		// update the product array
		void addQty(const char* sku);
		// add a member to product array;
		void addProduct(bool isPerishable);
		// display the menu, act as the user's selection
		int run();
	};
}

#endif