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
     List ();

     List(Node *list_head);

     int insert(int value);

     int insert_After(int number_to_insert, int number_in_list);
     int pop ();

     int delete_Node(int value);

     bool search(int value);

     bool is_Empty ();

     Node* next_Node(Node* somenode);

     void print_List();

};
