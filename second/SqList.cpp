// File: SqList.cpp
// Project: CMSC 341 Project 2, Fall 2017
// Author: Andrew Le
// Date: 10/10/2017
// Email: ale16@umbc.edu
// This file contains the content of SqList.cpp
// 


#include <iostream>
#include <list>
#include <cmath>
#include "SqList.h"

using namespace std ;

SqList::SqList() 
{
	int size = 0;
}
// copy constructor
SqList::SqList(const SqList& other) 
{
	size = other.size;
	L = other.L;
}

const SqList& SqList::operator=(const SqList& rhs) 
{
	if(&rhs != this)
	{
		size = rhs.size;
		list< list<Int341> > ::iterator it = L.begin(); 
		L = rhs.L;
	}
	return *this;
}

// destructor
SqList::~SqList() 
{
	
}

//check to see if the list is okay
void SqList::consolidate() 
{	
	//create an iterator getlist for each inner list
	list< list<Int341> > ::iterator getlist = L.begin() ;
	//create an iterator getpos for each position in the inner list
	list<Int341>  ::iterator getpos = (*getlist).begin();
	//dont_cont_toomuch will be the size of the inner list
	int dont_count_toomuch = 0;
	// iterates the outer list 
	for(getlist ; getlist != L.end() ; ++getlist)
	{
		//check if list is empty, if so delete the list 
		if(getlist->empty() && size != 0)
		{
			getlist = L.erase(getlist);
			--getlist;
		}


		//too big, split	
		else
		{
			dont_count_toomuch = getlist->size();
			if(dont_count_toomuch  > (sqrt(size) * 2))
			{
				//create an interator that points behind the list
				list< list <Int341> > ::iterator new_list = getlist;
				getpos = getlist->begin();
				L.insert(getlist, list <Int341> ());
				--new_list;		

				//create an iterator which points to the position at approximately half of the lest
				advance(getpos, dont_count_toomuch / 2);
				
				//set temp, an iterator, to the end of the list to be passed in the splice function later 
				list<Int341>  ::iterator temp = getlist->begin();
				//splice from half of the list, rounded up, to the beginning, into a new list.. this is so i dont have to worry about changing the pointer
				new_list->splice(new_list->begin(), *getlist, temp, getpos);

			}
			
			if(dont_count_toomuch  < (sqrt(size) / 2) && (dont_count_toomuch > 0))
			{
				//create a variable to hold the size
				int dont_count_toomuch = size;

				//make get list hold previous value, temp right hold current
				list< list <Int341> > ::iterator temp_right = getlist;
				temp_right = getlist;
				++temp_right;
				//make sure list isnt empty
				if(temp_right != L.end() && (dont_count_toomuch > 0) ) 
				{

					dont_count_toomuch = temp_right->size();			
				}
				if( (dont_count_toomuch) < (sqrt(size) / 2) && (dont_count_toomuch > 0))
				
				{ 
					temp_right->splice(temp_right->begin(), *getlist);
				}
				
			}	
		}	 
	} 
}

//function to add to beginning
void SqList::addFirst (const Int341& x) 
{
	//if there are no lists, add a list
	if(L.empty())
		{
			list<Int341> first_list;
			L.push_back(first_list);
			size = 0;
		}
	list<Int341> *pointer = &(L.front());
	pointer->push_front(x);
	++size;

	consolidate();
}
//function to add to end
void SqList::addLast (const Int341& x) 
{
	//if there are no lists, add a list
	if(L.empty())
		{
			list<Int341> first_list;
			L.push_back(first_list);
			size = 0;
		}

	list<Int341> *pointer = &(L.back());
	pointer->push_back(x);

	++size;
	consolidate();
}

//remove the first element in the square list
Int341 SqList::removeFirst ()
{
	if(L.empty())
		throw "list doesn't exist";
	list< list<Int341> > ::iterator first = L.begin() ;
	Int341 temp; 
	temp = first->front() ; 

	// list<Int341> *pointer = &(L.front());
	first->pop_front();

	--size;

	consolidate();

	return temp ; 
}
//remove the laast element in the square list
Int341 SqList::removeLast ()
{
	if(L.empty())
		throw "list doesn't exist";

	list< list<Int341> > ::iterator last = L.end() ;
	Int341 temp; 
	temp = last->back() ; 

	// list<Int341> *pointer = &(L.back());
	last->pop_back();
	--size;
	consolidate();

	return temp ; 
}

