// Input a list of more than 20 correctly spelled lowercase words. The words are inserted into the
// hash table. Handle collision using separate chaining. After input is obtained, each word that the
// user enters into the program is looked up within the hash table to see if it exists. If the user
// entered word exists within the hash table, then that word is spelled correctly.

#include<iostream>
#include<vector>
#include<list>
#include<string>

using namespace std;

const int TABLE_SIZE = 10;

class HashTable{
    vector<list<string>> table;

    int hashFunction(const string& word){
        int hash = 0;
        for(char ch: word){
            hash = (hash*31 + ch) % TABLE_SIZE;

        }
        return hash;
    }

public:
    HashTable(){
        table.resize(TABLE_SIZE);
    }

    void insert(const string& word){
        int index = hashFunction(word);
        table[index].push_back(word);
    }

    bool search(const string& word){
        int index = hashFunction(word);

        for(const string& w: table[index]){
            if(w == word){
                return true;
            }
        }
        return false;
    }

    void loadDictionary() {
        vector<string> words = {
            "apple", "banana", "grape", "orange", "melon",
            "lemon", "cherry", "peach", "plum", "kiwi",
            "mango", "pear", "lime", "apricot", "fig",
            "date", "guava", "papaya", "coconut", "berry",
            "nectarine", "lychee", "tangerine", "quince", "dragonfruit"
        };

        for (const string& word : words) {
            insert(word);
        }

        cout << "Dictionary loaded with " << words.size() << " words.\n";
    }
};

int main(){
    HashTable hashTable;
    hashTable.loadDictionary();

    string input;
    cout << "\nEnter words to check spelling (type 'exit' to stop):\n";

    while(true){
        cout << "> ";

        cin>>input;

        if(input == "exit"){
            break;
        }
        if(hashTable.search(input)){
            cout << input << " is spelled correctly.\n";
        } else {
            cout << input << " is not found in the dictionary.\n";
        }
    }

}

// **Evaluating code explanation request**

// The user posted a new code snippet related to a hash table with separate chaining. Given that they've asked for similar explanations before, I'll assume they want another detailed line-by-line breakdown.

// I'll provide an explanation in a clear, structured manner, using bullet points and a step-by-step approach. I will also include a sample test case, as that seems to be what they're looking for, keeping the tone natural and human without over-commenting on the code.

// **Crafting code explanation**

// I should explain each part of the user’s code: starting with constants, the class, the constructor, then moving on to insert, search, and the hash function details, followed by how the dictionary is loaded. I'll demonstrate with a step-by-step test using a dictionary with TABLE\_SIZE=10, computing indices for a list of words and showing how collisions apply with separate chaining. I could use Python privately to quickly compute indices for illustration, including checking for correctly spelled words and errors with a sample test.


// Thought for 15 seconds


// Below is the same two‑part treatment you asked for last time — first a **line‑by‑line guide**, then a **walk‑through with real data** so you can watch the hash table grow and see look‑ups succeed or fail.

// ---

// ## 1  What every line is doing

// | Code                         | Reason / effect                                                    |
// | ---------------------------- | ------------------------------------------------------------------ |
// | `#include <iostream>`        | Gives access to `std::cout`, `std::cin`, etc.                      |
// | `#include <vector>`          | Supplies the dynamic‑array container we’ll use for the table.      |
// | `#include <list>`            | Supplies a doubly‑linked list for each bucket (separate chaining). |
// | `#include <string>`          | Needed for the `std::string` word type.                            |
// | `using namespace std;`       | Lets us drop the `std::` prefix everywhere.                        |
// | `const int TABLE_SIZE = 10;` | The hash table will have ten buckets (indices 0–9).                |

// ### `class HashTable`

// | Fragment                                   | Explanation                                                                                                                                                                |
// | ------------------------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
// | `vector<list<string>> table;`              | The core data structure: an array (vector) where each cell holds its own linked list of words that hashed to that bucket.                                                  |
// | **`int hashFunction(const string& word)`** | Simple polynomial‑rolling hash using base 31 (classical for strings). Every character `ch` updates `hash = (hash*31 + ch) % TABLE_SIZE`, so the final value is always 0‑9. |
// | **Constructor** – `HashTable()`            | Resizes the vector to `TABLE_SIZE` empty lists so every bucket exists from the start.                                                                                      |
// | **`void insert(const string& word)`**      | 1) compute bucket index, 2) `push_back` the word onto that bucket’s list.                                                                                                  |
// | **`bool search(const string& word)`**      | 1) find the bucket, 2) iterate through its list; return `true` on first exact match, else `false`.                                                                         |
// | **`void loadDictionary()`**                | Hard‑coded “dictionary” of 25 fruit names → calls `insert` for each, then prints how many words were loaded.                                                               |

// ### `main()`

// * Creates a `HashTable`.
// * Calls `loadDictionary()` to pre‑fill it with 25 words (⇢ many more than the 10 buckets, so collisions are guaranteed).
// * Repeatedly prompts the user.
//   \* `"exit"` terminates the loop.
//   \* For any other word, `search()` decides whether it is spelled correctly (present) or not (absent).

// ---

// ## 2  What actually happens with the built‑in dictionary

// ### 2.1  Bucket population

// The table size is 10, so every hash is `wordHash % 10`. Here are the 25 words and where they land (same order in which they’re inserted):

// | Bucket | Words inserted in that bucket (separate chaining order) |
// | ------ | ------------------------------------------------------- |
// | 0      | apple → mango → fig                                     |
// | 1      | *empty*                                                 |
// | 2      | guava                                                   |
// | 3      | cherry → peach → lime → coconut → nectarine             |
// | 4      | pear → apricot → date → lychee                          |
// | 5      | quince                                                  |
// | 6      | orange → plum → kiwi → papaya                           |
// | 7      | grape → tangerine                                       |
// | 8      | berry                                                   |
// | 9      | banana → melon → lemon → dragonfruit                    |

// *(I generated the table with the exact same hash function so you can reproduce it.)*

// ### 2.2  Sample interactive run

// ```
// Dictionary loaded with 25 words.

// Enter words to check spelling (type 'exit' to stop):
// > apple
// apple is spelled correctly.
// > aplpe
// aplpe is not found in the dictionary.
// > kiwi
// kiwi is spelled correctly.
// > coconut
// coconut is spelled correctly.
// > carrot
// carrot is not found in the dictionary.
// > exit
// ```

// **Why look‑ups are fast**

// * `hashFunction("coconut")` → 3, jump straight to bucket 3.
// * Bucket 3’s list is five nodes long; we compare sequentially until `"coconut"` matches the fourth node — a constant‑time bucket access plus a tiny linear scan of that short list.

// Even with only ten buckets and 25 words the longest chain length is five, so worst‑case lookup touches six items (bucket head + five nodes). With a larger table size the load factor would fall and the chains would become even shorter.

// ---

// ### Big‑picture summary

// This program demonstrates **separate chaining**:

// * The table never “fills up” — a bucket can hold unlimited words via its linked list.
// * Insertion is *O(1)* amortised: compute index, `push_back`.
// * Search is *O(1 + α)* where α = average chain length (load factor).
//   With 25 words / 10 buckets, α = 2.5, so typical search costs about 3–4 string comparisons.

// Use it as a minimalist spell‑checker scaffold: swap in a real dictionary file, maybe enlarge `TABLE_SIZE`, and you have a perfectly serviceable hash‑table‑backed dictionary lookup.
