#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR) {
	
	Dlist *temp1 = *tail1, *temp2 = *tail2;
	char result = 0, carry = 0;

	while (temp1 || temp2 ) {

		result = (temp1 ? temp1->data : 0) + (temp2 ? temp2->data : 0)+ carry;

		if (dl_insert_first(headR, tailR, result % 10) == FAILURE) {
			printf("ERROR: Failed to insert the data to the node.\n");
			return FAILURE;
		}

		if (result >= 10) carry = result / 10;
		else carry = 0;

		if (temp1) temp1 = temp1->prev;
		if (temp2) temp2 = temp2->prev;
	}

	if (carry && dl_insert_first(headR, tailR, carry) == FAILURE) {
		printf("ERROR: Failed to insert the data to the node.\n");
		return FAILURE;
	}

	if (remove_leading_zeros(headR) == FAILURE) {
		printf("ERROR: Failed to remove leading zero from the list.\n");
		return FAILURE;
	}

	return SUCCESS;
}