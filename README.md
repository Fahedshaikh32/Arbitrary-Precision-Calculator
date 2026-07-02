# Arbitrary Precision Calculator

A high-performance **Arbitrary Precision Calculator (APC)** implemented in **C**, designed to perform arithmetic on integers of virtually unlimited length.

Unlike native C integer types (`int`, `long`, `long long`), which are constrained by fixed memory sizes, this implementation stores every digit in a **Doubly Linked List**, allowing calculations on numbers containing hundreds or even thousands of digits.

The project demonstrates low-level data structure design, modular software architecture, memory management, and arithmetic algorithm implementation without relying on external libraries.

---

## Features

* Addition of arbitrarily large signed integers
* Subtraction with borrow propagation
* Multiplication using partial-product accumulation
* Integer division using repeated subtraction
* Support for positive and negative operands
* Automatic carry and borrow handling
* Removal of leading zeros
* Command-line interface
* Modular implementation
* Input validation with error handling

---

## Why Arbitrary Precision?

Standard C integer types have limited storage capacity.

| Data Type | Typical Size |
| --------- | -----------: |
| int       |       32-bit |
| long long |       64-bit |

For example,

```
999999999999999999999999999999
```

cannot be stored using built-in data types.

This project overcomes that limitation by representing every digit as an individual node inside a Doubly Linked List.

```
98765432109876543210

↓

+-----+    +-----+    +-----+    +-----+
|  9  |<-> |  8  |<-> |  7  |<-> | ... |
+-----+    +-----+    +-----+    +-----+
```

The size of the integer is therefore limited only by the available system memory.

---

## Project Architecture

```
.
├── main.c                 # Command-line interface
├── apc.h                  # Data structures & function declarations
├── apc_validation.c       # Input validation
├── apc_utils.c            # Linked-list helper functions
├── apc_operation.c        # Addition, subtraction, multiplication
├── apc_division.c         # Division algorithm
├── Makefile               # Build configuration
└── README.md
```

---

## Internal Design

### Number Representation

Each decimal digit is stored in one node of a Doubly Linked List.

```
123456

Head
 ↓

+---+---+    +---+---+    +---+---+
| 1 | • |<-> | 2 | • |<-> | 3 | • | ...
+---+---+    +---+---+    +---+---+

                                ↑
                              Tail
```

Traversing from the tail enables arithmetic exactly as performed manually.

---

## Arithmetic Algorithms

### Addition

* Traverse both operands from least significant digit
* Add corresponding digits
* Propagate carry
* Insert result at the front of the result list

**Time Complexity**

```
O(max(n, m))
```

---

### Subtraction

* Compare operands
* Traverse from least significant digit
* Handle borrow propagation
* Remove leading zeros

**Time Complexity**

```
O(max(n, m))
```

---

### Multiplication

Implements the traditional long multiplication algorithm.

For every digit in the multiplier:

* Multiply every digit of the multiplicand
* Generate partial products
* Shift according to place value
* Accumulate partial results

**Time Complexity**

```
O(n × m)
```

---

### Division

Performs integer division using repeated subtraction.

Algorithm:

1. Compare dividend and divisor
2. Repeatedly subtract divisor
3. Increment quotient
4. Continue until dividend becomes smaller than divisor

**Time Complexity**

```
O(quotient × n)
```

---

## Building

Compile using GCC.

```bash
make
```

or

```bash
gcc *.c -o apc
```

---

## Usage

```
./apc <operand1> <operator> <operand2>
```

Example

```bash
./apc 10 + 20
30

./apc 100 - 45
55

./apc 25 '*' 40
1000

./apc 500 '/' 25
20

./apc -500 + 100
-400
```

---

## Input Validation

The application validates:

* Invalid operators
* Non-numeric operands
* Division by zero
* Incorrect command-line arguments
* Signed integers (+/-)

---

## Technologies Used

* C (C17 compatible)
* GCC
* Doubly Linked List
* Dynamic Memory Allocation
* Modular Programming
* Command-Line Interface

---

## Learning Outcomes

This project demonstrates practical understanding of:

* Data Structures
* Pointer manipulation
* Dynamic memory management
* Large integer arithmetic
* Linked list traversal
* Algorithm design
* Modular software architecture
* Command-line application development
* Defensive programming
* Error handling

---

## Future Improvements

* Faster division algorithm
* Karatsuba multiplication
* Modulus operation
* Exponentiation
* Arbitrary precision floating-point arithmetic
* Unit testing
* Continuous Integration (GitHub Actions)
* Memory leak detection using Valgrind
* Performance benchmarking

---

## Author

**Fahed Shaikh**

Electronics & Telecommunication Engineer

Embedded Systems | C Programming | Data Structures | Linux | Firmware Development
