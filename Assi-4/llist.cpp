/*
  Title : Linked List Implementation

  Purpose : To implement a Linked List using classes

  Description :
  -> The program has an IntList class, which is a linked list of integers
  -> There is also an Iterator class which is used to view the elements
  but not modify them

  Author : S. Pradeep Kumar
  Date : 08 - 10 - 2010

  Notes :
  * Use friend to allow IntList access to private variables of Iterator
  Aim of the program : 
  * Use Iterators to enable access to the nodes of the linked list without allowing them to MODIFY the list
  * This means that the pointers to the list must be private; otherwise, you might have two lists sharing nodes, etc.
  Note : 
  * A member function of a class can access all the private variables of all the objects of that class passed to it, not just the object which called it
  * operator ++ turns into prefix operator if you pass an integer parameter
  * Consider storing - 
  - pointer to the tail of the list
  - size in the list

  Errors encountered so far :
  * First segfault was due to the destructor being called at the end of main, which led me to discover that empty () was working wrongly... Would never have guessed it if not for GDB. GDB Rocks! (at least for segfaults)
  * Prefix operator was implemented in terms of the postfix operator (or so I thought). Went into an infinite loop as it called itself
  * Had to make operator* const; otherwise, calling *iter on a const iterator given would lead to the "quantifier being discarded"
  * iter != list.begin() -> led to a problem because operator!= took an Iterator & as argument and, somehow, it was checking for != as an operator for IntList::begin(); FIX : Make operator* (Iterator ) without the &
  * Same for operator==; Removed the &
  * My copy constructor was written in terms of operator=, where I was calling empty(), clear(), etc. on the this object. But, since I had never initialized head = NULL, empty() was returning false. Big Error.
  * operator* on Iterator gave segfault when called on an empty Iterator. So, to check that, we use (iter == end())
  * Always check if you are calling * or -> on a NULL pointer
  */


#include <iostream>
#include <fstream>
#include <string>
#include "llist.h"

using namespace std;
	  
/*
 * Class to access the elements of the list. We need a separate class
 * for this as we want to keep the pointers to the nodes private.
 */
IntList::IntList()		//  Constructor 
{
     head = NULL;
     tail = NULL;
}

IntList::IntList(const IntList & llist) //  Copy constructor
{
     head = NULL;
     tail = NULL;
     *this = llist;
}
     
     
bool IntList::empty() const	//  Function to check if the list is empty 
{
     if (begin() == end())
	  return true;
     else
	  return false;
}
     
unsigned int IntList::size() const //  Function to return the number of elements 
{
     int n;
     Iterator iter;
     for (n=0, iter = begin(); iter != end(); n++, ++iter)
	  ;
     return n;
}
     
     
void IntList::push_front(int value)
{
     Node * temp = new Node;
     temp -> val = value;
     temp -> next = head;
     temp -> prev = NULL;
     if (head)
	  head -> prev = temp;
     else{			// First node ever
	  tail = temp;
     }
     head = temp;
}
     
     
	       
int IntList::pop_front()
{
     int value;
     if (empty ())
	  return 0;
	       
     Node * curr = head;
     if (curr -> next == NULL){
	  value = curr -> val;
	  delete curr;
		    
	  head = NULL;
	  tail = NULL;
	  // cout << "Pop_front : " << value << endl;
	  return value;
     }
     else{
	  head = curr -> next;
	  head -> prev = NULL;
	  if (head -> next == NULL)
	       tail = head;
	  value = curr -> val;
	  delete curr;
	  // cout << "Pop_front : " << value << endl;
	  return value;
     }
}
     
void IntList::clear()		//  Function to delete all elements from the list 
{
     while (!empty ()){
	  pop_back ();
     }
}


void IntList::print ()
{
     cout<<endl;
     cout << "List : ";
    IntList::Iterator iter;
     if (empty())
	  cout<< "Empty!";
     else
	  for (iter = begin(); iter != end(); ++iter)
	       cout<<*iter<<" ";
     cout<<endl;
}
     
	       
IntList::~IntList()		//  Destructor to delete elements 
{
     clear();
}

int main(){

     // Testing code :
     IntList list;
     
     list.push_back (10);
     list.push_back (20);
     list.push_front (100);
     list.push_front (300);
     list.push_front (400);
     list.push_front (500);
     list.push_front (200);
     list.print();
//      IntList::Iterator iter = list.begin();
//      IntList::Iterator iter2 (iter);
//      iter2.print();
     
//      for (iter = list.begin(); iter != list.end(); ++iter)
// 	  iter.print();

//      for (iter = list.rev_begin(); iter != list.rev_end(); --iter)
// 	  iter.print();
//      --iter;
//      iter.print ();
     
//      list.print ();
//      IntList list2 = list;
//      IntList list3 (list);
//      list.print ();
//      list2.print ();
//      list3.print ();
     
//      cout << "Empty : " << list.empty() << endl;
//      cout << "Size : " << list.size() << endl;
     
//      cout << "Empty : " << list2.empty() << endl;
//      cout << "Size : " << list2.size() << endl;

//      cout << "Empty : " << list3.empty() << endl;
//      cout << "Size : " << list3.size() << endl;

//      while (!list3.empty()){
// 	  list3.print ();
// 	  cout << list3.pop_front() << endl;
//      }
     

//      list2.clear();
//      cout << list2.size();
     
//      iter = list.begin();
//      list.print ();
//      iter.print ();
//      list.insert(++iter, 600);
//      iter.print ();
//      list.print ();
//      list.remove(iter);
//      iter.print ();
//      list.print();
//      iter = list3.begin();
//      list3.insert(iter, 500);
//      list3.insert (iter, 1000);
//      iter = list3.begin();
     
//      list3.remove(iter);
     
//      list3.print();
     return 0;
}
