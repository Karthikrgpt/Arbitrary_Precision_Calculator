#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR) {

    Dlist *temp_head1 = *head1, *temp_tail1 = *tail1;
    long long int count = 0;

    if ((*head2)->data == 0) {
        printf("ERROR: Can't division with 0.\n");
        return FAILURE;
    }

    while (compare_lists(temp_head1, *head2) == LARGER) {

        if (subtraction(&temp_head1, &temp_tail1, head2, tail2, headR, tailR) == FAILURE) {
            printf("ERROR: Failed to do subtraction.\n");
            return FAILURE;
        }

        temp_head1 = *headR;
        temp_tail1 = *tailR;
        *headR = NULL;
        *tailR = NULL;

		count++;
    }

	if (compare_lists(temp_head1, *head2) == EQUAL) count++;

    if (dl_insert_last(headR, tailR, count)  == FAILURE) {
        printf("ERROR: Failed to inset the data to the node.\n");
        return FAILURE;
    }

    return SUCCESS;
}
