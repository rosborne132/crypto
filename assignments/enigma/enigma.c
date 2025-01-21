#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A 'A'  // ASCII value of 'A'
#define NC 26  // Number of characters in the alphabet

const char *rotors[] = {
  "BDFHJLCPRTXVZNYEIWGAKMUSQO", // fast
  "AJDKSIRUXBLHWTMCQGZNPYFVOE", // medium
  "EKMFLGDQVZNTOWYHXUSPAIBRCJ", // slow
  "IXUHFEZDAOMTKQJWNSRLCYPBVG"  // reflector
};

/**
 * Applies the rotor transformation to a given character.
 *
 * @param c The character to be transformed.
 * @param rotor A pointer to the rotor array used for transformation.
 * @return The transformed character.
 */
char rapply(char c, const char *rotor) {
  // Return the character at the calculated index in the rotor array 'rotor'
  return rotor[c - A];
}


/**
 * Inverts a given rotor configuration.
 *
 * @param rotor The input rotor configuration as a string.
 * @return A newly allocated string containing the inverted rotor configuration.
 */
char* invert(const char *rotor) {
  // Allocate memory for the inverted rotor string
  char *inverted = malloc((NC + 1) * sizeof(char));

  // Populate the inverted rotor by mapping each character in the rotor
  // to its corresponding position in the alphabet
  for (int i = 0; i < NC; i++) {
      inverted[rotor[i] - A] = i + A;
  }

  inverted[NC] = '\0';

  return inverted;
}

/**
 * Extends the given rotor configuration by adding inverted rotors.
 *
 * @param original An array of strings representing the original rotor configuration.
 * @return A newly allocated array of strings containing the extended rotor configuration.
 *
 * @note The original rotor configuration is assumed to contain 4 rotors.
 *       The extended rotor configuration will contain 7 rotors, including the inverted rotors.
 */
const char** extend_rotors(const char **original) {
  // Allocate memory for the extended rotor configuration
  const char **extended_rotors = malloc(7 * sizeof(char *));

  // Copy the original rotors to the extended rotor configuration
  memcpy(extended_rotors, original, 4 * sizeof(char *));

  // Create inverted rotors and add them to the extended rotor configuration
  for (int i = 2; i >= 0; i--) {
    extended_rotors[6 - i] = invert(original[i]);
  }

  return extended_rotors;
}

/**
 * Shifts a character by a given number of positions in the alphabet.
 *
 * @param c The character to be shifted.
 * @param n The number of positions to shift the character.
 * @return The shifted character.
 */
char nshift(char c, int n) {
  // Calculate the zero-based index of the character 'c' in the alphabet
  int index = c - A;
  // Apply the shift, ensuring it wraps around using modulo operation
  int shifted_index = (index + n + NC) % NC;

  // Convert the zero-based index back to a character
  return shifted_index + A;
}

/**
 * Computes the shifts for the rotors based on the input position and rotor number.
 *
 * @param p The current position or step count.
 * @param n The rotor number.
 * @return The computed shift value for the specified rotor.
 */
int shifts(int p, int n) {
  switch (n) {
    case 0: return p % NC;                  // Fast rotor
    case 1: return (p / NC) % NC;           // Medium rotor
    case 2: return (p / (NC * NC)) % NC;    // Slow rotor
    case 4: return (p / (NC * NC)) % NC;    // Reverse slow rotor
    case 5: return (p / NC) % NC;           // Reverse medium rotor
    case 6: return p % NC;                  // Reverse fast rotor
    default: return 0;                      // Reflector does not shift
  }
}


/**
 * Applies a shift and rotor transformation to a character.
 *
 * @param c The character to be transformed.
 * @param n The number of positions to shift the character.
 * @param rotor The rotor configuration used for transformation.
 * @return The transformed character.
 */
char shiply(char c, int n, const char *rotor) {
  // Shift the character forward by 'n' positions
  char shifted_char = nshift(c, n);

  // Apply the rotor transformation to the shifted character
  char transformed_char = rapply(shifted_char, rotor);

  // Shift the transformed character backward by 'n' positions
  return nshift(transformed_char, -n);
}

/**
 * Encrypts a single letter using a series of transformations.
 *
 * @param c The character to be encrypted.
 * @param l The initial shift value.
 * @param r An array of strings representing the transformation rules.
 * @return The encrypted character.
 */
char letter(char c, int l, const char **r) {
  // Iterate over the rotors and apply the transformations
  for (int i = 0; i < 7; i++) {
    int shift_val = shifts(l, i);

    // Apply the shift and rotor transformation to the character
    c = shiply(c, shift_val, r[i]);
  }

  return c;
}

/**
 * Encrypts a string using the Enigma machine simulation.
 *
 * @param input The input string to be encrypted.
 * @param rotors An array of strings representing the rotor configurations.
 * @return A newly allocated string containing the encrypted output.
 */
char* enigma(const char *input, const char **rotors) {
  int length = strlen(input);

  // Allocate memory for the output string
  char *output = malloc((length + 1) * sizeof(char));

  // Iterate over the input string and encrypt each character
  for (int i = 0; i < length; i++) {
    output[i] = letter(input[i], i + 1, rotors);
  }

  output[length] = '\0';

  return output;
}

/**
 * @file enigma.c
 * @brief Main entry point for the Enigma encryption program.
 *
 * This program simulates the Enigma machine encryption process.
 * It takes an input string from the command line arguments,
 * extends the rotor configuration, and then encrypts the input string.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 *             argv[1] should contain the input string to be encrypted.
 *
 * @return Returns 0 upon successful completion.
 */
int main(int argc, char *argv[]) {
  // Create the extended rotor configuration
  const char **extended_rotors = extend_rotors(rotors);

  // Encrypt the input string
  char *output = enigma(argv[1], extended_rotors);

  printf("%s\n", output);

  return 0;
}
