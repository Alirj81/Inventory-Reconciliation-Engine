#include "inventory.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
bool parse_nonnegative_int(const char *text, int *result)
{
    if (text == NULL || result == NULL) {
        return false;
    }

    if (text[0] == '\0') {
        return false;
    }

    char *endptr;
    errno = 0;

    long value = strtol(text, &endptr, 10);

    // continue here
}

void parsecountedfile(Product *product) {
    // Implementation for parsing the counted file and populating the inventory array
    char input[10000];
    char quantitychar[8];
    FILE *file = fopen("counted.txt", "r");
    while (fgets(input, sizeof input, file) != NULL) {
        int fields = sscanf(input, "%30[^|]|%8[^|]", product->id, quantitychar);
        if (fields == 2) {
            if(quantitychar[0] == '\0'){
                product->quantity = 0;
            } 
            char *endptr;
            errno = 0; // Reset errno before the call
            product->quantity = strtol(quantitychar, &endptr, 10);
            if (errno == ERANGE) {
                // Handle overflow or underflow error
                product->quantity = 0; // Set to a default value or handle as needed
            } else if (endptr == quantitychar) {
                // Handle case where no digits were found
                product->quantity = 0; // Set to a default value or handle as needed
            } else if (*endptr != '\0') {
                // Handle case where there are extra characters after the number
                product->quantity = 0; // Set to a default value or handle as needed
            } else {
                // Successfully converted the string to a long integer
                product->quantity = strtol(quantitychar, NULL, 10);
            }
            
        }
    }
    fclose(file);
}

void parseexpectedfile(Inventory *inventory, Report *report) {
    // Implementation for parsing the expected file and populating the inventory array
    char input[10000];
    char expectedchar[8];
        FILE *file = fopen("expected.txt", "r");
    while (fgets(input, sizeof input, file) != NULL) {
        int fields = sscanf(input, "%30[^|]|%30[^|]| %8[^|]", inventory->id, inventory->name, expectedchar);
        if (fields == 3) {
            if(expectedchar[0] == '\0'){
                inventory->expected = 0;
                inventory->status = MALFORMED;
                report->malformed++;
            }
            char *endptr;
            errno = 0; // Reset errno before the call
            inventory->expected = strtol(expectedchar, &endptr, 10);
            if (errno == ERANGE) {
                // Handle overflow or underflow error
                inventory->expected = 0; // Set to a default value or handle as needed
            } else if (endptr == expectedchar) {
                // Handle case where no digits were found
                inventory->expected = 0; // Set to a default value or handle as needed
            } else if (*endptr != '\0') {
                // Handle case where there are extra characters after the number
                inventory->expected = 0; // Set to a default value or handle as needed
            } else {
                // Successfully converted the string to a long integer
                inventory->expected = strtol(expectedchar, &endptr, 10);
            }
        }
        }
        fclose(file);
}

void search_inventory(Inventory *inventory, int size, char *id, Inventory *result) {
    // Implementation for searching the inventory array for a specific ID
}

void store_products(Product *products, int size) {
    // Implementation for storing the inventory data to a file
}

int inventory_search(Inventory *inventory, int size, char *id) {
    // Implementation for checking the inventory data for consistency
    return -1; // Placeholder return value
}
