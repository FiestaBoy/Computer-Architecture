#include <stdio.h>

int main(int argc, char** argv) {
    int num;

    sscanf(argv[1], "%x", &num);

    num >> 2;

    printf("%x", num);



    return 0;
}