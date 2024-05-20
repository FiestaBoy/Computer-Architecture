// Precondition: parameters should be a power of 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

typedef struct block {
    int* LRU; // Array to keep track of the least recently used element of the set
    int* words; // Array to store words (addresses)
    int* values; // Array to store values at the addresses
} block_t;

// Initialize a new block in cache
block_t* newBlock(int block_size) {
    block_t* ret = (block_t*)malloc(sizeof(block_t));
    ret->values = (int*)malloc(block_size * sizeof(int));
    ret->words = (int*)malloc(block_size * sizeof(int));
    ret->LRU = (int*)malloc(block_size * sizeof(int));
    for (int i = 0; i < block_size; i++) {
        ret->LRU[i] = 0;
        ret->words[i] = 0;
        ret->values[i] = 0;
    }
    return ret;
}

// Set up the structure of the cache
block_t*** populateCache(int blocks, int block_size, int block_associativity) {
    int row_num = blocks / block_associativity;
    block_t*** cache = (block_t***)malloc(row_num * sizeof(block_t**));
    for (int i = 0; i < row_num; i++) {
        cache[i] = (block_t**)malloc(block_associativity * sizeof(block_t*));
        for (int j = 0; j < block_associativity; j++) {
            cache[i][j] = newBlock(block_size);
        }
    }
    return cache;
}

// Find the index of the LRU element
int findLRU(int* arr, int block_size) {
    int min = INT_MAX;
    int index = -1;
    for (int i = 0; i < block_size; i++) {
        if (arr[i] < min) {
            min = arr[i];
            index = i;
        }
    }
    return index;
}

int main(int argc, char** argv) {
    int main_memory[65536] = {0};  // Initialize all main memory to 0
    int blocks, block_size, block_associativity;
    bool console_log = false; // Used to select whether to write to the console or to a file
    int LRU_tracker = 0;
    
    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = NULL;
    
    if (argc == 2) {
        console_log = true;
    } else if (argc == 3) {
        output_file = fopen(argv[2], "w");
    } else {
        perror("Wrong number of arguments.");
        exit(EXIT_FAILURE);
    }

    fscanf(input_file, "%d %d %d", &blocks, &block_size, &block_associativity);

    block_t*** cache = populateCache(blocks, block_size, block_associativity);
    
    char command[6];
    int address, items_read, value;
    int block_offset, block_index, set_index, tag;
    int block_offset_bits = (int)log2(block_size);
    int set_index_bits = (int)log2(blocks / block_associativity);
    // To extract the values of the variables from the address, I need to use bitmasking
    // Because the block number, block size and set-associativity are variable I used this expression below
    // A simple example: If block_offset_bits is 4 then the arithmetic would look like this:
    // 0b1 -> 0b10000 -> 0b1111, thus we get the bitmask and extract the indexes that we want
    int block_offset_bitmask = (1 << block_offset_bits) - 1;
    int set_index_bitmask = (1 << set_index_bits) - 1;

    while ((items_read = fscanf(input_file, "%5s %x", command, &address)) != EOF) {
        if (strcmp(command, "store") == 0) {
            items_read = fscanf(input_file, "%d", &value);
        }

        block_offset = address & block_offset_bitmask;
        set_index = (address >> block_offset_bits) & set_index_bitmask;
        tag = address >> (block_offset_bits + set_index_bits);

        block_index = -1;
        bool hit = false;
        // Iterating through parallel blocks and checking for cache hits
        for (int i = 0; i < block_associativity; i++) {
            if (cache[set_index][i]->words[block_offset] == address) {
                block_index = i;
                hit = true;
                break;
            }
        }

        if (hit) {
            if (strcmp(command, "load") == 0) {
                if (console_log) {
                    printf("load 0x%x hit %d\n", address, cache[set_index][block_index]->values[block_offset]);
                } else {
                    fprintf(output_file, "load 0x%x hit %d\n", address, cache[set_index][block_index]->values[block_offset]);
                }
            } else if (strcmp(command, "store") == 0) {
                if (console_log) {
                    printf("store 0x%x hit\n", address);
                } else {
                    fprintf(output_file, "store 0x%x hit\n", address);
                }
                cache[set_index][block_index]->values[block_offset] = value; // On a cache hit set the value at the address to the store value
            }
            cache[set_index][block_index]->LRU[block_offset] = LRU_tracker++;  // Update LRU
        } else {
            int lru_block = findLRU(cache[set_index][0]->LRU, block_size); // Get the index of the LRU element
            if (strcmp(command, "load") == 0) {
                if (console_log) {
                    printf("load 0x%x miss %d\n", address, cache[set_index][lru_block]->values[block_offset]);
                } else {
                    fprintf(output_file, "load 0x%x miss %d\n", address, cache[set_index][lru_block]->values[block_offset]);
                }
                // On a miss bring the block from the main memory to cache
                cache[set_index][lru_block]->values[block_offset] = main_memory[address];
                cache[set_index][lru_block]->words[block_offset] = address;
            } else if (strcmp(command, "store") == 0) {
                if (console_log) {
                    printf("store 0x%x miss\n", address);
                } else {
                    fprintf(output_file, "store 0x%x miss\n", address);
                }
                // Bring the block from the main memory to cache and update the main memory
                cache[set_index][lru_block]->values[block_offset] = value;
                cache[set_index][lru_block]->words[block_offset] = address;
                main_memory[address] = value;
            }
            cache[set_index][lru_block]->LRU[block_offset] = LRU_tracker++;  // Update LRU
        }
    }

    // Cleanup
    fclose(input_file);
    if (output_file) fclose(output_file);
    for (int i = 0; i < blocks / block_associativity; i++) {
        for (int j = 0; j < block_associativity; j++) {
            free(cache[i][j]->values);
            free(cache[i][j]->words);
            free(cache[i][j]->LRU);
            free(cache[i][j]);
        }
        free(cache[i]);
    }
    free(cache);

    printf("Simulation complete.\n");

    return 0;
}