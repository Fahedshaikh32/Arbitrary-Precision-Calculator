#include <stdio.h>             
#include <stdlib.h>             
#include "apc.h"                

int str_to_list(char **argv, Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)   // Convert string to doubly linked list
{
    int i = 0;                  // Index for first number
    if (argv[1][0] == '+' || argv[1][0] == '-')     i = 1;   // Skip sign if present

    Dlist *new1 = (Dlist *)malloc(sizeof(Dlist));   // Allocate memory for first node
    if (!new1) return FAILURE;   // Check memory allocation

    *head1 = *tail1 = new1;      // Initialize head and tail
    new1->prev = NULL;           // First node previous is NULL
    new1->next = NULL;           // First node next is NULL
    new1->data = argv[1][i++] - '0';   // Store first digit

    Dlist *temp = *head1;        // Temporary pointer

    for (; argv[1][i]; i++) {    // Loop through remaining digits
        new1 = (Dlist *)malloc(sizeof(Dlist));   // Allocate new node
        if (!new1) return FAILURE;   // Check memory

        temp->next = new1;       // Link next pointer
        new1->prev = temp;       // Link previous pointer
        new1->next = NULL;       // Set next as NULL
        new1->data = argv[1][i] - '0';   // Store digit

        temp = new1;             // Move temp forward
        *tail1 = new1;           // Update tail
    }

    int j = 0;                   // Index for second number
    if (argv[3][0] == '+' || argv[3][0] == '-') j = 1;   // Skip sign

    Dlist *new2 = (Dlist *)malloc(sizeof(Dlist));   // Allocate first node for second number
    if (!new2) return FAILURE;   // Check memory

    *head2 = *tail2 = new2;      // Initialize head and tail
    new2->prev = NULL;           // Previous is NULL
    new2->next = NULL;           // Next is NULL
    new2->data = argv[3][j++]- '0';   // Store first digit

    temp = *head2;               // Temporary pointer

    for (; argv[3][j]; j++) {    // Loop through remaining digits
        new2 = (Dlist *)malloc(sizeof(Dlist));   // Allocate node
        if (!new2) return FAILURE;   // Check memory

        temp->next = new2;       // Link next
        new2->prev = temp;       // Link prev
        new2->next = NULL;       // Set next NULL
        new2->data = argv[3][j] - '0';   // Store digit

        temp = new2;             // Move temp
        *tail2 = new2;           // Update tail
    }
    return SUCCESS;              // Return success
}

int compare_lists(Dlist *h1, Dlist *h2)   // Compare two numbers
{
    int len1 = 0, len2 = 0;      // Length counters
    Dlist *t1 = h1, *t2 = h2;    // Temporary pointers

    while (t1) { len1++; t1 = t1->next; }   // Count length of first
    while (t2) { len2++; t2 = t2->next; }   // Count length of second

    if (len1 > len2) return 1;   // If first bigger
    if (len1 < len2) return -1;  // If second bigger

    while (h1 && h2) {           // If same length compare digit by digit
        if (h1->data > h2->data) return 1;   // First greater
        if (h1->data < h2->data) return -1;  // Second greater
        h1 = h1->next;           // Move forward
        h2 = h2->next;           // Move forward
    }
    return 0;                    // If equal
}

void add_sign_node(Dlist **headR, Dlist **tailR)   // Add negative sign node
{
    if (*headR == NULL)     return;   // If list empty return

    Dlist *new = (Dlist *)malloc(sizeof(Dlist));   // Allocate new node
    new->data = -1;          // Store -1 to represent minus sign
    new->prev = NULL;        // Previous NULL
    new->next = *headR;      // Link to old head

    (*headR)->prev = new;    // Update old head prev
    *headR = new;            // Update head
}

void insert_front(Dlist **head, Dlist **tail, int data)   // Insert node at front
{
    Dlist *new = (Dlist *)malloc(sizeof(Dlist));   // Allocate new node
    new->data = data;        // Store data
    new->prev = NULL;        // Previous NULL
    new->next = *head;       // Link to old head

    if (*head)      (*head)->prev = new;   // If list not empty update prev
    else            *tail = new;           // If empty update tail

    *head = new;            // Update head
}

int is_zero(Dlist *head)    // Check if number is zero
{
    while (head) {          // Traverse list
        if (head->data != 0)    return 0;   // If any digit not zero
        head = head->next;      // Move forward
    }
    return 1;               // All digits zero
}

void copy_list(Dlist *src, Dlist **head, Dlist **tail)   // Copy one list to another
{
    *head = *tail = NULL;   // Initialize new list
    while (src) {           // Traverse source
        Dlist *new = malloc(sizeof(Dlist));   // Allocate node
        new->data = src->data;    // Copy data
        new->next = NULL;         // Next NULL
        new->prev = *tail;        // Link prev

        if (*tail)  (*tail)->next = new;   // Link next if exists
        else        *head = new;           // If first node

        *tail = new;         // Update tail
        src = src->next;     // Move source forward
    }
}

void increment_by_one(Dlist **head, Dlist **tail)   // Increase number by 1
{
    Dlist *oneH = NULL, *oneT = NULL;   // Create list for number 1
    insert_front(&oneH, &oneT, 1);      // Insert digit 1
    addition(head, tail, &oneH, &oneT, head, tail);   // Add 1 to number
}

void remove_leading_zeros(Dlist **head, Dlist **tail)   // Remove extra zeros at front
{
    while (*head && (*head)->data == 0 && *head != *tail) {   // While leading zero and not single node
        Dlist *temp = *head;   // Store current head
        *head = (*head)->next; // Move head forward
        (*head)->prev = NULL;  // Update prev pointer
        free(temp);            // Free old node
    }
}

void print_list(Dlist *headR)   // Print final result
{
    if (!headR) {               // If list empty
        printf("INFO : List is empty\n");   // Print message
        return;                 // Return
    }

    if (headR->data == -1) {    // If first node is sign
        printf("-");            // Print minus sign
        headR = headR->next;    // Move to next node
    }

    while (headR) {             // Traverse list
        printf("%d", headR->data);   // Print digit
        headR = headR->next;        // Move forward
    }
    printf("\n");               // New line
}
