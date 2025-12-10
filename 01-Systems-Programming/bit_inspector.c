/*
 * PROJECT: Sovereign Bit Inspector
 * AUTHOR: Andrew Mason
 * DATE: 2025-12-09
 *
 * SPECIFICATION (The "What")
 * 1. The tool accepts an integer input.
 * 2. It prints the Decimal, Hexadecimal, and Binary representation.
 * 3. It MUST handle negative numbers correctly (showing Two's Complement).
 * 4. It must verify the conversion using Unit Tests before running.
 *
 * ARCHITECTURE (The "How")
 * - Input: Hardcoded variable (for now) or Command Line Argument.
 * - Logic: Use Bitwise AND (&) and Bitwise SHIFT (>>) to extract bits.
 * - QA: Assert that the binary string matches expected patterns for known numbers.
 */

#include <stdio.h>
#include <stdlib.h> 
#include <assert.h> // For unit testing.
#include <string.h> // For string comparison in tests
#include <limits.h> // Contains INT_MAX (The 2 billion limit)
#include <errno.h> // For detecting overflow errors.

// --- LOGIC: The Converter ---
// This function prints the 32 bits of an integer.
// It does NOT use a string buffer (yet). it just prints to stdout.
void print_binary(int n) {
    printf("Binary:      ");

    //We loop 31 times down to 0 (32 bits total)
    for (int i = 31; i >= 0; i--) {
        //1. Shift the number 'i' spots to the right.
        // If n is 1100, and i is 3, shifting right 3 times leaves 1.
        int k = n >> i;

        //2. Check the box with the Sensor (Mask)
        if (k & 1)
            printf("1");
        else
            printf("0");

        //Format: Add a space every 4 bits for readibility (Nibbles)
        if (i % 4 == 0) printf(" ");
    }
    printf("\n");
}

void print_hex(int n) {
    
    //%X is the standard format specifier for Hexadecimal
    //%#X adds the "0X" prefix automatically.

    printf("Hex:      %#X\n", n);
    printf("Dec:      %d\n", n);
}

//--- UNIT TEST HARNESS ---
// We test the math, not the printing.
void run_tests(){
    printf("[QA] Running System Checks... \n");

    int test_val = 5; //Binary: ...0000 0101

    //TEST 1: Verify Bitwise Logic manually.
    // 5 >> 1 is 5 (0101). (5 & 1) should be 1.
    assert((test_val >> 0 & 1) == 1);

    // 5 >> 1 is 2 (0010). (2 & 1) should be 0.
    assert((test_val >> 1 & 1) == 0);

    //5 >> 2 is 1 (0001). (1 & 1) should be 1.
    assert((test_val >> 2 & 1) == 1);

    //TEST 2: Verify Negative Number ( Two's Compliment)
    // -1 is all 1s: 1111...1111
    int neg_val = -1;
    assert((neg_val >> 0 & 1) == 1);
    assert((neg_val >> 31 & 1) == 1); // The "Sign Bit" must be 1.

    printf("[QA] All Bitwise Operations Nominal. \n\n");
}

// --- DRIVER: The Main Entry Point ---
int main(int argc, char *argv[]) {
    //1. Run QA
    run_tests();



    //2. Check Input Existence
        if (argc < 2) {
            printf("ERROR: Missing input. \n");
            printf("Usage: ./bit_inspector <integer>\n");
            return 1;
        }

    //3. SAFE PARSING ( The "Senior Dev" way)
    char *input_string = argv[1];
    char *end_pointer;

    errno = 0; // Reset the error flag.
    long parsed_value = strtol(input_string, &end_pointer, 10);

    //CHECK A: Did the user type letters or decimals? 
    if(*end_pointer != '\0'){
        printf("ERROR: Invalid Input. Integers only.\n");
        printf("Detected invalid character: '%c'\n", *end_pointer);
        return 1;
    }

    //CHECK B: Integer Overflow?
    if((errno == ERANGE) || (parsed_value > INT_MAX) || (parsed_value < INT_MIN)){
        printf("ERROR: Integer Overflow. \n");
        printf("This system is 32-bit. Limit is +/- %d\n", INT_MAX);
        return 1;
    }

    //4. Run Application
     int number_to_inspect = (int)parsed_value;
    printf("--- Sovereign Bit Inspector ---\n");
    printf("Inspecting: %d\n", number_to_inspect);
    print_hex(number_to_inspect);
    print_binary(number_to_inspect);

    return 0;
}