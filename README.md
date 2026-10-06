# Inventory Reconciliation Engine

A command-line inventory reconciliation tool developed in **C**, designed to compare expected inventory records against physically counted stock and identify discrepancies.

This project focuses on practical systems programming, including file processing, dynamic memory management, structured data handling, input validation, and inventory reconciliation.

## Project Overview

Inventory reconciliation is the process of comparing recorded stock quantities with actual physical inventory.

The Inventory Reconciliation Engine processes two input files:

- **Expected Inventory:** Contains product IDs, names, and expected quantities.
- **Counted Inventory:** Contains product IDs and physically counted quantities.

The program compares these records, identifies discrepancies, and produces a summary report.

The goal is to handle inventory data reliably, including malformed records, unknown product IDs, and differences in stock quantities.

## Features

- **Inventory comparison:** Compare expected and counted quantities.
- **Discrepancy detection:** Identify shortages, surpluses, and exact matches.
- **Input validation:** Detect malformed records and invalid quantities.
- **Unknown product detection:** Identify counted products that do not exist in the expected inventory.
- **Dynamic memory allocation:** Manage an inventory list that can grow as records are processed.
- **Structured data management:** Use C structures and enumerations to organize inventory information.
- **Summary reporting:** Generate statistics describing reconciliation results.

## Technologies and Concepts

**Language:** C (C11)

**Development tools:** GCC, terminal, Git

**Programming concepts:**
- Structures (`struct`) and enumerations (`enum`)
- Pointers and memory management
- Dynamic arrays using `malloc()` and `realloc()`
- File I/O
- String parsing and numeric conversion
- Error handling and input validation
- Modular programming
- Standard C library functions

## Project Structure

```text
Inventory-Reconciliation-Engine/
│
├── main.c          # Program entry point
├── inventory.c     # Inventory processing implementation
├── inventory.h     # Data structures and function declarations
├── expected.txt    # Expected inventory data
├── counted.txt     # Physical inventory data
└── README.md        # Project documentation
```

## Input File Format

### Expected Inventory (`expected.txt`)

Each valid record follows:

```text
ProductID|ProductName|ExpectedQuantity
```

Example:

```text
P1001|Keyboard|50
P1002|Mouse|100
P1003|Monitor|25
P1004|USB Cable|200
```

### Counted Inventory (`counted.txt`)

Each valid record follows:

```text
ProductID|CountedQuantity
```

Example:

```text
P1001|45
P1002|110
P1003|25
P1004|180
X9999|15
BROKEN LINE
```

In this example:

- `P1001` has a shortage of 5 units.
- `P1002` has a surplus of 10 units.
- `P1003` is an exact match.
- `P1004` has a shortage of 20 units.
- `X9999` is an unknown product ID.
- `BROKEN LINE` is a malformed record.

## Compiling and Running

### Requirements

- GCC or another C11-compatible compiler
- A terminal
- Expected and counted inventory input files

### Compilation

```bash
gcc -Wall -Wextra -std=c11 main.c inventory.c -o inventory-check
```

### Execution

**Linux / macOS:**

```bash
./inventory-check
```

**Windows:**

```powershell
.\inventory-check.exe
```

The current implementation uses the inventory file paths configured inside the source code.

Ensure that both input files are available at the expected locations.

## Reconciliation Logic

For each product, the program compares its expected quantity against the physically counted quantity.

The difference is calculated as:

```text
Difference = Counted Quantity - Expected Quantity
```

Products can have one of three reconciliation statuses:

| Status | Condition |
|---|---|
| MATCH | Counted = Expected |
| SHORTAGE | Counted < Expected |
| SURPLUS | Counted > Expected |

Malformed records and unknown product IDs are tracked separately.

## Summary Report

The program provides the following statistics:

```text
===== INVENTORY REPORT =====
Malformed entries: ...
Surplus entries: ...
Exact matches: ...
Shortage entries: ...
Total matched products: ...
Unknown ID entries: ...
```

These statistics provide an overview of inventory accuracy and data quality.

## Implementation Approach

The project uses a dynamically allocated product list rather than a fixed-size array.

The main data structures are:

**Product**

Represents an individual inventory item, including its identifier, name, quantities, and reconciliation status.

**ProductList**

Manages the dynamically allocated collection of products using an item pointer, count, and capacity.

**Report**

Stores summary statistics, including matching products, shortages, surpluses, malformed records, and unknown IDs.

The program separates its functionality into individual operations responsible for parsing inventory files, maintaining the product list, and reporting results.

## Development and Learning Objectives

This project was developed as part of my ongoing effort to strengthen my C programming skills through practical problem-solving.

Rather than focusing only on language syntax, the development process emphasized:

1. Designing data structures before implementation.
2. Understanding pointer ownership and dynamic memory allocation.
3. Managing array capacity and preventing invalid memory access.
4. Separating parsing, storage, and reporting responsibilities.
5. Processing potentially invalid external data.
6. Writing modular, maintainable C code.
7. Building a functional command-line application from a problem specification.

Particular attention was given to understanding how dynamic data structures work internally and how errors can propagate through a C application.

## Author

**Alireza Jamshidian Tehrani**

B.Sc. Computer Science — University of Wuppertal

Interested in systems programming, C/C++ development, backend engineering, and software problem-solving.

**Project:** Inventory Reconciliation Engine  
**Language:** C  
**Category:** Systems Programming / CLI Application
