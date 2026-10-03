#ifndef INVENTORY_H
#define INVENTORY_H
typedef struct {
    char *id;
    char *name;
    int quantity;
} Product;
typedef struct{
    char *id;
    char *name;
    unsigned int counted;
    unsigned int expected;
    int difference;
    enum {SURPLUS, SHORTAGE, MATCH} status;
} Inventory;
typedef struct{
    int Matched;
    int Surplus;
    int Shortage;
    int UnknownIDs;
}report;
void parsecountedfile(char *filename, Inventory **inventory, int *size);
void parseexpectedfile(char *filename, Inventory **inventory, int *size);
void generate_report(Inventory *inventory, int size, report *report);

#endif 
