#include "inventory.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
/*
bool parse_counted_file(Product *product, Report *report);
bool parse_expected_file(Product *product, Report *report);
bool product_list_append(ProductList *list, Product *product);
int load_expected_inventory(ProductList *list, Report *report);
void free_product_list(ProductList *list, Report *report);
*/


int list_append(ProductList *list, Product *product) {
    if (list->count >= list->capacity) { // reallocate if the list is full
        size_t new_capacity = (list->capacity == 0) ? 1 : list->capacity * 2;// Double the capacity 
        Product *new_items = realloc(list->items, new_capacity * sizeof(Product)); // Reallocate memory for the items array
        if (new_items == NULL) {
            return -1; // Memory allocation failed
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count++] = *product; // Append the new product to the list and increment the count for the index of the next product to be added
    return 0; // Success
}
int product_list_find(const ProductList *list, const char *id) {
    for (size_t i = 0; i < list->count; i++) {
        if (strcmp(list->items[i].id, id) == 0) {
            return i;
        }
    }
    return -1; // Return -1 if the product is not found in the list
}
void free_product_list(ProductList *list)
{
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}
bool parse_expected_file(ProductList *list, Report *report){
    char input [10000];
    char quantitychar[8];
    FILE *file = fopen("expected.txt", "r");

        if (file == NULL) {
    fprintf(stderr, "Could not open expected.txt\n");
    return false;
}
    

    while( fgets(input, sizeof input, file) != NULL){
        Product temp = {0};
       
        int fields = sscanf(input, "%19[^|]|%19[^|]|%7[^|]", temp.id, temp.name, quantitychar);
        if(fields == 3){
            if(temp.id[0] == '\0'){
                report->malformed++;
                continue; // Skip this entry and continue with the next line
            }
            if(temp.name[0] == '\0'){
                report->malformed++;
                continue; // Skip this entry and continue with the next line
            }
            if(quantitychar[0] == '\0'){
                report->malformed++;
                continue;
            } else {
                
                char *endptr;
                errno = 0; // Reset errno 
                long value = strtol(quantitychar, &endptr, 10);
                if (errno == ERANGE) {
                    // Handle overflow or underflow error
                    
                    report->malformed++; 
                    continue; // Skip the rest of the loop for overflow/underflow errors
                } else if (endptr == quantitychar) {
                    // Handle case where no digits were found
                    report->malformed++;
                    continue; // Skip the rest of the loop for no digits found
                } else if (*endptr != '\0') {
                    // Handle case where there are extra characters after the number
                    
                    report->malformed++; 
                    continue; // Skip the rest of the loop for extra characters after the number
                } else {
                    
                    if(value < 0 || value > INT_MAX) {
                        report->malformed++; // Increment the malformed count for unmatched ID
                        continue; // Skip the rest of the loop for invalid value
                    }
                    else { 
                        int existing = product_list_find(list, temp.id);
                        if (existing != -1) {
                            report->malformed++;
                            continue;
                        }
                        // Successfully converted the string to a long integer
                        temp.expected = (int)value; // Assign the converted value to product->expected
                        if (list_append(list, &temp) == -1) {
                            fclose(file);
                            fprintf(stderr, "Failed to append product to list\n");
                            return false;
}
                    }
                }
            }
        }
        else{
            
            report->malformed++; //  case where the line does not have the expected format
            continue; // Skip the rest of the loop for lines with unexpected format
        }
    }
    fclose(file);
    return true;
}
    
bool parse_counted_file(ProductList *list,  Report *report){
    char input [10000];
    char quantitychar[8];
    FILE *file = fopen("counted.txt", "r");

        if (file == NULL) {
    fprintf(stderr, "Could not open counted.txt\n");
    return false;
}
    while( fgets(input, sizeof input, file) != NULL){
        Product temp = {0};
        int fields = sscanf(input, "%19[^|]|%7[^|]", temp.id, quantitychar);
        if(fields == 2){
            if(quantitychar[0] == '\0'){
                temp.counted = 0;
                report->malformed++; // Increment the malformed count for empty counted field
                continue; // Skip the rest of the loop for empty counted field
            } else {
                int index = product_list_find(list, temp.id);
                char *endptr;
                errno = 0; // Reset errno 
                long value = strtol(quantitychar, &endptr, 10);
                if (errno == ERANGE) {
                    // Handle overflow or underflow error
                    
                    report->malformed++;
                    continue; // Skip the rest of the loop for overflow/underflow errors
                } else if (endptr == quantitychar) {
                    // Handle case where no digits were found
                    report->malformed++; 
                    continue; // Skip the rest of the loop for invalid input
                } else if (*endptr != '\0') {
                    // Handle case where there are extra characters after the number
                    report->malformed++; 
                    continue; // Skip the rest of the loop for extra characters after the number
                } else {
                    if(value < 0 || value > INT_MAX) {
                        report->malformed++; // Increment the malformed count for unmatched ID
                        continue; // Skip the rest of the loop for negative values
                    }
                    if (index == -1) {
                        report->UnknownIDs++; // Increment the UnknownIDs count for unmatched ID
                        continue; // Skip the rest of the loop for unknown IDs
                    }
                    else {
                        // Successfully converted the string to a long integer
                        temp.counted = (int)value;

                        list->items[index].counted = temp.counted;
                        report->Matched++;

                        if (temp.counted == list->items[index].expected) {
                            report->ExactMatches++;
                            list->items[index].status = MATCH;
                        }
                        else if (temp.counted > list->items[index].expected) {
                            report->Surplus++;
                            list->items[index].status = SURPLUS;
                        }
                        else {
                            report->Shortage++;
                            list->items[index].status = SHORTAGE;
                        }
                    }
                    
                }
            }
        }
        else{
            // Handle the case where the line does not have the expected format
            report->malformed++;
        }
    }
    fclose(file);
    return true;
}
