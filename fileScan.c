#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        perror("Expected 2 arguments: ");
        return EXIT_FAILURE;
    }

    FILE* file;
    file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("File did not open: ");
        return EXIT_FAILURE;
    }

    char string_buffer[1000];
    int count = 0;
    while (fscanf(file, "%[^\n]\n", string_buffer) != EOF) {
        char* cur_token = strtok(string_buffer, " ");
        while (cur_token != NULL) {
            int i = 0;
            while (cur_token[i] != "\0") {
                if(cur_token[i] < 96) {
                    cur_token[i] -= 32;
                }
                i++;
            }
            cur_token = strtok(NULL, " ");
        }
    }

    printf("%d\n", count);

    fclose(file);

    return 0;
}