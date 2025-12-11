/*
 * PROJECT: Pointer Basics
 * OBJECTIVE: Visualize the physical memory address of variables.
 */

#include <stdio.h>

int main() {
    // 1. Create a variable (The House)
    int number = 42;

    // 2. Create a Pointer (The Address on a piece of paper)
    // 'int *' means "This variable holds an address to an int"
    int *address_of_number = &number;

    printf("--- The Reality of Variables ---\n");
    
    // Print the VALUE (What is inside the box?)
    printf("Value of number:    %d\n", number);

    // Print the ADDRESS (Where is the box?)
    // %p is the format specifier for "Pointer"
    printf("Address of number:  %p\n", address_of_number);
    
    // Prove they are linked:
    // This prints the address directly using the & operator
    printf("Direct calculation: %p\n", &number);

    return 0;
}