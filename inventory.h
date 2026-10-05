#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdbool.h>
#include <stddef.h>

/* Represents a single product entry in the inventory. */
typedef enum {
    SURPLUS,
    SHORTAGE,
    MATCH
} InventoryStatus;

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
    size_t ExactMatches;
    size_t Surplus;
    size_t Shortage;
    size_t malformed;
    size_t UnknownIDs;
} Report;

/* Clearer naming, while keeping the older function names for compatibility. */
bool parse_counted_file(ProductList *list, Report *report);
bool parse_expected_file(ProductList *list, Report *report);
int list_append(ProductList *list, Product *product);
bool list_modify(ProductList *list, Product *product);
int product_list_find(const ProductList *list, const char *id); // const because the function does not modify the list
void free_product_list(ProductList *list);


#endif // INVENTORY_H   

