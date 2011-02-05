class Node 
{ 
public: 
     int data; 
     Node *next; 
     Node() {next = NULL;} 
     Node(int num) {data = num; next = NULL;} 
};

class List 
{ 
     Node *head; 
public: 
     class Iterator
     {
     private:
	  Node * curr_node;
     public:
	  Iterator () {};
	  Iterator (const Iterator & orig_iter) {}; //  Copy constructor
	  Iterator operator=(const Iterator & orig_iter) {}; // Assignment operator
	  Iterator operator++() {};	// Postfix operator
	  int &operator*() {}; const //  Operators to return elements contained in the list 
	  bool operator==(Iterator orig_iter) {}; const //  Operators to compare two iterators 
	  bool operator!=(Iterator orig_iter) {}; const
	  void print() {};
	  friend class List;
     };
     List();
     List(Node *list_head);
     List::Iterator begin();
     List::Iterator end();
     int insert(int value);
     int insert_After(int number_to_insert, int number_in_list);
     int pop ();
     int delete_Node(int value);
     bool search(int value);
     bool is_Empty ();
     Node* next_Node(Node* somenode);
     void print_List();
};

