#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE -1

#define EQUAL 2
#define LARGER 1
#define SMALLER 0

typedef struct node
{
	struct node *prev;
	int data;
	struct node *next;
}Dlist;

/*Verify the arguments */
int verify_argv(int argc, char *argv[]);

/*store the operands into the list */
int digit_to_list(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,char *argv[]);

/*Addition */
int addition(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*subtraction*/
int subtraction(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*Multiplication*/
int multiplication(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*Division */
int division(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*Comparing list1 with list2 and returing larger or not*/
int compare_lists(Dlist *head1, Dlist *head2);

/*Remove leadig zeros from the list*/
int remove_leading_zeros( Dlist **head);

/*Basic 2D linked list*/
int dl_insert_first(Dlist **head, Dlist **tail, int data);
int dl_insert_last(Dlist **head, Dlist **tail, int data);
int dl_delete_list(Dlist **head, Dlist **tail);
int dl_delete_first(Dlist **head, Dlist **tail);

/*To display the message, data, and list*/
void display_error( char *message);
void display_data(Dlist *head1, Dlist *head2, Dlist *headR, char symbol);
void print_list(Dlist *head);

#endif
