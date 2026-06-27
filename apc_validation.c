#include <stdio.h>             
#include "apc.h"                

int apc_validation(char *argv[], char *operator)    // Function to validate input
{
    if (argv[2][0] == '+' || argv[2][0] == '-' || argv[2][0] == '*' || argv[2][0] == '/')    
        *operator = argv[2][0];     // Store operator if valid
    else {
        printf("ERROR: Invalid operator '%s'\n", argv[2]);   // Print error if operator invalid
        return FAILURE;             // Return failure
    }

    for (int i = 0; argv[1][i]; i++) {    // Loop through operand 1
        if (i == 0 && (argv[1][i] == '+' || argv[1][i] == '-') && argv[1][i+1] != '\0')     
            continue;              // Allow sign at first position
        if (argv[1][i] < '0' || argv[1][i] > '9') {   // Check if not a digit
            printf("ERROR: Operand 1 should contain only digits\n");   // Print error
            return FAILURE;         // Return failure
        }
    }

    for (int i = 0; argv[3][i]; i++) {    // Loop through operand 2
        if (i == 0 && (argv[3][i] == '+' || argv[3][i] == '-') && argv[3][i+1] != '\0')     
            continue;              // Allow sign at first position
        if (argv[3][i] < '0' || argv[3][i] > '9') {   // Check if not a digit
            printf("ERROR: Operand 2 should contain only digits\n");   // Print error
            return FAILURE;         // Return failure
        }
    }
    return SUCCESS;                 // Return success if all valid
}
