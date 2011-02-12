#ifndef LLIST_H
#define LLIST_H
class Node 
{ 
public: 
     int val; 
     Node *next; 
     Node *prev;
};

class IntList {
private:
     Node * head;
     Node * tail;
public:
     IntList();							//  Constructor 
     IntList(const IntList & llist);				//  Copy constructor
     IntList &	operator = (const IntList & llist);		//  Assignment Operator 
     bool empty() const;					//  Function to check if the list is empty 
     unsigned int size() const;					//  Function to return the number of elements 
     void push_front(int value);
     int pop_front();
     void clear();						//  Function to delete all elements from the list 
     void print ();
     ~IntList();						//  Destructor to delete elements 
};

#endif
