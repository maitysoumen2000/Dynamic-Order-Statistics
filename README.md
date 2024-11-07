# Order-Statistics Tree Implementation in C

This project implements a Red-Black Tree (RBT) with features for insertion, deletion, searching, in-order and pre-order traversal, and finding the k-th smallest element in the tree.

## Features

- **Red-Black Tree (RBT)**
  - Self-balancing binary search tree with efficient insertion, deletion, and search operations.
  - Supports finding the k-th smallest element and performing both in-order and pre-order traversals.
  
- **Order Statistics (k-th Smallest Element)**
  - Implements an order statistics function to find the k-th smallest element in the tree.
  
- **Timing Measurement (optional)**
  - This implementation does not measure time, but you can add timing functions if needed.

## Code Structure

### Data Structure

The Red-Black Tree uses nodes with a `color` property to maintain balance and an `int size` attribute for order statistics calculations.

```c
typedef enum { red, black } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    int size;
} Node;
