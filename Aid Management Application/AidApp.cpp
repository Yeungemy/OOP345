/**********************************************************************
OOP244 Milestone 6: Compiling modular source code
File: AidApp.cpp
Date: Jul 28, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include <iomanip>
#include "AmaPerishable.h"
#include "AidApp.h"
#include "Date.h"
using namespace std;

namespace sict {
	// The constructor receives a constant char string called filename
	AidApp::AidApp(const char* filename) {
		int i;

		// copies filename to filename_ member variable
		if (filename != nullptr) {
			strncpy(filename_, filename, 255);
			filename_[255] = 0;

			// initialize all product member point to null
			for (i = 0; i < MAX_NO_RECS; i++) {
				product_[i] = nullptr;
			}

			noOfProducts_ = 0;
			// call loadRecs function to load data from CSV file
			loadRecs();
		}
	}

	// distructor
	AidApp::~AidApp() {		
		int i = 0;

		// deallocate all product pointer;
		for (i = 0; i < noOfProducts_; i++) {
			delete product_[i];
		}
	}

	// pause the screen
	void AidApp::pause()const {
		cout << endl;
		cout << "Press Enter to continue..." << endl;
		cin.ignore(2000, '\n');
	}

	// menu() displays the memu for user to select an option
	int AidApp::menu() {
		int option = 1;

		cout << "Disaster Aid Supply Management Program" << endl
			<< "1- List products" << endl
			<< "2- Display product" << endl
			<< "3- Add non-perishable product" << endl
			<< "4- Add perishable product" << endl
			<< "5- Add to quantity of purchased products" << endl
			<< "0- Exit program" << endl
			<< "> ";
		cin >> option;

		// always validate user's input, otherwise encounter a fatal crash
		if (cin.fail()) {
			cin.clear();
			cin.ignore(2000, '\n');
			option = -1;
		}
		else {
			option = (option < 0 || option > 5) ? -1 : option;
		}
		return option;
	}

	// opens the data file for reading
	void AidApp::loadRecs() {
		char a = 0;
		// Set readIndex to zero
		int readIndex = 0;

		// opens the data file for reading
		datafile_.open(filename_, ios::in);
		if (datafile_.is_open()) {
			// until reading fails loop
			while (readIndex < MAX_NO_RECS && !datafile_.get(a).fail()) {
				// ignore one comma
				datafile_.ignore( );
				// dyallocate memory
				delete product_[readIndex];
				if (a == 'P') {
					AmaPerishable* item = new AmaPerishable;
					item->load(datafile_);
					product_[readIndex++] = item;
					// release item pointer
					item = nullptr;
					// ignore one comma before the date
					datafile_.ignore();
				}
				else if (a == 'N') {
					AmaProduct* item = new AmaProduct;
					item->load(datafile_);
					// release item pointer
					product_[readIndex++] = item;	
					item = nullptr;
				}				
				noOfProducts_ = readIndex;
			}
		}
		else {
			datafile_.clear();
			datafile_.close();
			datafile_.open(filename_, ios::out);			
		}
		// close file
		datafile_.close();
	}

	// open the data file for writing
	void AidApp::saveRecs() {
		// Opens the data file for writing
		datafile_.open(filename_, ios::out);
		//  Loops through the product_ array up to noOfProducts_
		for (int i = 0; i < noOfProducts_; i++) {
			// stores them in the datafile
			product_[i]->store(datafile_, true);
		}
		datafile_.close();
	}

	// display the list of products
	void AidApp::listProducts()const {
		int i, j = 0;
		double totalCost = 0.0;

		cout << " Row |" << " SKU    |" << " Product Name       |" << " Cost  |"
			<< " QTY|" << " Unit     |" << "Need|" << " Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------"
			<< endl;
		// display products one by one
		for (i = 0; i < noOfProducts_; i++) {
			cout << setw(4) << setfill(' ') << right << i + 1 << " | ";
			product_[i]->write(cout, true);
			j++;
			cout << endl;
			// call operator += to get the total cost of the product on hand
			totalCost += *product_[i];
			// when the number of printed items reaches 10,
			// pause and continue unti enter hit
			if (j == 10) {
				j = 0;
				pause();
			}
		}
		// pring the total cost
		cout << "---------------------------------------------------------------------------"
			<< endl
			<< "Total cost of support: $" << fixed << setprecision(2)
			<< totalCost << endl;
		pause();
	}

	// locate a item by sku
	int AidApp::SearchProducts(const char* sku)const {
		int index = -1;
		bool found = false;

		for (int i = 0; i < noOfProducts_ && !found; i++) {
			// call operater= from Product.cpp
			if(*product_[i] == sku) {
				index = i;
				found = true;
			}
		}
		return index;
	}

	// update the product array
	void AidApp::addQty(const char* sku) {
		// hold qty actually purchased
		int n = 0;
		// hold qty to be returned if buy in exceed item needed
		int r = 0;
		// hold the index of the item needed to be updated
		int index = SearchProducts(sku);
		// qty asked to buy in
		int bal = (product_[index]->qtyNeeded() - product_[index]->quantity());		

		if (index != -1) {
			product_[index]->write(cout, false);
			cout << endl << "Please enter the number of purchased items: ";
			cin >> n;
			cout << endl;

			while (cin.fail()) {
				cin.clear();
				cin.ignore(2000, '/n');
				cout << "Invalid quantity value! " << endl;
				cout << endl << "Please enter the number of purchased items: ";
				cin >> n;
			}
			if (n <= bal) {
				*product_[index] += n;
			}
			else {
				r = n - bal;
				*product_[index] += +bal;
				cout << "Too many items; only " << bal << " is needed, please return the extra "
					<< r << " items." << endl;
			}
			//  all records will be saved back to the file
			saveRecs();
			cout << "Updated!" << endl;
		}
		else {
			cout << "Not found!" << endl;
		}
	}

	// add a member to product array;
	void AidApp::addProduct(bool isPerishable) {
		Product* temp;
		isPerishable ? temp = new AmaPerishable : temp = new AmaProduct;

		// call overload operator >>
		cin >> *temp;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			// call overload operator <<
			cout << *temp;			
		}
		else {
			// call copy assignment
			product_[noOfProducts_++] = temp;
			temp = nullptr;
			saveRecs();
			cout << endl << "Product added" << endl;
		}
	}

	// display the menu, act as the user's selection
	int AidApp::run() {
		int choice;
		int index = 3;
		char SKU[MAX_SKU_LEN + 1] = "";

		do {
			choice = menu();
			cin.ignore(2000, '\n');
			
			switch (choice) {
			case 1:
				cout << endl;
				listProducts();
				break;
			case 2:
				cout << endl << "Please enter the SKU: ";
				cin >> SKU;
				cout << endl;
				cin.ignore(2000, '\n');
				index = SearchProducts(SKU);
				if (index == -1) {
					cout << "Not found!" << endl;
				}
				else {
					product_[index]->write(cout, false);
					pause();
				}
				break;
			case 3:
				cout << endl;
				addProduct(false);
				cout << endl;
				break;
			case 4:
				cout << endl;
				addProduct(true);
				cout << endl;
				break;
			case 5:
				cout << endl;
				cout << "Please enter the SKU: ";
				cin >> SKU;
				cout << endl;
				addQty(SKU);
				cout << endl;
				break;
			case 0:
				cout << endl << "Goodbye!!" << endl;
				break;
			default:
				cout << endl;
				cout << "===Invalid Selection, try again.===";
				pause();
				break;
			}
		} while (choice != 0);
		return 0;
	}
}