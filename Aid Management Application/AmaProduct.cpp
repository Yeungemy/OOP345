/**********************************************************************
OOP244 Milestone 4: Compiling modular source code
File: AmaProduct.cpp
Date: Jul 18, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>

#include "AmaProduct.h"
using namespace std;

namespace sict {
	// constructor receives the value for the filetag_
	AmaProduct::AmaProduct(char fileTag) {
		fileTag_ = fileTag;
		unit_[0] = '\0';
	}

	// destructor
	AmaProduct::~AmaProduct() {

	}

	// returns a constant pointer to the unit_ member variable
	const char* AmaProduct::unit()const {
		return unit_;
	}

	// Copies the incoming value string into the unit_ string
	// Make sure copying does not pass the size of the unit_ array
	void AmaProduct::unit(const char* value) {
		if (this->unit_ != value) {
			if (value != nullptr) {
				int len = strlen(value);
				len = (len + 1) > 11 ? 10 : len;
				strncpy(unit_, value, len);
				unit_[len] = '\0';
			}
		}
	}

	// ouput the product to the compiler
	std::fstream& AmaProduct::store(std::fstream& file, bool addNewLine)const {
		if (!isEmpty()) { // enhanced: add empty check
			file << fileTag_ << "," << sku() << "," << name() << "," << price() << ","
				<< taxed() << "," << quantity() << "," << unit() << "," << qtyNeeded();
			if (addNewLine == true) {
				file << endl;
			}
		}
		return file;
	}

	// read data member from the buffer
	fstream& AmaProduct::load(fstream& file){
		//file.open("amaPrd.txt", ios::in);
		char buf[2000];
		double dbuf;
		int ibuf;

		file.getline(buf, MAX_SKU_LEN + 1, ',');
		sku(buf);
		file.getline(buf, 2000, ',');
		name(buf);
		file >> dbuf;
		price(dbuf);
		file.ignore();
		file >> ibuf;
		taxed(bool(ibuf));
		file.ignore();
		file >> ibuf;
		quantity(ibuf);
		file.ignore();
		file.getline(buf, 10, ',');
		unit(buf);
		file >> ibuf;
		qtyNeeded(ibuf);
		file.ignore();
		return file;
	}

	// prints the prodcut in the format of form or linear
	std::ostream& AmaProduct::write(std::ostream& ostr, bool linear)const {
		if (!(err_.isClear())) {
			ostr << err_.message() << endl;
		}
		else {
			// Enchance: add Empty check
			if (!isEmpty()) {
				switch (linear) {
				case true:
					ostr << setw(7) << setfill(' ') << left << sku() << "|"
						<< setw(20) << setfill(' ') << left << name() << "|"
						<< setw(7) << setfill(' ') << fixed << setprecision(2) << right << cost() << "|"
						<< setw(4) << setfill(' ') << right << quantity() << "|"
						<< setw(10) << setfill(' ') << left << unit() << "|"
						<< setw(4) << setfill(' ') << right << qtyNeeded() << "|";
					break;
				case false:
					ostr << "Sku: " << sku() << endl
						<< "Name: " << name() << endl
						<< "Price: " << price() << endl;
					taxed() ? ostr << "Price after tax: " << cost() << endl :
						ostr << "Price after tax: " << "N/A" << endl;
					ostr << "Quantity On Hand: " << quantity() << " " << unit() << endl
						<< "Quantity Needed: " << qtyNeeded() << endl;
					break;
				}
			}
		}
		return ostr;
	}

	// Receives the values using istream
	std::istream& AmaProduct::read(std::istream& istr) {
		char c[2000] = { '\0' };
		int q = 0;
		double x = 0.0;
		bool t = true;
		
		std::cout << "Sku: ";
		// enhanced: MAX_SKU_LEN rather than MAX_SKU_LEN + 1
		istr.getline(c, MAX_SKU_LEN, '\n');
		sku(c);
		std::cout << "Name: ";
		istr.getline(c, 20, '\n');
		name(c);
		std::cout << "Unit: ";
		// enhanced: change 11 to 10
		istr.getline(c, 10, '\n');
		unit(c);
		std::cout << "Taxed? (y/n): ";
		istr>>c;
		// Check the character entered for state of tax
		switch (c[0]) {
		case 'y':
		case 'Y':
			t = true;
			break;
		case 'N':
		case 'n':
			t = false;
			break;
		default:
			istr.setstate(ios::failbit);
			err_.message("Only (Y)es or (N)o are acceptable");
			break;
		}
			if ((err_.isClear())) {
				taxed(t);
				std::cout << "Price: ";
				istr >> x;
				if (istr.fail()) {
					istr.setstate(ios::failbit);
					err_.message("Invalid Price Entry");
				}
				else {
					price(x);
					std::cout << "Quantity On hand: ";
					istr >> q;
					if (istr.fail()) {
						istr.setstate(ios::failbit);
						err_.message("Invalid Quantity Entry");
					}
					else {
						quantity(q);
						std::cout << "Quantity Needed: ";
						istr >> q;
						if (istr.fail()) {
							istr.setstate(ios::failbit);
							err_.message("Invalid Quantity Needed Entry");
						}
						else {
							qtyNeeded(q);
						}
					}
				}
				// Enhanced: delete not clear() check
			}		
		return istr;
	}
}