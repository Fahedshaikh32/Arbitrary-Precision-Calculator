#include <stdlib.h>              
#include "apc.h"                 

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)   // Addition function
{
    int carry = 0, sum;          // Carry and sum variables
    Dlist *t1 = *tail1;          // Pointer to last digit of number1
    Dlist *t2 = *tail2;          // Pointer to last digit of number2

    *headR = *tailR = NULL;      // Initialize result list

    while (t1 != NULL || t2 != NULL) {   // Loop until both numbers finish
        sum = carry;             // Start sum with carry

        if (t1) { sum += t1->data; t1 = t1->prev; }   // Add digit from number1
        if (t2) { sum += t2->data; t2 = t2->prev; }   // Add digit from number2

        carry = sum / 10;        // Calculate new carry
        insert_front(headR, tailR, sum % 10);   // Insert last digit of sum
    }

    if (carry)  insert_front(headR, tailR, carry);   // Insert remaining carry
    return SUCCESS;           // Return success
}

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)   // Subtraction function
{
    Dlist *t1 = *tail1;       // Pointer to last digit of number1
    Dlist *t2 = *tail2;       // Pointer to last digit of number2
    int borrow = 0;           // Borrow variable

    *headR = *tailR = NULL;   // Initialize result list

    while (t1) {              // Loop until number1 finishes
        int sub = t1->data - (t2 ? t2->data : 0) - borrow;   // Subtract digits with borrow

        if (sub < 0) {        // If result negative
            sub += 10;        // Adjust by adding 10
            borrow = 1;       // Set borrow
        }
        else borrow = 0;      // Reset borrow if no need

        insert_front(headR, tailR, sub);   // Insert result digit

        t1 = t1->prev;        // Move to previous digit of number1
        if (t2) t2 = t2->prev;   // Move to previous digit of number2
    }

    remove_leading_zeros(headR, tailR);   // Remove extra zeros at front
    return SUCCESS;          // Return success
}

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)   // Multiplication function
{
    Dlist *t1 = *head1, *t2 = *head2;   // Get head pointers of both numbers

    if (is_zero(t1) || is_zero(t2)) {   // If any number is zero
        *headR = *tailR = NULL;         // Initialize result
        insert_front(headR, tailR, 0);  // Insert zero
        return SUCCESS;                 // Return success
    }

    Dlist *resultH = NULL, *resultT = NULL;   // Temporary result list
    insert_front(&resultH, &resultT, 0);      // Initialize result with 0

    int shift = 0;       // Shift counter for place value

    for (Dlist *d2 = *tail2; d2; d2 = d2->prev) {   // Loop through second number from last digit
        Dlist *tempH = NULL, *tempT = NULL;         // Temporary list for partial result
        int carry = 0;                              // Carry for multiplication

        for (int i = 0; i < shift; i++)     insert_front(&tempH, &tempT, 0);   // Add zeros for shift

        for (Dlist *d1 = *tail1; d1; d1 = d1->prev) {   // Loop through first number
            int prod = d1->data * d2->data + carry;     // Multiply digits and add carry
            carry = prod / 10;                          // Update carry
            insert_front(&tempH, &tempT, prod % 10);    // Insert last digit
        }

        if (carry)      insert_front(&tempH, &tempT, carry);   // Insert remaining carry

        addition(&resultH, &resultT, &tempH, &tempT, &resultH, &resultT);   // Add partial result
        shift++;       // Increase shift for next digit
    }

    *headR = resultH;   // Assign final head
    *tailR = resultT;   // Assign final tail
    return SUCCESS;     // Return success
}
