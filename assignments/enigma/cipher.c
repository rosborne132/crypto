#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Alphabet and rotors
#define alphabet "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ROTORS { \
    "BDFHJLCPRTXVZNYEIWGAKMUSQO", /* Fast rotor */ \
    "AJDKSIRUXBLHWTMCQGZNPYFVOE", /* Medium rotor */ \
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ", /* Slow rotor */ \
    "IXUHFEZDAOMTKQJWNSRLCYPBVG"  /* Reflector */ \
}

/**
 * @brief Finds the index of the first occurrence of a character in a string.
 *
 * This function searches for the first occurrence of the character `c` in the
 * string `str` and returns its index. If the character is not found, the
 * function returns -1.
 *
 * @param str The string to be searched.
 * @param c The character to find in the string.
 * @return The index of the first occurrence of the character in the string,
 *         or -1 if the character is not found.
 */
int find_index(const char *str, char c) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) return i;
    }

    return -1; // Character not found
}

/**
 * Encrypts a single character using the provided rotor.
 *
 * @param rotor A string representing the rotor used for encryption.
 * @param c The character to be encrypted.
 * @return The encrypted character.
 */
char encrypt_char(const char *rotor, char c) {
    int index = find_index(alphabet, c);
    return rotor[index];
}

/**
 * Decrypts a single character using the provided rotor.
 *
 * This function takes a rotor and a character, finds the index of the character
 * in the rotor, and returns the corresponding character from the alphabet.
 *
 * @param rotor A pointer to a character array representing the rotor.
 * @param c The character to be decrypted.
 * @return The decrypted character from the alphabet.
 */
char decrypt_char(const char *rotor, char c) {
    int index = find_index(rotor, c);
    return alphabet[index];
}

/**
 * @brief Processes a given input string using a specified rotor and processing function.
 *
 * This function takes an input string, a rotor string, and a processing function pointer.
 * It processes each character of the input string using the provided processing function
 * and rotor, and returns the resulting processed string.
 *
 * @param input The input string to be processed.
 * @param rotor The rotor string used in the processing function.
 * @param process A function pointer to the processing function that takes the rotor and a character from the input string.
 * @return A newly allocated string containing the processed characters. The caller is responsible for freeing this memory.
 */
char* process_string(const char *input, const char *rotor, char (*process)(const char *, char)) {
    char *output = malloc(strlen(input + 1) * sizeof(char));

    for (int i = 0; i < strlen(input); i++) {
        output[i] = process(rotor, input[i]);
    }

    output[strlen(input)] = '\0';

    return output;
}

int main() {
    // Initialize variables
    const char *rotors[] = ROTORS;
    const char *rotor = rotors[0];
    char input[256];

    // Get user input
    printf("Enter a string to encrypt (uppercase letters only): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove trailing newline

    char *encrypted = process_string(input, rotor, encrypt_char);
    char *decrypted = process_string(encrypted, rotor, decrypt_char);

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    // Check if decryption was successful
    if (strcmp(input, decrypted) == 0) printf("Decryption successful!\n");
    else printf("Decryption failed!\n");

    return 0;
}