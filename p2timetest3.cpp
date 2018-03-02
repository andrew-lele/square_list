// File: p2timetest3.cpp
//
// UMBC Fall 2017 CMSC 341 Project 2
// 
// Timing runs to show expected O(n^(1.5)) running time.
//

#include <iostream> 
#include "SqList.h"
#include "Int341.h"

using namespace std ;

void SqList::inspector() {

   cout << "\n\n=============================================\n" ;
   cout << "SqList::inspector() report\n" ;
   cout << "=============================================\n" ;

   bool errorFound = false ;

   int n = numItems() ;

   list< list<Int341> >::iterator it ;


   // calculate total number of items in data structure
   //
   int sum = 0 ;
   for (it = L.begin() ; it != L.end() ; it++) {
      sum += it->size() ;
   }


   // report on size()
   //
   if (n == sum) {
      cout << "numItems() correct\n" ;
   } else {
      errorFound = true ;
      cout << "*** numItems() wrong! " << endl 
           << "    numItems() = " << n << endl 
      << "    sum of sizes = " << sum << endl ; 
   }


   // special case if no items
   //
   if (L.size() == 0) {
      cout << "Empty SqList, nothing more to check\n" ; 
      return ;
   }


   // Run down the outer list and check if there are any
   // of these errors: empty list, list too long, adjacent
   // short lists.
   //
   int prevSize, currSize ;
   bool prevIsShort = false ;
   bool currIsShort ;
   
   int index = 0 ;
   
   for(it = L.begin() ; it != L.end() ; it++) {

      currSize =  it->size() ;

      if (currSize == 0) {    // empty?
         errorFound = true ;
         currIsShort = true ;
    cout << "*** Inner list " << index << " empty! " << endl  ;

      } else if ( (currSize-1)*(currSize-1) > 4*n ) {   // too long?
         errorFound = true ;
    cout << "*** Inner list " << index << " too long! " << endl 
         << "    inner list size  = " << currSize << endl 
         << "    sum of sizes = " << n << endl ; 

      } else if ( 4*(currSize+1)*(currSize+1) <= n) {  // too short?
         currIsShort = true ;
    if (prevIsShort) {  // adjacent shorts?
            errorFound = true ;
       cout << "*** Adjacent short inner lists found! " << endl 
       << "    sum of sizes = " << n << endl 
       << "    inner list " << index-1 << " has size  = " << prevSize << endl  
       << "    inner list " << index << " has size  = " << currSize << endl ;
    }
      } else {
         currIsShort = false ;
      }
      prevSize = currSize ;
      prevIsShort = currIsShort ;
      index++ ;
   }

   if (!errorFound) {
      cout << "No errors found!\n" ;
   }

   cout << "=============================================\n" ;
   
}

int main() {
   SqList S ;
   int n = 60000 ;

   Int341::m_debug = false ;

   // add lots of items
   //
   for (int i=0 ; i < 2*n ; i++) {
     S.addLast(Int341(i)) ;
   }
   for (int i=0 ; i < 2*n ;i++) {
     S.addFirst(Int341(i*i)) ;
   }

   // remove half
   //
   Int341 result ;
   for (int i=0 ; i < n ; i++) {
      result = S.removeFirst() ; 
   }
   for (int i=0 ; i < n ; i++) {
      result = S.removeLast() ; 
   }

   //my edits


   SqList T(S) ;
   SqList U ;
   U = T ;


   Int341 answer ;


   for (int i=5 ; i < 700 ; i+=3) {
      // cout << "goes into removing with i = " << i << endl;
      // S.dump();
      answer = S.remove(i) ;
   }

   Int341 stuff(1) ;
   
   int pos = U.indexOf(stuff) ;
   if (pos >= 0) {
      cout << "Found " << stuff.m_data << " in index " << pos << endl ;
   } else {
      cout << "Did not find " << stuff.m_data << endl ;
   }



      stuff = Int341(-1) ;
   pos = U.indexOf(stuff) ;
   if (pos >= 0) {
      cout << "Found " << stuff.m_data << " in index " << pos << endl ;
   } else {
      cout << "Did not find " << stuff.m_data << endl ;
   }

   // U.dump() ;
   Int341::report() ;

   U.inspector() ;
   return 0 ;
}