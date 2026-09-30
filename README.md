# Data Structures — C++

Lab work and assignments from my Data Structures course at COMSATS University Islamabad, Attock Campus. Implemented in C++ from scratch — no STL containers.

## Topics Covered

### Array Lists (Week 1 + Assignment 01)

Custom array-backed list implemented as a struct with manual bounds checking.

| **Operation**                  | **Description**                      |
| ------------------------------ | ------------------------------------ |
| `insertEnd`                    | Append to the back                   |
| `insertStart`                  | Prepend, shifting all elements right |
| `insertAfter` / `insertBefore` | Insert relative to a target value    |
| `deleteEnd` / `deleteStart`    | Remove from either end               |
| `deleteSpecific`               | Remove by value                      |
| `linearSearch`                 | Find index of a target element       |

**Assignment 01** extends this with raw pointer traversal to compute:

* Min, max, sum, median
* General average vs. special average (min + median + max / 3)
* Closest value to the special average
* Final score combining all three distances
* Deletion of the closest element and re-insertion of the rounded special average

### Singly Linked Lists (Week 2)

| **File**    | **What it does**                                                                   |
| ----------- | ---------------------------------------------------------------------------------- |
| `task1.cpp` | Build a linked list; display forward, reverse (recursive), and reverse (iterative) |
| `task2.cpp` | Build two separate linked lists; merge them into a third                           |
| `task3.cpp` | Search a linked list for all positions where a value occurs; count occurrences     |

### Doubly Linked Lists (Week 3)

Implemented doubly linked list operations using manual pointer manipulation without STL containers.

| **Task**    | **What it does**                                                                                  |
| ----------- | ------------------------------------------------------------------------------------------------- |
| `task1.cpp` | Reverse the order of a doubly linked list by swapping the `prev` and `next` pointers of each node |
| `task2.cpp` | Search for two values and swap the actual nodes containing them without swapping their data       |
| `task3.cpp` | Convert a singly linked list into a doubly linked list containing the same data                   |

**Week 3 concepts include:**

* Doubly linked list node structure
* `prev` and `next` pointer manipulation
* Traversing a doubly linked list
* Reversing a doubly linked list
* Swapping nodes by changing links rather than values
* Handling adjacent nodes and head-node swaps
* Converting singly linked lists into doubly linked lists
* Dynamic memory allocation

---

## How to Compile & Run

Requires a C++ compiler (`g++` recommended).

```bash
# Example — compile and run any file
g++ -o out "Week 1/Lab 1/task2.cpp" && ./out
```

For Week 3:

```bash
# Example
g++ -o out "Week 3/task1.cpp" && ./out
```

---

## Course Info

**Subject:** Data Structures
**University:** COMSATS University Islamabad, Attock Campus
**Language:** C++
**Implementation:** From scratch — no STL containers
