/*
  Title : Linked List Implementation in C

  Purpose : To implement a Linked List using structures and pointers

  Author : S. Pradeep Kumar
  Date : 16 - 01 - 2011

  To compile:
  gcc linkedlist.c

  Execute:
  ./a.out

  Major Implementation Details:
  * Pointers were used to point to the next node of the Linked List

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct lnode
{
     int data;
     struct lnode *next;
}listNode;

int insert (int value, listNode **head)
{
     /* Insert a node at the beginning of the list */
     listNode * temp = NULL;
     temp = (listNode *) malloc (sizeof (listNode));
     if (temp == NULL){
	  printf ("Error! Unable to allocate memory...");
	  return -1;
     }

     temp -> data = value;
     temp -> next = *head;
     *head = temp;
     return 0;
}

int insert_After (int number_to_insert, int number_in_list, listNode **head)
{
     /*
       Should insert an element in a place other than head
       Insert at tail if number_in_list is not in list
     */
     listNode * curr = *head;
     if (*head == NULL){
	  insert (number_to_insert, head);
	  return 0;
     }
     while (curr -> next != NULL && curr -> data != number_in_list)
	  curr = curr -> next;

     listNode * temp = NULL;
     temp = (listNode *) malloc (sizeof (listNode));

     if (temp == NULL){
	  printf ("Error! Unable to allocate memory...");
	  return -1;
     }

     temp -> data = number_to_insert;
     temp -> next = curr -> next;
     curr -> next = temp;
     return 0;
}

int delete_Node (int value, listNode **head)
{
     /* Delete the node having data 'value' */
     listNode * temp = NULL, * curr = NULL;
     if (*head == NULL)
	  return 0;
     else if ((*head) -> data == value){
	  temp = *head;
	  *head = (*head) -> next;
	  free (temp);
	  return 0;
     }
     curr = *head;
     while (curr -> next != NULL && (curr -> next) -> data != value)
	  curr = curr -> next;

     if (curr -> next != NULL){
	  temp = curr -> next;
	  curr -> next = temp -> next;
	  free (temp);
     }
     return 0;
}
	  

int search (int value, listNode *head)
{
     /*
       Return 1 if node with matching value is found;
       Else, 0
     */
     listNode * curr = head;
     while (curr != NULL && curr -> data != value)
	  curr = curr -> next;
     if (curr != NULL)
	  return 1;
     else
	  return 0;
}

int is_Empty (listNode *head)
{
     if (head == NULL)
	  return 1;
     else
	  return 0;
}

listNode * next_Node (listNode * somenode, listNode *head)
{
     if (somenode == NULL){
	  printf ("Given pointer to node is NULL!\n");
	  return NULL;
     }
     return somenode -> next;
}

void print_List (listNode *head)
{
     /* Print the list of values */
     listNode * temp = head;
     printf ("List: ");
     while (temp != NULL){
	  printf ("%-d\t", temp -> data);
	  temp = temp -> next;
     }
     printf("\n");
}
 
int main()
{
     /* Test inputs */
     listNode * head = NULL;
     insert (10, &head);
     insert (20, &head);
     insert (30, &head);
     insert (40, &head);
     insert (50, &head);
     print_List (head);
     insert_After (45, 40, &head);
     insert_After (100, 50, &head);
     print_List (head);

     delete_Node (40, &head);
     print_List (head);
     delete_Node (40, &head);
     print_List (head);    
     printf("%d\n", search (100, head));
     printf("%d\n", is_Empty (head));

     listNode * somenode1 = NULL;
     somenode1 = next_Node (head, head);
     printf("%d\n", somenode1 -> data);
     somenode1 = next_Node (somenode1, head);
     printf("%d\n", somenode1 -> data);
     return 0;
}

