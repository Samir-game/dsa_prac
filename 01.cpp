// Consider the student database of N students and their marks. Make use of a hash table
// implementation to quickly insert and lookup students' Rollno and marks. Implement collision
// handling techniques- linear probing with chaining without replacement.
// Test case:
// Create a hash table of size 10.
// 1. Linear probing with chaining without replacement: Insert the following RollNos:
// (31,13,14,51,16,71,48,19)

#include <iostream>
using namespace std;

const int SIZE = 10;

struct Student {
    int rollNo;
    int marks;
    int link;
    bool occupied;

    Student() {
        rollNo = -1;
        marks = 0;
        link = -1;
        occupied = false;
    }
};

class HashTable {
    Student table[SIZE];

    int hashFunction(int rollNo) {
        return rollNo % SIZE;
    }

public:
    // Insert a roll number and marks into the hash table
    void insert(int rollNo, int marks) {
        int index = hashFunction(rollNo);

        // Case 1: Home slot is empty
        if (!table[index].occupied) {
            table[index].rollNo = rollNo;
            table[index].marks = marks;
            table[index].occupied = true;
            return;
        }

        // Case 2: Home slot is occupied — find next free slot
        int i = (index + 1) % SIZE;
        while (i != index && table[i].occupied) {
            i = (i + 1) % SIZE;
        }

        if (i == index) {
            cout << "Hash table is full!\n";
            return;
        }

        // Insert at free slot
        table[i].rollNo = rollNo;
        table[i].marks = marks;
        table[i].occupied = true;

        // Chain from home slot (without replacement)
        int j = index;
        while (table[j].link != -1) {
            j = table[j].link;
        }
        table[j].link = i;
    }

    // Display the hash table
    void display() {
        cout << "Index\tRollNo\tMarks\tLink\n";
        for (int i = 0; i < SIZE; ++i) {
            if (table[i].occupied)
                cout << i << "\t" << table[i].rollNo << "\t" << table[i].marks << "\t" << table[i].link << "\n";
            else
                cout << i << "\tEmpty\n";
        }
    }
};

int main() {
    HashTable ht;

    int rollNos[] = {31, 13, 14, 51, 16, 71, 48, 19};
    int n = sizeof(rollNos) / sizeof(rollNos[0]);

    // Insert roll numbers with dummy marks = rollNo + 50
    for (int i = 0; i < n; ++i) {
        ht.insert(rollNos[i], rollNos[i] + 50);
    }

    // Display final table
    cout << "Final Hash Table (Linear Probing with Chaining Without Replacement):\n";
    ht.display();

    return 0;
}

// **Explaining C++ code for hash table**

// The user has shared C++ code implementing a hash table with chaining and linear probing, and based on prior instructions, it seems like they may want an explanation for educational purposes. I will explain each line of the code in detail, covering the purpose of variables, functions, and logic used. Afterward, I'll provide a step-by-step breakdown of the entire code using a sample test case to demonstrate how it works in practice. That should offer a clear, educational walkthrough.

// **Providing an explanation for code**

// The user previously asked for a detailed explanation of each line of code, specifically not to add code comments but to focus purely on the logic and variables. Since the user now provided a hash table implementation, I'll follow the same approach. I'll break down the code into high-level sections: headers, constants, structs, class, functions, and the main function. I'll explain step-by-step with bullet points, focusing on things like the use of arrays, hash functions, and how the test case demonstrates the code's execution, without adding code comments directly.


// Thought for 20 seconds


// Below is a **two‑part walkthrough**:

// 1. **Line‑by‑line commentary** – what every declaration, variable, statement, and branch does.
// 2. **Step‑by‑step execution trace** – how the sample data `{31, 13, 14, 51, 16, 71, 48, 19}` is processed to produce the final table.

// ---

// ## 1  Line‑by‑line explanation

// | Code fragment          | What it means / why it is there                                                        |
// | ---------------------- | -------------------------------------------------------------------------------------- |
// | `#include <iostream>`  | Brings in the standard input/output stream library so the program can use `std::cout`. |
// | `using namespace std;` | Allows writing `cout` instead of `std::cout`, `endl`, etc.                             |
// | `const int SIZE = 10;` | Compile‑time constant holding the hash‑table size (10 slots).                          |

// ### `struct Student`

// | Line             | Purpose                                                                              |
// | ---------------- | ------------------------------------------------------------------------------------ |
// | `int rollNo;`    | Key to hash on and to identify the record.                                           |
// | `int marks;`     | Value stored with the key.                                                           |
// | `int link;`      | Index of the **next** record in the collision chain ( `‑1` = end of chain).          |
// | `bool occupied;` | `true` if the slot currently stores a record; `false` if empty.                      |
// | **Constructor**  | Initializes a fresh slot: rollNo = −1, marks = 0, link = −1, and `occupied` = false. |

// ### `class HashTable`

