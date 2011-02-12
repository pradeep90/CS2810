#include<iostream>

using namespace std;

class Node
{
public:
     int data;
     Node *next;
     Node() {next=NULL;}
};

class Stack
{
     int size;
     Node * head;
public:
     Stack() {head=NULL,size=0;}
     bool isempty();
     void push(int);
     int pop();
     int get_size();
};

int Stack::get_size()
{
     return size;
}

bool Stack::isempty()
{
     if(head==NULL)
	  return 1;
     else
	  return 0;
}

void Stack::push(int a)
{
     Node * tmp = new Node;
     tmp->next=head;
     tmp->data=a;
     head=tmp;
     size++;	
}

int Stack::pop()
{
     if(head==NULL)
     {
	  cout<<"Sorry u r poping from empty stack"<<endl;
	  return 'a';	//i don't know what to return
     }
     else
     {
	  Node * tmp = head;
	  head=head->next;
	  size--;
	  return tmp->data;
     }
}

//main()
//{
//	Stack a;
//	a.push('c');
//	a.push('2');
//	if(a.isempty())
//		cout<<"empty"<<endl;
//	else
//		cout<<"not empty"<<endl;
//	cout<<a.pop()<<endl;
//	cout<<a.pop()<<endl;
//	cout<<a.pop()<<endl;
//	Stack b;

//}
