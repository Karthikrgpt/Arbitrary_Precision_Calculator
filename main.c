#include "apc.h"

int main(int argc, char* argv[]) {

	/* Declare the pointers */
      
	Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL; 
    Dlist *headR = NULL,*tailR = NULL;

	if (verify_argv(argc, argv) == FAILURE) {
		display_error("ERROR: Failed to verify the Command Line Arguments");
		return FAILURE;
	}

	if (digit_to_list(&head1,&tail1,&head2,&tail2, argv) == FAILURE){
		display_error("ERROR: Failed to convert digit to list.");
		return FAILURE;
	}

	char operator = argv[2][0];

	switch (operator) {

		case '+':
        	if (addition(&head1,&tail1,&head2,&tail2,&headR,&tailR) == FAILURE) {
				display_error("ERROR: Failed to do addition.");
				return FAILURE;
			}
			break;
		case '-':	
			if (subtraction(&head1,&tail1,&head2,&tail2,&headR,&tailR) == FAILURE) {
				display_error("ERROR: Failed to do subtraction.");
				return FAILURE;
			}
			break;
		case '*':	
			if (multiplication(&head1,&tail1,&head2,&tail2,&headR,&tailR) == FAILURE) {
				display_error("ERROR: Failed to do multiplication.");
				return FAILURE;
			}

			break;
		case '/':	
			if (division(&head1,&tail1,&head2,&tail2,&headR,&tailR)  == FAILURE) {
				display_error("ERROR: Failed to do division.");
				return FAILURE;
			}

			break;
	}

	display_data(head1, head2, headR, operator);

	return FAILURE;
}