// | Part                                                          | Explanation                                                                                                                    |
// | ------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------ |
// | `Student table[SIZE];`                                        | The fixed‑size array that holds all slots.                                                                                     |
// | `int hashFunction(int rollNo)`<br>`{ return rollNo % SIZE; }` | Simple modulo‑10 hash. For a 10‑slot table, keys 0‑9 map to the same index as the key itself; 10 maps to 0; 31 maps to 1, etc. |

// #### `void insert(int rollNo, int marks)`

// 1. **Compute home slot**
//    `int index = hashFunction(rollNo);`
// 2. **Case 1 – home slot empty**
//    *If `table[index].occupied` is `false`*   → store the record there and quit.
//    (No chain manipulation needed because there is no collision.)
// 3. **Case 2 – home slot already occupied**
//    *Find the next free position by linear probing*

//    ```cpp
//    int i = (index + 1) % SIZE;
//    while (i != index && table[i].occupied) { … }
//    ```

//    *The loop wraps around the array until it either finds an empty slot or returns to the starting index.*
//    • If it returns to the start → every slot is occupied → “Hash table is full!”
// 4. **Store the record in the empty slot `i`.**
// 5. **Build / extend the collision chain without replacement**

//    ```cpp
//    int j = index;                // start at home slot
//    while (table[j].link != -1)   // walk to the last node
//        j = table[j].link;
//    table[j].link = i;            // append new slot
//    ```

//    The chain always starts from the *original* home slot; the new record never replaces anything already in the home slot.

// #### `void display()`

// Prints a header line and then, for every index `i`, either:

// * `i   roll  marks  link` – if the slot is occupied, or
// * `i   Empty` – if not.

// ### `main()`

// 1. Creates an empty `HashTable ht`.
// 2. Test data: `int rollNos[] = {31, 13, 14, 51, 16, 71, 48, 19};`
// 3. Loops through the array, inserting each roll number with dummy marks `rollNo + 50`.
// 4. Calls `ht.display()` to show the finished structure.

// ---

// ## 2  Execution trace with the test case

// | Step | RollNo | Home slot `rollNo % 10` | Action taken                                                                                                    | Chain updates             |
// | ---- | ------ | ----------------------- | --------------------------------------------------------------------------------------------------------------- | ------------------------- |
// | 1    | **31** | 1                       | Slot 1 empty → store (marks = 81).                                                                              | Chain at 1: **1**         |
// | 2    | **13** | 3                       | Slot 3 empty → store (marks = 63).                                                                              | Chain at 3: **3**         |
// | 3    | **14** | 4                       | Slot 4 empty → store (marks = 64).                                                                              | Chain at 4: **4**         |
// | 4    | **51** | 1                       | Slot 1 occupied → linear probe finds slot 2 free → store there.<br>Append to chain that starts at 1 → `1 → 2`.  | Chain at 1: 1 → **2**     |
// | 5    | **16** | 6                       | Slot 6 empty → store (marks = 66).                                                                              | Chain at 6: **6**         |
// | 6    | **71** | 1                       | Slot 1 occupied → probe 2 (occ), 3 (occ), 4 (occ) → slot 5 free → store there.<br>Append to chain: `1 → 2 → 5`. | Chain at 1: 1 → 2 → **5** |
// | 7    | **48** | 8                       | Slot 8 empty → store (marks = 98).                                                                              | Chain at 8: **8**         |
// | 8    | **19** | 9                       | Slot 9 empty → store (marks = 69).                                                                              | Chain at 9: **9**         |

// ### Final table exactly as `display()` prints it

// ```
// Index  RollNo  Marks  Link
// 0      Empty
// 1      31      81     2
// 2      51      101    5
// 3      13      63     -1
// 4      14      64     -1
// 5      71      121    -1
// 6      16      66     -1
// 7      Empty
// 8      48      98     -1
// 9      19      69     -1
// ```

// **What you can observe**

// * All keys hash into the range 0–9 with `rollNo % 10`.
// * Collisions that share the same home slot (31, 51, 71) form a singly‑linked list: 1 → 2 → 5.
// * “Without replacement” means the very first occupant of the home slot (31) never moves; later items are linked outwards via `link`.
// * Linear probing stops as soon as the first free slot is found, but the logical linkage is still through the `link` field, so lookup starts at the home slot and follows links until the key is found or the chain ends (`link == ‑1`).

// ---

// ### Overall functionality recap

// The program demonstrates an **open‑addressing hash table** with a hybrid collision‑resolution technique:

// * **Linear probing** is used only to *physically* find the next free slot when a collision occurs.
// * **Chaining “without replacement”** keeps a **logical** linked list starting at the original bucket so that lookups need follow at most one simple chain even though the physical records might be scattered.

// This design keeps load factors high without moving items already in place, while still ensuring that all records with the same home bucket can be retrieved in *O(chain length)* time.
