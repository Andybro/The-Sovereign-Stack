#include <stdio.h>
#include <stdlib.h> // For strtol

// PROTOTYPES
// Note: We pass char* because a string is just a pointer to the first char.
void encrypt_message(char* ptr, int key);
void decrypt_message(char* ptr, int key);

int main() {
    // 1. Allocate space for the message on the STACK
    // We create a buffer of 256 bytes.
    char message[256]; 
    char key_input[16];
    int key;

    // 2. Get the Message
    printf("--- THE SOVEREIGN CIPHER ---\n");
    printf("Enter your secret message: ");
    
    // fgets reads up to sizeof(message) from stdin (keyboard)
    if (fgets(message, sizeof(message), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // 3. Get the Key
    printf("Enter shift key (number): ");
    fgets(key_input, sizeof(key_input), stdin);
    // Use your strtol skills here to convert key_input to an int
    key = (int)strtol(key_input, NULL, 10);

    // 4. Encrypt
    printf("\nEncrypting...\n");
    encrypt_message(message, key);
    printf("Encrypted: %s", message);

    // 5. Decrypt
    printf("Decrypting...\n");
    decrypt_message(message, key);
    printf("Decrypted: %s", message);

    return 0;
}

// YOUR MISSION IS HERE
void encrypt_message(char* ptr, int key) {
    // TODO: 
    // 1. Create a loop that runs until *ptr is equal to '\0' (Null Terminator).
    // 2. Inside the loop, take the value at *ptr and add the key to it.
    //    Example: *ptr = *ptr + key;
    // 3. Increment the pointer to move to the next memory address.
    // NOTE: Be careful not to shift the '\n' (newline) or '\0' at the end!
    //       You might need an if statement inside the loop.
}

void decrypt_message(char* ptr, int key) {
    // TODO:
    // Same logic, but subtract the key.
}

//--- UNIT TEST HARNESS ---
// We will test the 