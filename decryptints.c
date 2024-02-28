#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

    if (argc != 2) {
        perror("Exactly two arguments needed");
        return EXIT_FAILURE;
    }
    
    FILE* file = fopen(argv[1], "r");

    unsigned int num;
    int count = 0;

    // While loop to iterate through each unsigned integer in the file
    while (fscanf(file, "%u", &num) == 1) {

        // Getting the number of wanted byte
        count %= 4;
        // Shifting by 8 bits (1 byte) times the number (1-4) that count is, & operation is necessary to only select the first 8 little-endian
        // bits. OxFF is 11111111, so when it ands with an unsigned integer (which is 24 bits long after the shift), it only keeps the first ones the same
        char cur_char = (char) (num >> (8 * count) & 0xFF);
        printf("%c", cur_char);
        count++;
    }

    fclose(file);

    return 0;
}