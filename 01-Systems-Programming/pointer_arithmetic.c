/*
 * PROJECT: Pointer Arithmetic
 * OBJECTIVE: Prove that arrays are just pointers to sequential memory.
 */

#include <stdio.h>

int main() {
    // 1. Create an array of 5 integers
    // In memory, this is 20 bytes (5 * 4 bytes) in a straight line.
    int stack_of_numbers[5] = {10, 20, 30, 40, 50};

    // 2. Create a pointer to the start of the array
    // Notice: The name of the array IS the address of the first element!
    int *ptr = stack_of_numbers;

    printf("--- The Physics of Arrays ---\n");
    printf("Base Address: %p\n\n", ptr);

    // 3. Iterate using POINTER MATH, not brackets
    for (int i = 0; i < 5; i++) {
        // Calculate the address of the current element
        // (ptr + i) moves the pointer forward by i * 4 bytes
        int *current_address = ptr + i;
        
        // Go inside that address to get the value
        int value = *current_address; // Same as stack_of_numbers[i]

        printf("Slot %d: Address %p | Value: %d\n", i, current_address, value);
    }

    return 0;
}