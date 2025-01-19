#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR) {
	
	Dlist *temp1, *temp2;
	char result = 0, borrow = 0, temp_var, symbol;

	if (compare_lists(*head1, *head2) == SMALLER) {
		temp1 = *tail2;
		temp2 = *tail1;
		symbol = '-';
	} else {
		temp1 = *tail1;
		temp2 = *tail2;		
	}
	
	while (temp1 || temp2) {

		temp_var = temp1->data;

		if (borrow) {
			temp_var--;
			borrow = 0;
		}

		if ( temp_var < (temp2 ? temp2->data : 0)) {

			borrow = 1;
			result = ( temp_var + 10 ) -  (temp2 ? temp2->data : 0);

		} else result = temp_var - (temp2 ? temp2->data : 0);

		if ( dl_insert_first(headR, tailR, result ) == FAILURE) {
			printf("ERROR: Failed to insert the data to the node.\n");
			return FAILURE;
		}

		if (temp1) temp1 = temp1->prev;
		if (temp2) temp2 = temp2->prev;
	}

	if (remove_leading_zeros(headR) == FAILURE) {
		printf("ERROR: Failed to remove leading zero from the list.\n");
		return FAILURE;
	}

	if (symbol == '-' && dl_insert_first(headR, tailR, '-' ) == FAILURE) {
		printf("ERROR: Failed to insert the '-' symbol to the node.\n");
		return FAILURE;
	}

	return SUCCESS;
}
