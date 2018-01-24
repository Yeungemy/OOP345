/**********************************************************************
OOP244 Milestone 3: Compiling modular source code
File: Product.cpp
Date: Jul 11, 2017
Course section: SAB
Author: Emy Yeung
ID:   026-302-117
email: htzheng@myseneca.ca
**********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>

#include "Product.h"
using namespace std;

namespace sict {
	// default constructor
	Product::Product() {
		sku_[0] = '\0';
		name_ = nullptr;
		price_ = 0.00;
		taxed_ = false;
		quantity_ = 0;
		qtyNeeded_ = 0;
	}

	// Constructor with five parameters
	Product::Product(const char* s, const char* n,
		bool t, double p, int q) {
		quantity(0);
		sku(s);
		name(n);
		taxed(t);
		price(p);
		qtyNeeded(q);
	}

	// distructor
	Product::~Product() {

	}

	// copy constructor
	Product::Product(const Product& src) {
		name_ = nullptr;
		*this = src;
	}

	// assignment operator=
	Product& Product::operator= (const Product& source) {
		if (this != &source) { // self-assignment check
			// shallow copy
			sku(source.sku_);
			price(source.price_);
			quantity(source.quantity_);
			qtyNeeded(source.qtyNeeded_);
			taxed(source.taxed_);
			// resource copy
			name(source.name_);  
		}
		return *this;
	}

	// set SKU
	void Product::sku(const char* s) {
		sku_[0] = '\0';
		if (s != nullptr) {
			int n = sizeof(s) / sizeof(s[0]);
			n = n > MAX_SKU_LEN ? MAX_SKU_LEN : n;
			// enhance: delete for loop 
			strncpy(sku_, s, n);
			sku_[n] = '\0';
		}
	}

	// set name
	void Product::name(const char* nm) {
		if (name_ != nm) {// self-assignment check
			delete[] name_;  // deallocate memory
			name_ = nullptr;
			if (nm != nullptr) {
				int n = strlen(nm);
				// dynamically allocate memory
				name_ = new char[n + 1];
				strncpy(name_, nm, n);
				name_[n] = '\0';
			}
		}		
	}

	// set price
	void Product::price(const double p) {
		// enhance: including 0
		price_ = p > 0.00 ? p : 0.00;
	}

	// set taxed or not
	void Product::taxed(bool t) {
		taxed_ = t;
	}

	// set quantity on hand
	void Product::quantity(const int qty) {
		// enhance: including 0
		quantity_ = qty > 0 ? qty : 0;
	}

	// set quantity needed
	void Product::qtyNeeded(const int qtyAsked) {
		// enhance: including 0
		qtyNeeded_ = qtyAsked > 0 ? qtyAsked : 0;
	}

	// get SKU;
	const char* Product::sku()const {
		return sku_;
	}

	//get price
	double Product::price()const {
		return price_;
	}

	// get name
	const char* Product::name()const {
		return name_;
	}

	// get taxed or not
	bool Product::taxed()const {
		return taxed_;
	}

	// get quantity on hand
	int Product::quantity()const {
		return quantity_;
	}

	// get quantity asked for
	int Product::qtyNeeded()const {
		return qtyNeeded_;
	}

	// get cost
	double Product::cost()const {
		return (taxed()) ? price_ * (1 + TAX) : price_;
	}

	// check the empty safe state
	bool Product::isEmpty()const {
		return sku_[0] == '\0' && name_ == nullptr && price_ == 0 &&
			taxed_ == false && quantity_ == 0 && qtyNeeded_ == 0;
	}

	// compare two SKU
	bool Product::operator==(const char* tempSku) {
		return strcmp(sku_, tempSku) == 0;
	}

	// add quantity to the current
	int Product::operator+=(int q) {
		return quantity_ += q;
	}

	// deduct quantity from the current
	int Product::operator-=(int qty) {
		return quantity_ -= qty;
	}

	// get the total cost of the product on hand
	double operator+=(double& lhs, const Product& rhs) {
		// enhance: calculate total cost of the item		
		return lhs += rhs.quantity() * rhs.cost();
	}

	// operator<<
	istream& operator>>(istream& istr, Product& p) {
		return p.read(istr);
	}

	// operator>>
	ostream& operator<<(ostream& ostr, const Product& p) {
		return p.write(ostr, true);
	}
}