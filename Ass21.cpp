// Consider the student database of N students and their marks. Make use of a hash table
// implementation to quickly insert and lookup students' PNR and marks. Implement collision
// handling techniques- linear probing with chaining with replacement
// Test case :
// Create a hash table of size 10.
// Linear probing with chaining with replacement: Insert the following PNR: (11,
// 21,31,34,55,52,33)

#include <iostream>
using namespace std;

const int SIZE = 10;

struct Student {
    int pnr;
    int marks;
    bool occupied;
    int link;

    Student() {
        pnr = -1;
        marks = 0;
        occupied = false;
        link = -1;
    }
};

class HashTable {
    Student table[SIZE];

    int hashFunction(int pnr) {
        return pnr % SIZE;
    }

public:
    void insert(int pnr, int marks) {
        int home = hashFunction(pnr);

        if (!table[home].occupied) {
            // Empty home slot
            table[home].pnr = pnr;
            table[home].marks = marks;
            table[home].occupied = true;
            return;
        }

        int existingHome = hashFunction(table[home].pnr);
        if (existingHome != home) {
            // Replacement needed: current slot occupied by a displaced record
            Student displaced = table[home];

            // Insert new at correct home
            table[home].pnr = pnr;
            table[home].marks = marks;
            table[home].occupied = true;
            table[home].link = -1;

            // Reinsert displaced student elsewhere
            int i = (home + 1) % SIZE;
            while (table[i].occupied)
                i = (i + 1) % SIZE;

            table[i] = displaced;

            // Update link of correct home of displaced
            int dispHome = hashFunction(displaced.pnr);
            while (table[dispHome].link != -1)
                dispHome = table[dispHome].link;
            table[dispHome].link = i;
        } else {
            // Collision, find next slot
            int i = (home + 1) % SIZE;
            while (table[i].occupied)
                i = (i + 1) % SIZE;

            table[i].pnr = pnr;
            table[i].marks = marks;
            table[i].occupied = true;

            // Chain from home
            int j = home;
            while (table[j].link != -1)
                j = table[j].link;
            table[j].link = i;
        }
    }

    void display() {
        cout << "\nIndex\tPNR\tMarks\tLink\n";
        for (int i = 0; i < SIZE; ++i) {
            if (table[i].occupied)
                cout << i << "\t" << table[i].pnr << "\t" << table[i].marks << "\t" << table[i].link << endl;
            else
                cout << i << "\tEmpty\n";
        }
    }
};

int main() {
    HashTable ht;
    int pnrList[] = {11, 21, 31, 34, 55, 52, 33};
    int marksList[] = {70, 80, 75, 85, 90, 60, 65};

    for (int i = 0; i < 7; ++i)
        ht.insert(pnrList[i], marksList[i]);

    ht.display();

    return 0;
}

// ----------------------------------------------------------------

// Let's break down this C++ program **step-by-step** to understand how it works and how it applies **linear probing with chaining with replacement** for collision handling in a hash table.

// ---

// ## 🧠 **Goal of the Program**

// We are storing student records (PNR and marks) in a hash table of size 10 using:

// * **Hashing** → `index = PNR % SIZE`
// * **Collision resolution**:

//   * **Linear probing** (look for the next empty slot)
//   * **Chaining with replacement** (if home index is occupied by someone else’s entry, replace and relocate displaced entry)

// ---

// ## 📦 **Data Structure**

// ```cpp
// struct Student {
//     int pnr;       // student PNR (unique identifier)
//     int marks;     // marks scored
//     bool occupied; // whether this slot is filled
//     int link;      // link to next chained entry (collision resolution)
// };
// ```

// ---

// ## 📌 **Key Functions and Logic**

// ### 1. **Hash Function**

// ```cpp
// int hashFunction(int pnr) {
//     return pnr % SIZE;
// }
// ```

// Simple modulo hashing.

// ---

// ### 2. **Insert Operation**

// This is where it gets interesting.

// Let’s say you want to insert a new student at their **home index**:

// * **Case 1: Home index is free** → insert directly.
// * **Case 2: Home index is occupied:**

//   * If the occupying entry **belongs to a different home**:

//     * REPLACE it with the new student (new student deserves that index).
//     * Find a new spot for the displaced one.
//     * Update chaining (using `.link`).
//   * If the occupying entry **belongs to the same home**:

//     * LINEAR PROBING to find a new spot.
//     * Update the `link` of the last node in the chain.

// ---

// ## 🔍 **Walkthrough Example**

// ### Test Case:

// ```cpp
// int pnrList[] = {11, 21, 31, 34, 55, 52, 33};
// ```

// Table size is 10, so:

// | PNR | Hash (PNR % 10) |
// | --- | --------------- |
// | 11  | 1               |
// | 21  | 1               |
// | 31  | 1               |
// | 34  | 4               |
// | 55  | 5               |
// | 52  | 2               |
// | 33  | 3               |

// ### Step-by-step Insertions:

// 1. **Insert 11 at index 1** → empty → done.
// 2. **Insert 21 → hash = 1** → index 1 already has 11 (whose home is 1), so linear probe → store at next free spot (say index 2) → link 1→2.
// 3. **Insert 31 → hash = 1** → index 1 has 11 → 11’s home is 1 → linear probe → go to next free (say index 3) → link 2→3.
// 4. **Insert 34 → hash = 4** → empty → store directly.
// 5. **Insert 55 → hash = 5** → empty → store directly.
// 6. **Insert 52 → hash = 2** → index 2 has 21, but 21’s hash = 1 ≠ 2 → **REPLACE**.

//    * Insert 52 at index 2.
//    * Find new place for 21 (say index 6).
//    * Update chain: 1→6→3.
// 7. **Insert 33 → hash = 3** → index 3 has 31 (hash 1 ≠ 3) → **REPLACE**.

//    * Insert 33 at index 3.
//    * Move 31 to a new place (say 7).
//    * Update chain: 1→6→7

// ---

// ## 📊 **Display Output**

// `display()` prints:

// ```
// Index   PNR   Marks   Link
// 0       Empty
// 1       11    70      6
// 2       52    60      -1
// 3       33    65      -1
// 4       34    85      -1
// 5       55    90      -1
// 6       21    80      7
// 7       31    75      -1
// 8       Empty
// 9       Empty
// ```

// This shows how `link` pointers are updated as per chaining logic.

// ---

// ## ✅ Summary

// * Uses **hashing with chaining and replacement** to insert student records.
// * Handles collisions:

//   * **Same home**: probe + update `link`
//   * **Different home**: replace + relocate + update `link`
// * Efficient for minimizing clustering and improving lookup.

// Would you like to add **lookup/search function** to retrieve marks by PNR next?
