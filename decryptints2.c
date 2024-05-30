/* For a number at index i, check the i (mod 8)th digit of the
number in hex. That digit (mod 7) will tell you which nibble index
the char in the secret message begins at (also in hex). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

    if (argc != 2) {
        perror("Incorrect number of arguments. Two arguments needed.");
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "r");

    unsigned int num, hex_to_check;
    int index = 0;
    char decrypted_char;

    while (fscanf(file, "%u", &num) == 1) {
        index %= 8;
        hex_to_check = (num >> (index * 4)) & 0xF;
        hex_to_check %= 7;
        decrypted_char = (char) ((num >> (hex_to_check * 4)) & 0xFF);
        printf("%c", decrypted_char);
        index++;
    }
    
    fclose(file);
    
    return 0;
}