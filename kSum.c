#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int kSum(char* string, int k) {
    int len = strlen(string); // Get length of the string
    char sub_string[100] = ""; // Sets the max length of sub_string to 100, sub_string is each number seperated by a space, it resets every time a space or \0 is reached
    int sum = 0; // Initialize the sum of integers to 0
    for (int i = 0; i <= len; i++) { // for loop iterates until (including) \0
        if (*(string + i) != ' ' && *(string + i) != '\0') { // if statement to check if the char is not a space or the end of the string (\0)
            strncat(sub_string, (string + i), 1); // strncat() appends n characters from the string pointed to by src to the end of the string pointed to by dest
        } else { // in case of a space or \0
            int num;
            sscanf(sub_string, "%d", &num); // Reads sub_string, stores integer value in num
            sum += num;
            memset(sub_string, 0, sizeof(sub_string));  // Reset sub_string after the end of the integer is reached (' ' or \0), overwrites memory block with zeros
        }
    }

    int result = sum * k;
    
    return result; 
}

int main(int argc, char** argv) {

    if (argc != 3 || strlen(argv[1]) > 100) { // If argument number is not the wanted one or the string size too big throw error
        puts("Incorrect number of arguments or the size of the string is too large");
        perror("Error: ");
        return 1;
    }
    
    int k = atoi(argv[2]); // cast second argument to int
    int result = kSum(argv[1], k);
    printf("%d\n", result);
    
    return 0;
}