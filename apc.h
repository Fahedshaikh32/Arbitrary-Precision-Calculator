#ifndef APC_H              // Check if APC_H not defined
#define APC_H              // Define APC_H to avoid multiple inclusion

#include <stdio.h>         // Standard input output library
#include <stdlib.h>        // Standard memory library

#define SUCCESS 0          // Define SUCCESS value
#define FAILURE -1         // Define FAILURE value

typedef int data_t;        // Define data_t as integer type

typedef struct node        // Structure for doubly linked list node
{
    struct node *prev;     // Pointer to previous node
    data_t data;           // Store digit data
    struct node *next;     // Pointer to next node
} Dlist;                   // Rename struct node as Dlist

int apc_validation(char *argv[], char *operator);   // Function to validate input

int str_to_list(char **argv, Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2);   // Convert string to list

void print_list(Dlist *headR);   // Print linked list result

void insert_front(Dlist **head, Dlist **tail, int data);   // Insert node at front

int is_zero(Dlist *head);   // Check if number is zero

void copy_list(Dlist *src, Dlist **head, Dlist **tail);   // Copy one list to another

void remove_leading_zeros(Dlist **head, Dlist **tail);   // Remove extra zeros

void add_sign_node(Dlist **headR, Dlist **tailR);   // Add negative sign node

void increment_by_one(Dlist **head, Dlist **tail);   // Increase number by 1

int compare_lists(Dlist *h1, Dlist *h2);   // Compare two numbers

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);   // Addition function

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);   // Subtraction function

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);   // Multiplication function

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);   // Division function

#endif                     // End of header file
