#include <stdio.h>
#include <stdlib.h>
#include "inventory.c"
#include "inventory.h"

int main(void) {
    ProductList list = {0};
    Report report = {0};

    parse_expected_file(&list, &report);
    parse_counted_file(&list, &report);

    printf("\n===== INVENTORY REPORT =====\n");

    printf("Malformed entries: %zu\n", report.malformed);
    printf("Surplus entries: %zu\n", report.Surplus);
    printf("Exact matches: %zu\n", report.ExactMatches);
    printf("Shortage entries: %zu\n", report.Shortage);
    printf("Total matched products: %zu\n", report.Matched);
    printf("Unknown ID entries: %zu\n", report.UnknownIDs);

    free_product_list(&list);

    return EXIT_SUCCESS;
}
