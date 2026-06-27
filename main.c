    /*
    NAME:- FAHED SHAIKH

    START DATE:- 08/02/2026

    END DATE:- 18/02/2026

    DESCRIPTION:-    The APC Project is a calculator that performs arithmetic operations on large multi-digit numbers.

    Since normal data types in C have size limits, this project uses a Doubly Linked List to store each digit of the number separately.

    It supports:

    Addition (+)

    Subtraction (-)

    Multiplication (*)

    Division (/)

    The program takes input from the command line, converts numbers into linked lists, performs the operation, and prints the result.


    SAMPLE INPUT/ OUTPUT:-  


    fahed@FAHED:/mnt/c/Users/Fahed/Downloads/APC/APC$ gcc *.c
    fahed@FAHED:/mnt/c/Users/Fahed/Downloads/APC/APC$ ./a.out 10 + 10
    20
    fahed@FAHED:/mnt/c/Users/Fahed/Downloads/APC/APC$ ./a.out 10 - 10
    0
    fahed@FAHED:/mnt/c/Users/Fahed/Downloads/APC/APC$ ./a.out 10 - 1
    9
    fahed@FAHED:/mnt/c/Users/Fahed/Downloads/APC/APC$ ./a.out 1 - 10
    -9
    fahed@FAHED:/mnt/c/Users/Fahed/Downloads/APC/APC$ ./a.out 10 '*' 10
    100
    fahed@FAHED:/mnt/c/Users/Fahed/Downloads/APC/APC$ ./a.out 10 '/' 10
    1
    fahed@FAHED:/mnt/c/Users/Fahed/Downloads/APC/APC$
    */


#include <stdio.h>              
#include "apc.h"                

int main(int argc, char *argv[])   // Main function with command line arguments
{
    Dlist *head1 = NULL, *tail1 = NULL;   // First number linked list head and tail
    Dlist *head2 = NULL, *tail2 = NULL;   // Second number linked list head and tail
    Dlist *headR = NULL, *tailR = NULL;   // Result linked list head and tail

    char operator;               // To store operator (+,-,*,/)
    int sign1 = 1, sign2 = 1, signR = 1;   // Signs of operand1, operand2 and result

    if (argc != 4) {             // Check correct number of arguments
        printf("Usage: ./apc <operand1> <operator> <operand2>\n");  // Show usage message
        return FAILURE;          // Return failure if wrong input
    }

    if (apc_validation(argv, &operator))   // Validate input and get operator
        return FAILURE;          // Return if validation fails

    if (argv[1][0] == '-') sign1 = -1;   // Check if first number is negative
    if (argv[3][0] == '-') sign2 = -1;   // Check if second number is negative

    if (str_to_list(argv, &head1, &tail1, &head2, &tail2))   // Convert string to linked list
        return FAILURE;          // Return if conversion fails

    int cmp;                     // Variable to store compare result

    switch (operator)            // Check which operator is used
    {
        case '+':                // If operator is addition
            if (sign1 == sign2) {   // If both signs are same
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);  // Perform addition
                signR = sign1;    // Result sign same as operands
            }
            else {                // If signs are different
                cmp = compare_lists(head1, head2);   // Compare two numbers
                if (cmp == 0) {   // If both numbers equal
                    printf("0\n");  // Print zero
                    return SUCCESS;  // Return success
                }
                else if (cmp > 0) {   // If first number greater
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);  // Do subtraction
                    signR = sign1;   // Result sign same as first
                }
                else {              // If second number greater
                    subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);  // Reverse subtraction
                    signR = sign2;   // Result sign same as second
                }
            }
            break;               // Exit case

        case '-':                // If operator is subtraction
            sign2 = -sign2;      // Reverse second number sign
            if (sign1 == sign2) {   // If signs same after change
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);  // Perform addition
                signR = sign1;   // Result sign
            }
            else {               // If signs different
                cmp = compare_lists(head1, head2);   // Compare numbers
                if (cmp == 0) {   // If equal
                    printf("0\n");  // Print zero
                    return SUCCESS;  // Return success
                }
                else if (cmp > 0) {   // If first greater
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);  // Subtract
                    signR = sign1;   // Result sign
                }
                else {             // If second greater
                    subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);  // Reverse subtract
                    signR = sign2;   // Result sign
                }
            }
            break;               // Exit case

        case '*':                // If operator is multiplication
            multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);  // Multiply numbers
            signR = sign1 * sign2;   // Result sign depends on operands
            break;               // Exit case

        case '/':                // If operator is division
            if (division(&head1, &tail1, &head2, &tail2, &headR, &tailR) == FAILURE)  // Perform division
                return FAILURE;  // Return if division fails
            signR = sign1 * sign2;   // Result sign
            break;               // Exit case

        default:                 // If operator invalid
            printf("Invalid operator\n");  // Print error
            return FAILURE;      // Return failure
    }

    if (signR == -1 && !is_zero(headR))   // If result negative and not zero
        add_sign_node(&headR, &tailR);    // Add negative sign node

    print_list(headR);          // Print final result

    return SUCCESS;             // End program successfully
}
