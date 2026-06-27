#include <stdlib.h>              
#include <stdio.h>               
#include "apc.h"                 

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)   // Division function
{
    if (*head2 == NULL || is_zero(*head2)) {   // Check if divisor is zero
        printf("ERROR: Division by zero\n");   // Print error message
        return FAILURE;                        // Return failure
    }

    *headR = *tailR = NULL;        // Initialize result list as empty
    insert_front(headR, tailR, 0); // Insert 0 as initial result

    Dlist *tempH = NULL, *tempT = NULL;   // Temporary list for dividend copy
    copy_list(*head1, &tempH, &tempT);    // Copy first number into temp list

    while (tempH && compare_lists(tempH, *head2) >= 0) {   // Repeat while temp >= divisor
        Dlist *aH = NULL, *aT = NULL;   // Temporary list A
        Dlist *bH = NULL, *bT = NULL;   // Temporary list B

        copy_list(tempH, &aH, &aT);     // Copy temp value to A
        copy_list(*head2, &bH, &bT);    // Copy divisor to B

        Dlist *resH = NULL, *resT = NULL;   // List to store subtraction result

        subtraction(&aH, &aT, &bH, &bT, &resH, &resT);   // Perform temp - divisor
        remove_leading_zeros(&resH, &resT);               // Remove extra zeros

        tempH = resH;              // Update temp head with result
        tempT = resT;              // Update temp tail with result

        increment_by_one(headR, tailR);   // Increase result (quotient) by 1
    }
    return SUCCESS;                // Return success after division
}