#include<iostream>

using namespace std;

template <class Type>
class Node
{
public:
	Type data;
	Node *next;
	Node() {next=NULL;}
};

template <class Type>
class Stack
{
	int size;
     Node <Type> * head;
public:
	Stack() {head=NULL,size=0;}
	bool isempty();
	void push(Type);
	Type pop();
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

void Stack::push(Type a)
{
     Node <Type>* tmp = new Node <Type>;
	tmp->next=head;
	tmp->data=a;
	head=tmp;
	size++;	
}

char Stack::pop()
{
	if(head==NULL)
	{
		cout<<"Sorry u r poping from empty stack"<<endl;
		return 'a';	//i don't know what to return
	}
	else
	{
		Node <Type>* tmp = head;
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
