#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdbool.h>
#include <stddef.h>

/* Representing a single product entry in the inventory. */
typedef enum {
    SURPLUS,
    SHORTAGE,
    MATCH
}InventoryStatus;

typedef struct {
    char id[20];
    char name[20];
    size_t counted;
    size_t expected;
    InventoryStatus status;
} Product;

/* Dynamic list of inventory products. "items" points to the array of Product entries. */
typedef struct {
    Product *items;
    size_t count;
    size_t capacity;
} ProductList;

/* Summary of the parsing results for the inventory files. */
typedef struct {
    size_t Matched;
    size_t Surplus;
    size_t Shortage;
    size_t malformed;
    size_t UnknownIDs;
} Report;

/* Clearer naming, while keeping the older function names for compatibility. */
bool parse_counted_file(Product *product, Report *report);
bool parse_expected_file(Product *product, Report *report);
bool product_list_append(ProductList *list, Product *product);
int load_expected_inventory(ProductList *list, Report *report);
void free_product_list(ProductList *list, Report *report);


#endif   

