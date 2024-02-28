#include <stdio.h>

int main(int argc, char** argv) {
    float var1, var2;

    sscanf(argv[1], "%f", &var1);
    sscanf(argv[2], "%f", &var2);

    float multiplied = var1 * var2;

    printf("Multiplied numbers: %f", multiplied);
    return 0;
}