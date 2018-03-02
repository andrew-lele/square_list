// File: Int341.h
// 
// UMBC Fall 2017 CMSC 341 Project 2 
//
// Int341 is basically an int.
// Having it defined as a class allows us to track the number of times
// data items are copied for the SqList data structure for Project 2.
//

#ifndef _SQLIST_H_
#define _SQLIST_H_

#include <iostream>
#include <list>
#include "Int341.h"

using namespace std;


class SqList {

public:
	SqList() ;

	// copy constructor
	SqList(const SqList& other) ;

	const SqList& operator=(const SqList& rhs) ;

	// destructor
	~SqList() ;

	// void consolidate(bool trigger, list< list<Int341> > ::iterator it) ; 

	void consolidate() ; 


	void addFirst (const Int341& x) ; 

	void addLast (const Int341& x) ;

	Int341 removeFirst (); 

	Int341 removeLast ();

	void add(int pos, const Int341& data) ;

	Int341 remove(int pos) ;

	int indexOf(const Int341& data) ;

	int numItems() ; 

	void inspector() ; 

	// overloaded assignment operator
	Int341& operator[](int pos) ;



	// debugging function, prints out contents of data structure
	void dump() ;

private:
	list< list<Int341> > L ;
	int size;
};
#endif