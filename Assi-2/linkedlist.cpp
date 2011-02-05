/*
  Title : Linked List Implementation in C++

  Purpose : To implement a Linked List using classes

  Author : S. Pradeep Kumar
  Date : 16 - 01 - 2011


  Problems:
  * head was not initialized to NULL

  To compile:
  g++ linkedlist.cpp

  To execute:
  ./a.out

  Major Implementation Details:
  * The nodes of the Linked List were defined as objects of Node class
  * Then, a Linked List class was defined
  */

#include <iostream>
#include "linkedlist.h"

using namespace std;


IntList::Iterator ()
{
     curr_node = NULL;
}

IntList::Iterator (const Iterator & orig_iter) //  Copy constructor
{
     *this = orig_iter;
}

IntList::Iterator IntList::Iterator::operator=(const Iterator & orig_iter) // Assignment operator
{
     curr_node = orig_iter.curr_node;
}

IntList::Iterator IntList::Iterator::operator++()	// Postfix operator
{
     Iterator * temp = this;

     if(curr_node)
	  curr_node = curr_node -> next;
     return *temp;
}

int & IntList::Iterator::operator*() const //  Operators to return elements contained in the list 
{
     // if (curr_node == NULL)
     // 	  return -1;
     return curr_node->val;

}

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

// IntList method definitions

IntList::IntList ()
{
     // Without this line, inserting and then trying to
     // access the elements of the list would lead to a
     // seg fault
     head = NULL;
}
     
IntList::IntList(Node *list_head) 
{
     head = list_head;
}

int IntList::insert(int value) 
{
     // Insert a new node
     Node * temp = new Node (value);
     temp -> next = head;
     head = temp;
     return 0;
}
     
int IntList::insert_After(int number_to_insert, int number_in_list) {
     // Should insert an element in a place other than head
     // Insert at tail if number_in_list is not in list
     Node * temp = new Node (number_to_insert);
     Node * curr = head;
     if (head == NULL)
     {
	  insert (number_to_insert);
	  return 0;
     }
     
     while (curr -> next != NULL && curr -> data != number_in_list)
	  curr = curr -> next;
     temp -> next = curr -> next;
     curr -> next = temp;
     return 0;
}

int IntList::pop ()
{
     // Method to pop a node from the head of the Linked
     // List and return the value in that node
     Node *temp = NULL;
     int val;
     if (head == NULL)
	  return 0;
     else{
	  temp = head;
	  head = head -> next;
	  val = temp -> data;
	  delete temp;
	  return val;
     }
}
     
int IntList::delete_Node(int value) 
{
     // Delete node matching given value
     Node *temp = NULL, *curr = NULL;
     if (head == NULL)
	  return -1;
     else if (head -> data == value){
	  temp = head;
	  head = head -> next;
	  delete temp;
	  return 0;
     }

     curr = head;
     while (curr -> next != NULL && (curr -> next) -> data != value)
	  curr = curr -> next;

     if (curr -> next != NULL){
	  temp = curr -> next;
	  curr -> next = temp -> next;
	  delete temp;
     }
     return 0;
}
     
bool IntList::search(int value)
{
     Node *curr = head;
     while (curr != NULL && curr -> data != value)
	  curr = curr -> next;
     if (curr == NULL)
	  return 0;
     else
	  return 1;
}
     
bool IntList::is_Empty ()
{
     if (head == NULL)
	  return 1;
     return 0;
}
     
Node* IntList::next_Node(Node* somenode) 
{
     if (somenode == NULL){
	  cout << "Given node was NULL!\n";
	  return NULL;
     }
     return somenode -> next;
}
     
void IntList::print_IntList() 
{
     Node *curr = head;
     cout << "IntList :";
	       
     while (curr != NULL){
	  cout << ' ' << curr -> data;
	  curr = curr -> next;
     }
     cout << '\n';
}
     
// int main()
// {
//      // Test inputs
//      IntList l;
//      l.insert (10);
//      l.insert (20);
//      l.insert (30);
//      l.insert (40);
//      l.insert (50);
//      l.print_IntList ();
//      l.insert_After (45, 40);
//      l.insert_After (100, 50);
//      l.print_IntList ();
//      l.delete_Node (40);
//      l.print_IntList ();
//      l.delete_Node (40);
//      l.print_IntList ();    
//      cout << l.search (100) << endl;
//      cout << l.is_Empty () << endl;

//      l.print_IntList ();
//      Node * somenode1 = new Node (25);
//      IntList l2 (somenode1);
//      l2.insert_After (10, 25);
//      l2.insert_After (20, 25);
//      l2.insert_After (30, 25);
//      l2.print_IntList ();
     
//      somenode1 = l2.next_Node (somenode1);
//      cout << somenode1 -> data << endl;
//      somenode1 = l2.next_Node (somenode1);
//      cout << somenode1 -> data << endl;
//      for (int i = 0; i < 6; i++)
// 	  l2.pop();
//      l2.print_IntList();
     
//      return 0;
// }

