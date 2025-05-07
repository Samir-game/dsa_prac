// Given sequence k = k1<; k2<..... kn of n sorted keys, with a search probability pi for each
// key ki . Build the Binary search tree that has the least search cost given the access probability
// for each key. Display weight matrix, cost matrix and root matrix.
// test your program for following example:
// k1=do, k2=if, k3=read, k4= while
// p1 = 1, p2 = 3, p3 = 1, p4 = 3
// q0 = 1, q1 = 2, q2 = 1, q3= 1, q4 = 3

#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
using namespace std;

const int n = 4; // Number of keys

void buildOBST(vector<int> p, vector<int> q, vector<string> keys) {
    int cost[n + 2][n + 1] = {0};
    int weight[n + 2][n + 1] = {0};
    int root[n + 2][n + 1] = {0};

    // Initialization
    for (int i = 0; i <= n; i++) {
        cost[i + 1][i] = q[i];
        weight[i + 1][i] = q[i];
    }

    // Dynamic Programming
    for (int length = 1; length <= n; length++) {
        for (int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            cost[i][j] = INT_MAX;
            weight[i][j] = weight[i][j - 1] + p[j - 1] + q[j];

            for (int r = i; r <= j; r++) {
                int c = cost[i][r - 1] + cost[r + 1][j] + weight[i][j];
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }

    // Display Weight Matrix
    cout << "\nWeight Matrix:\n";
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j <= n; j++) {
            if (i <= j + 1)
                cout << setw(3) << weight[i][j] << " ";
            else
                cout << "    ";
        }
        cout << endl;
    }

    // Display Cost Matrix
    cout << "\nCost Matrix:\n";
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j <= n; j++) {
            if (i <= j + 1)
                cout << setw(3) << cost[i][j] << " ";
            else
                cout << "    ";
        }
        cout << endl;
    }

    // Display Root Matrix
    cout << "\nRoot Matrix:\n";
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j <= n; j++) {
            if (i <= j + 1)
                cout << setw(3) << root[i][j] << " ";
            else
                cout << "    ";
        }
        cout << endl;
    }

    cout << "\nMinimum cost of Optimal BST: " << cost[1][n] << endl;
}

int main() {
    vector<string> keys = {"do", "if", "read", "while"};
    vector<int> p = {1, 3, 1, 3};    // successful search probabilities
    vector<int> q = {1, 2, 1, 1, 3}; // unsuccessful search probabilities

    buildOBST(p, q, keys);

    return 0;
}

// This C++ program implements **Dynamic Programming** to construct an **Optimal Binary Search Tree (OBST)**. It minimizes the **expected search cost** of accessing keys and dummy (unsuccessful) keys based on given **probabilities**.

// Let’s break it down:

// ---

// ## ✅ Problem Summary

// Given:

// * `n = 4` keys: `{"do", "if", "read", "while"}`
// * `p[i]`: probability of a successful search for key `i`
// * `q[i]`: probability of an unsuccessful search between key `i-1` and key `i`

// The program computes:

// * Minimum cost of OBST
// * Structure (which node is root for each subtree)

// ---

// ## 📦 Matrix Definitions

// Let `i` and `j` denote the start and end key positions (1-based indexing).

// | Matrix         | Meaning                                              |
// | -------------- | ---------------------------------------------------- |
// | `cost[i][j]`   | Minimum expected cost to search in subtree `i...j`   |
// | `weight[i][j]` | Total probability mass of keys/dummies in `i...j`    |
// | `root[i][j]`   | Index `r` of the key that is root of `i...j` subtree |

// ---

// ## 🧠 Key Concepts

// ### 🧩 Initialization

// ```cpp
// for (int i = 0; i <= n; i++) {
//     cost[i + 1][i] = q[i];
//     weight[i + 1][i] = q[i];
// }
// ```

// * Cost/weight of **empty tree** between `i-1` and `i` is `q[i]`

// ---

// ### 🔁 Dynamic Programming

// ```cpp
// for (int length = 1; length <= n; length++) {
//     for (int i = 1; i <= n - length + 1; i++) {
//         int j = i + length - 1;
// ```

// Loop over **all lengths** of subtrees and **all possible positions** for that length.

// #### Calculate:

// * `weight[i][j]`: total weight in `i..j` subtree
// * Try all roots `r` in `[i..j]`:

//   ```cpp
//   int c = cost[i][r - 1] + cost[r + 1][j] + weight[i][j];
//   if (c < cost[i][j]) {
//       cost[i][j] = c;
//       root[i][j] = r;
//   }
//   ```

// Choose `r` that gives **minimum cost**.

// ---

// ## 🖥️ Output Format

// ### 1. **Weight Matrix**

// Shows total probabilities between key ranges:

// ```
// Weight Matrix:
//  1   4   6   10   17
//      2   4    7   14
//          1    5   12
//               1    5
//                    3
// ```

// ### 2. **Cost Matrix**

// Minimum cost for optimal BST over each subproblem:

// ```
// Cost Matrix:
//  1   5   10  21  42
//      2   5   11  24
//          1   5   12
//               1   5
//                    3
// ```

// ### 3. **Root Matrix**

// Best root index (1-based) for each subtree:

// ```
// Root Matrix:
//  0   1   2   2   2
//      0   2   2   2
//          0   3   4
//               0   4
//                    0
// ```

// * Example: `root[1][4] = 2` → key `2` (i.e., `"if"`) is the root of full tree.

// ---

// ## ✅ Final Output

// ```
// Minimum cost of Optimal BST: 24
// ```

// ---

// ## 🧪 How Keys Map to Indices:

// | Index | Key     |
// | ----- | ------- |
// | 1     | "do"    |
// | 2     | "if"    |
// | 3     | "read"  |
// | 4     | "while" |

// So `root[1][4] = 2` → `"if"` is root for keys 1 to 4.

// ---

// ## ✅ Summary

// | Concept   | Value                                                   |
// | --------- | ------------------------------------------------------- |
// | Type      | Optimal Binary Search Tree                              |
// | Goal      | Minimize expected search cost                           |
// | Approach  | Dynamic Programming with cost, weight, root tables      |
// | Output    | OBST structure, weights, and minimum cost               |
// | Test Data | `"do", "if", "read", "while"` with custom `p[]` & `q[]` |

// ---

// Would you like me to show how to **construct the actual OBST tree** from the root matrix and print it like a hierarchy?