//
void SqList::add(int pos, const Int341& data) 
{
	//use an iterator for outer list
	list< list<Int341> > ::iterator getlist = L.begin() ;
	//iterator points to the values inside inner list
	list<Int341>  ::iterator getpos = getlist->begin();

	for(getlist ; getlist != L.end() ; ++getlist)
	{
		int dont_count_toomuch = getlist->size();
	
		//subtract value from size to find the index
		if(pos - dont_count_toomuch >= 0 )
		{
			pos -= dont_count_toomuch; 
 			getpos = (*getlist).begin();
 		}
 		//whenthe value can be an actual index, insert there
 		else if (dont_count_toomuch > pos)
 		{
 			getpos = (*getlist).begin();
 			advance(getpos, pos);
			getlist->insert(getpos, data);
			++size;
			consolidate();
			return;
 		}
	} 
}

//
Int341 SqList::remove(int pos) 
{
	//use an iterator for outer list
	list< list<Int341> > ::iterator getlist = L.begin() ;
	//iterator points to the values inside inner list
	list<Int341>  ::iterator getpos = (*getlist).begin();
	//holds the value of the removed item
	int hold = 0;

	//iterate through outer list
	for(getlist ; getlist != L.end() ; ++getlist)
	{
		//get size of the inner list
		int dont_count_toomuch = getlist->size();
		//change position value to find the correct index
		if(pos - dont_count_toomuch >= 0 )
		{
			pos -= dont_count_toomuch; 
 			getpos = (*getlist).begin();
 		}
 		//when the correct index is found, work it
 		else if (dont_count_toomuch > pos)
 		{
 			getpos = (*getlist).begin();
 			advance(getpos, pos);
			hold = getpos->m_data;
			getlist->erase(getpos);
			--size;
			consolidate();
			return hold;

 		}
	} 

}


int SqList::indexOf(const Int341& data) 
{
	list< list<Int341> > ::iterator getlist = L.begin() ;
	//position is the actual position of the item being searched for, assuming it exists
	int pos = 0;
	for(getlist ; getlist != L.end() ; ++getlist)
	{
		list<Int341>  ::iterator getpos = (*getlist).begin();
		for(getpos ; getpos != getlist->end() ; ++getpos)
		{
			if(getpos->m_data == data.m_data)			
			{
				return pos;
 			}
			++pos;
 		}
	} 
	return (-1);
}


int SqList::numItems() 
{
	return (size) ;
}

Int341& SqList::operator[](int pos) 
{	
	//intialize iterators.. 
	list< list<Int341> > ::iterator getlist = L.begin() ;
	list<Int341>  ::iterator getpos = (*getlist).begin();

	for(getlist ; getlist != L.end() ; ++getlist)
	{
		int dont_count_toomuch = getlist->size();
		//change position to until correct index
		if(pos - dont_count_toomuch >= 0 )
		{
			pos -= dont_count_toomuch; 
 			getpos = (*getlist).begin();
 		}
 		//when correct index, ggogoo
 		else if (dont_count_toomuch > pos)
 		{
 			getpos = (*getlist).begin();
 			advance(getpos, pos);
			return (*getpos);

 		}
	} 
}


// debugging function, prints out contents of data structure
void SqList::dump() 
{
	list< list<Int341> > ::iterator getlist = L.begin() ;
	list<Int341>  ::iterator getpos = (*getlist).begin();
	
	int listnum = 0;
	int dont_count_toomuch = 0;

	cout << "num of items = " << size << endl;
	cout << "-------------------------------" << endl;

	for(getlist ; getlist != L.end() ; ++getlist)
	{
		dont_count_toomuch = getlist->size();
		cout << listnum << " (" << dont_count_toomuch << ") : ";

			for(getpos = getlist->begin(); getpos != getlist->end() ; ++getpos)
			{
				cout << getpos->m_data << " ";
			}
			cout << endl;
			++listnum;

	}

}
