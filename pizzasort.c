#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.14159265

typedef struct Pizza {
    char name[51];
    float CPSI;
} Pizza_t;

Pizza_t* newPizza(char* name, float CPSI) {
    Pizza_t* ret = malloc(sizeof(Pizza_t));
    strcpy(ret->name, name);
    ret->CPSI = CPSI;
    return ret;
}

// pizzaCount will be updated inside of this function so I can use it for printing and sorting the pizzas
Pizza_t** createPizzaMenu(char* file_name, int* pizzaCount) {
    FILE* file = fopen(file_name, "r");

    if (file == NULL) {
        perror("File did not open");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    char ch;

    // Iterating through every single character in the file, every time '\n' is reached, the pizza counter goes up
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }

    // Here pizza counter goes up by one because the while loop statement misses the last line as it reaches the end of the file and leaves the last line uncounted
    // This caused me the most pain, almost 2 hours worth of debugging time, this mistake seems more obvious now than it was to me before
    count++;

    rewind(file);

    Pizza_t** pizzas = malloc(sizeof(Pizza_t*) * count);

    if (pizzas == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // For loop iterating through every line of the file and then creating pizza structs in pizzas pointer array
    for (int i = 0; i < count; i++) {
        float cost;
        float di;
        char name_buffer[51];

        fscanf(file, "%s %f %f\n", name_buffer, &cost, &di);

        float CPSI = cost / (PI * (di / 2) * (di / 2));


        pizzas[i] = newPizza(name_buffer, CPSI);
    }

    // Updating pizzaCount to count so that it can be used in sorting and printing
    *pizzaCount = count;

    fclose(file);

    return pizzas;
}

// Simple bubble sort
void sortPizzas(Pizza_t** pizzas, int num_of_pizzas) {
    for (int i = 0; i < num_of_pizzas - 1; i++) {
        for (int j = 0; j < num_of_pizzas - i - 1; j++) {
            if(pizzas[j]->CPSI > pizzas[j + 1]->CPSI) {
                Pizza_t* temp = pizzas[j];
                pizzas[j] = pizzas[j + 1];
                pizzas[j + 1] = temp;
            } 
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        perror("Two arguments required");
        return EXIT_FAILURE;
    }
    
    int num_of_pizzas;
    Pizza_t** pizza_menu = createPizzaMenu(argv[1], &num_of_pizzas);
    sortPizzas(pizza_menu, num_of_pizzas);

    // Printing sorted pizzas
    for (int i = 0; i < num_of_pizzas; i++) {
        printf("%s %0.4f\n", pizza_menu[i]->name, pizza_menu[i]->CPSI);
    }

    for (int i = 0; i < num_of_pizzas; i++) {
        free(pizza_menu[i]);
    }

    
    return 0;
}