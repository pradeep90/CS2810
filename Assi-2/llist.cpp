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


IntList::Iterator::Iterator()	//  Constructor 
{
     curr_node = NULL;
}

IntList::Iterator::Iterator (const IntList::Iterator & orig_iter) //  Copy constructor 
{
     *this = orig_iter;
}

IntList::Iterator IntList::Iterator::operator=(const IntList::Iterator &orig_iter) //  Assignment operator 
{
     curr_node =  orig_iter.curr_node;
}

IntList::Iterator IntList::Iterator::operator++() //  Prefix and postfix operators, to move forward in the listR
{
     IntList::Iterator * temp = this;

     if(curr_node)
	  curr_node = curr_node -> next;
     return *temp;
}

// IntList::Iterator IntList::Iterator::operator++(int n)
// {
//      if (curr_node)
// 	  curr_node = curr_node -> next;
//      return *this;
// }
int& IntList::Iterator::operator*() const //  Operators to return elements contained in the list 
{
     // if (curr_node == NULL)
     // 	  return -1;
     return curr_node->val;

}

//int *operator->();

bool IntList::Iterator::operator==(Iterator orig_iter) const //  Operators to compare two iterators 
{
     return (curr_node == orig_iter.curr_node);
}

bool IntList::Iterator::operator!=(Iterator orig_iter) const
{
     return !(*this == orig_iter);
}
void IntList::Iterator::print()
{
     cout<<"Iter : "<<**this<<endl;
}
	  
/* Class to access the elements of the list. We need a separate class
 * for this as we want to keep the pointers to the nodes private.
 */
IntList::IntList()		//  Constructor 
{
     head = NULL;
}
IntList::IntList(const IntList & llist) //  Copy constructor
{
     head = NULL;
     *this = llist;
}
     
IntList & IntList::operator=(const IntList & llist) //  Assignment Operator 
{
     Iterator given_beg_list = llist.begin ();
     Iterator given_end_list = llist.end ();
	       
     clear();

     Iterator iter;
     for(iter = given_beg_list; iter != given_end_list; ++iter){
	  push_back(*iter);
     }

     return *this;
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
     
void IntList::push_back(int value)	//  Functions to add an element to the start and end of the list 
{
     Node * temp = new Node;
     temp -> val = value;
     temp -> next = NULL;
	       
     if (empty()){
	  head = temp;
     }
     else{
	  Node * list_tail = head;
	  while (list_tail -> next != NULL)
	       list_tail = list_tail -> next;
		    
	  list_tail -> next = temp;
     }
}
     
void IntList::push_front(int value)
{
     Node * temp = new Node;
     temp -> val = value;
     temp -> next = head;

     head = temp;
}
     
int IntList::pop_back()		//  Functions to remove an element from the start and end of the list 
{
     int value;
     if (empty ()){
	  return 0;
     }

     // To get to the second-to-last element
     Node * curr = head;
     if (curr -> next == NULL){
	  value = curr -> val;
	  delete curr;

	  head = NULL;
	  return value;
     }
     else{
	  while ((curr -> next) -> next != NULL)
	       curr = curr -> next;
	  value = (curr -> next) -> val;
	  delete curr -> next;
	  curr -> next = NULL;
	  return value;
     }
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
	  return value;
     }
     else{
	  head = curr -> next;
	  value = curr -> val;
	  delete curr;
	  return value;
     }
}
     
void IntList::clear()		//  Function to delete all elements from the list 
{
     while (!empty ()){
	  pop_back ();
     }
}

/* Functions to start and end an iteration*/
IntList::Iterator IntList::begin() const 	// begin returns an Iterator corresponding to the begin element
{
     Iterator beg_iter;
     beg_iter.curr_node = head;
     return beg_iter;
}
IntList::Iterator IntList::end() const 	// end should return an element that indicates that iterator is complete. That is it should return the value obtained on incrementing an iterator corresponding to the last element.
{
     IntList::Iterator iter;	// Note : iter -> curr_node = NULL (constructor)
     return iter;
}
     
void IntList::insert( const IntList::Iterator &given_iter, int value) //  insert adds an element after the given iterator 
{
     // Note : Doing nothing if given iterator value is not found in the list
     int iter_value;
     Node * temp = new Node, *curr;
     temp -> val = value;
     if (given_iter == end())
	  cout << "ERROR - Insert : The given iterator is empty!\n";
     else{
	  iter_value = *given_iter;
	  if (empty ()){
	       // head = temp;
	       // temp -> next = NULL;
	       delete temp;
	  }
	  else{
	       curr = head;
	       while (curr != NULL && (curr -> val) != iter_value)
		    curr = curr -> next;
	
	       if (curr != NULL){ // If found
		    temp -> next = curr -> next;
		    curr -> next = temp;
	       }
	  }
     }
}
	       
void IntList::remove(IntList::Iterator &given_iter)       // remove, deletes the element at the iterator and moves the iterator to the next element
{
     // Don't do anything if *iterator is not found in list
     Node * curr = head, *temp;
     if (given_iter == end())
	  cout << "ERROR - Remove : Given iterator is empty!\n";
     else if (!empty()){
	  if(head -> val == *given_iter){ // Single element
	       temp = head;
	       head = head -> next;
	       delete temp;
	  }
	  else{
	       while (curr -> next != NULL && ((curr -> next) ->val) != *given_iter)
		    curr = curr -> next;
	       if (curr -> next != NULL){
		    temp = curr -> next;
		    curr -> next = temp -> next;
		    ++given_iter;
		    delete temp;
	       }
	  }
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

// int main(){

//      // Testing code :
//      IntList list;
     
//      list.push_back (10);
//      list.push_back (20);
//      list.push_front (100);
//      list.push_front (200);
//      list.print();
//      IntList::Iterator iter = list.begin();
//      IntList::Iterator iter2 (iter);
//      iter2.print();
     
//      for (iter = list.begin(); iter != list.end(); ++iter)
// 	  iter.print();
     
//      IntList list2 = list, list3 (list);
//      cout << "Empty : " << list.empty() << endl;
//      cout << "Size : " << list.size() << endl;
     
//      while (!list3.empty()){
// 	  cout << list3.pop_front() << endl;
//      }
     
//      list2.clear();
//      cout << list2.size();
     
//      iter = list.begin();
//      list.insert(++iter, 500);
//      list.remove(iter);
//      list.print();
//      iter = list3.begin();
//      list3.insert(iter, 500);
//      list3.insert (iter, 1000);
//      iter = list3.begin();
     
//      list3.remove(iter);
     
//      list3.print();
//      return 0;
// }