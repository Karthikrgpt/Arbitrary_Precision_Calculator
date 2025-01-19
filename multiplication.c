#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR) {
	
	Dlist *Result1 = NULL, *Tail1 = NULL;
    Dlist *Result2 = NULL, *Tail2 = NULL;
	Dlist *temp1 = NULL, *temp2 = NULL;

	long long int stage = 0;
	char carry = 0, result = 0;

	temp1 = *tail1;
	temp2 = *tail2;

    while (temp2) {

        temp1 = *tail1;

        while (temp1) {

            result = temp2->data * temp1->data + carry;

            if ( dl_insert_first(&Result1, &Tail1, result % 10)  == FAILURE) {
			    printf("ERROR: Failed to insert the data to the node.\n");
			    return FAILURE;
		    }

			if (result >= 10) carry = result / 10;
			else carry = 0;

            temp1 = temp1->prev; 
        }

        if (carry) {
			if (dl_insert_first(&Result1, &Tail1, carry)  == FAILURE) {
			    printf("ERROR: Failed to insert the data to the node.\n");
			    return FAILURE;
		    }
			carry = 0;
		}

        /* Add zeros for positional adjustment (if not first iteration) */
        for(int i = 0; i < stage; i++) 
            if ( dl_insert_last(&Result1, &Tail1, 0) == FAILURE) {//append zero to Result2
			printf("ERROR: Failed to append zero to the node.\n");
			return FAILURE;
		}

        /* Add Result1 and Result2, storing the result directly into headR and tailR */
        if (addition(&Result1, &Tail1, &Result2, &Tail2, headR, tailR) == FAILURE) {
			printf("ERROR: Failed to perform addition.\n");
			return FAILURE;
		}

        /* Copy current result (headR) to Result2 for the next iteration, reset Result1 for next multiplication*/
		if (dl_delete_list(&Result1, &Tail1) == FAILURE) {
		    printf("ERROR: Failed to delete the list.\n");
		    return FAILURE;
		}

        if (dl_delete_list(&Result2, &Tail2) == FAILURE) {
			printf("ERROR: Failed to delete the list.\n");
		    return FAILURE;
	    }

		for ( Dlist *temp = *headR; temp; temp = temp->next ) 
            if (dl_insert_last(&Result2, &Tail2, temp->data)  == FAILURE) {
			    printf("ERROR: Failed to insert the data to the node.\n");
			    return FAILURE;
		    }
        
        if (dl_delete_list(headR, tailR) == FAILURE) {
			printf("ERROR: Failed to delete the list.\n");
		    return FAILURE;
	    }
		
		stage++;
		temp2 = temp2->prev; // Move to the previous node in list2
    }

	*headR = Result2;

    /*removing leading zeros*/
	if (remove_leading_zeros(headR) == FAILURE) {
		printf("ERROR: Failed to remove leading zero from the list.\n");
		return FAILURE;
	}

    return SUCCESS;
}