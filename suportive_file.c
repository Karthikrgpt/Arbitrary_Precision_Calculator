#include "apc.h"

int digit_to_list(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,char *argv[]) {

    for ( int i = 0; argv[1][i]; i++) if (dl_insert_last(head1, tail1, argv[1][i] - '0') == FAILURE) return FAILURE;
    for ( int i = 0; argv[3][i]; i++) if (dl_insert_last(head2, tail2, argv[3][i] - '0') == FAILURE) return FAILURE;

    /*removing leading zeros*/
	if (remove_leading_zeros(head1) == FAILURE) {
		printf("ERROR: Failed to remove leading zero from the list.\n");
		return FAILURE;
	}

	if (remove_leading_zeros(head2) == FAILURE) {
		printf("ERROR: Failed to remove leading zero from the list.\n");
		return FAILURE;
	}

	return SUCCESS;
}

int verify_argv(int argc, char *argv[]) {

	printf("-------------------------------------------------------\n");
	printf("\t   Arbitrary Precision Calculator\n");
	printf("-------------------------------------------------------\n");

	if (argc != 4) {
		printf("ERROR: Invalid Command.\nSample Command: ./output.out operand1 operator operand2\n");
        printf("Sample Operators:\n\t1. Addition:           +\n\t2. Subtraction:        -\n\t3. Multiplication:     \\*\n\t4. Division:           /\n");
		return FAILURE;
	}

	for ( int i = 0; argv[1][i]; i++) 
		if (!isdigit(argv[1][i])) {
			printf("ERROR: Invaild Operand1 %s\n", argv[1]);
			return FAILURE;
		}

    if (strlen(argv[2]) != 1) {
        printf("ERROR: Invaild Operator %s\n", argv[2]);
        printf("Sample Operators:\n\t1. Addition:           +\n\t2. Subtraction:        -\n\t3. Multiplication:     \\*\n\t4. Division:           /\n");
        return FAILURE;
    }

    if (!strchr("+-*/", argv[2][0])) {
        printf("ERROR: Invaild Operator %c\n", argv[2][0]);
        printf("Sample Operators:\n\t1. Addition:           +\n\t2. Subtraction:        -\n\t3. Multiplication:     \\*\n\t4. Division:           /\n");
        return FAILURE;
    }

	for ( int i = 0; argv[3][i]; i++)
		if (!isdigit(argv[3][i])) {
			printf("ERROR: Invaild Operand2 %s\n", argv[3]);
			return FAILURE;
		}

	return SUCCESS;
}

int compare_lists(Dlist *head1, Dlist *head2) {

    Dlist *temp1 = head1, *temp2 = head2;

    // Skip leading zeros without modifying original lists
    while (temp1 && temp1->data == 0) temp1 = temp1->next;
    while (temp2 && temp2->data == 0) temp2 = temp2->next;

    int len1 = 0, len2 = 0; // Compare lengths
    for (Dlist* temp = temp1; temp; temp = temp->next) len1++;
    for (Dlist* temp = temp2; temp; temp = temp->next) len2++;

    if (len1 > len2) return LARGER;
    if (len1 < len2) return SMALLER;

    // Compare digit by digit
    while (temp1 && temp2) {
        if (temp1->data > temp2->data) return LARGER;
        if (temp1->data < temp2->data) return SMALLER;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return EQUAL;
}

int remove_leading_zeros( Dlist **head) {

    while (*head && (*head)->data == 0 && (*head)->next ) {
        Dlist *temp = *head;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp);
    }

    return SUCCESS;
}

int dl_insert_first(Dlist **head, Dlist **tail, int data) {
    

    Dlist *new = (Dlist *) malloc( sizeof(Dlist));
    if ( new == NULL ) return FAILURE;

    new->prev = NULL;
    new->data = data;
    new->next = NULL;

    if ( *head == NULL && *tail == NULL ) {
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    (*head)->prev = new;
    new->next = *head;
    *head = new;

    return SUCCESS;
}

int dl_insert_last(Dlist **head, Dlist **tail, int data) {

    Dlist *new = (Dlist *) malloc( sizeof(Dlist));

    if ( new == NULL ) return FAILURE;

    new->prev = NULL;
    new->data = data;
    new->next = NULL;

    if ( *head == NULL && *tail == NULL ) {
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    (*tail)->next = new;
    new->prev = *tail;
    *tail = new;

    return SUCCESS;
} 

int dl_delete_list(Dlist **head, Dlist **tail) {

    if (*head == NULL && *tail == NULL) return SUCCESS;

    Dlist *temp;

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *head = NULL;
    *tail = NULL;

    return SUCCESS;
}

int dl_delete_first(Dlist **head, Dlist **tail) {

    if ( *head == NULL && *tail == NULL ) return FAILURE;

    if ( *head == *tail ) {
        free((*head));
        *head = NULL;
        *tail = NULL;

        return SUCCESS;
    }

    *head = (*head)->next;
    free((*head)->prev);
    (*head)->prev = NULL;

    return SUCCESS;
}

void display_error( char *message) {
    printf("%s\n", message);
    printf("-------------------------------------------------------\n");
}

void display_data(Dlist *head1, Dlist *head2, Dlist *headR, char symbol) {

    switch(symbol) {
        
		case '+': printf("Addition:-\n"); break;
		case '-': printf("Subtraction:-\n"); break;
		case '*': printf("Multiplication:-\n"); break;
		case '/': printf("Division:-\n"); break;
    }

    printf("\n\t  ");
    print_list(head1);
    printf("\n        %c ", symbol);
    print_list(head2);
    printf("\n        ");

    
    int len1 = 0, len2 = 0, lenR = 0; // Compare lengths
    for (Dlist* temp = head1; temp; temp = temp->next) len1++;
    for (Dlist* temp = head2; temp; temp = temp->next) len2++;
    for (Dlist* temp = headR; temp; temp = temp->next) lenR++;

    int len = len1 > len2 ? (len1 > lenR ? len1 : lenR) : (len2 > lenR ? len2 : lenR);

    for ( int i = 0; i <= len; i++) printf("-");
    printf("\nResult: ");

    print_list(headR);
    printf("\n        ");

    for ( int i = 0; i <= len; i++) printf("-");
    printf("\n");

    printf("-------------------------------------------------------\n");
}

void print_list(Dlist *head) {

	while (head) {
        if ( head->data == '-') printf("-");
		else printf("%d", head -> data);
	    head = head -> next;
    }

}