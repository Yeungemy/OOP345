/**********************************************************************
OOP244 Milestone 5: Compiling modular source code
File: Product.h
Date: Jul 14, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/
#ifndef SICT_PRODUCT_H_
#define SICT_PRODUCT_H_

#include "Streamable.h"
#include "general.h"

namespace sict {
	class Product : public Streamable {
		char sku_[MAX_SKU_LEN + 1];	// holds the SKU (barcode) of the items as a string
		char* name_;				// holds the name of the Product 
		double price_;				// holds the Price of the Product 
		bool taxed_;				// true if this Product is taxed
		int quantity_;				// holds the on hand (current) quantity of the Product
		int qtyNeeded_;				// holds the needed quantity of the Product
	public:
		// default constructor
		Product();
		// Constructor with five parameters
		Product(const char* s, const char* nm, bool t = true,
			double p = 0.00, int q = 0);
		// distructor
		~Product();
		// copy constructor
		Product(const Product& src);
		// assignment operator=
		Product& operator= (const Product& source);
		// set SKU
		void sku(const char* SKU);
		// set price
		void price(double p);
		// set name
		void name(const char* nm);
		// set taxed or not
		void taxed(bool t);
		// set quantity on hand
		void quantity(int qty);
		// set quantity needed
		void qtyNeeded(int qtyAsked);
		// get SKU;
		const char* sku()const;
		//get price
		double price()const;
		// get name
		const char* name()const;
		// get taxed or not
		bool taxed()const;
		// get quantity on hand
		int quantity()const;
		// get quantity asked for
		int qtyNeeded()const;
		// get cost
		double cost()const;
		// check the empty safe state
		bool isEmpty()const;
		// compare two SKU
		bool operator==(const char* tempSku);
		// add quantity purchased to the current
		int operator+=(int qtyPurchased);
		// deduct quantity sold from the current
		int operator-=(int qtySold);
		/*std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);*/
	};
	// get the total cost of the product on hand
	double operator+=(double& lhs, const Product& rhs);
	// operator<<
	std::istream& operator>>(std::istream& is, Product& p);
	// operator>>
	std::ostream& operator<<(std::ostream& os, const Product& p);
}
#endif