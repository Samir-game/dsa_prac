// Department maintains student information. the file contains rollno, name, division, and address.
// Allow user to add, edit, delete, insert and search information of student. use Direct access file to
// maintain the data. 

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 100;
const char* FILENAME = "students.dat";

class Student {
public:
    int rollNo;
    char name[30];
    char division;
    char address[50];

    Student() {
        rollNo = -1;
        strcpy(name, "");
        division = '-';
        strcpy(address, "");
    }

    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 30);
        cout << "Enter Division: ";
        cin >> division;
        cout << "Enter Address: ";
        cin.ignore();
        cin.getline(address, 50);
    }

    void display() {
        cout << "Roll No: " << rollNo << ", Name: " << name
             << ", Division: " << division << ", Address: " << address << endl;
    }
};

// Adds a student to the first empty slot
void addStudent() {
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    Student s;
    s.input();
    Student temp;

    for (int i = 0; i < MAX; ++i) {
        file.seekg(i * sizeof(Student), ios::beg);
        file.read((char*)&temp, sizeof(Student));
        if (temp.rollNo == -1) {
            file.seekp(i * sizeof(Student), ios::beg);
            file.write((char*)&s, sizeof(Student));
            cout << "Student added successfully.\n";
            file.close();
            return;
        }
    }

    cout << "File is full. Cannot add more students.\n";
    file.close();
}

// Searches student by roll number
void searchStudent() {
    ifstream file(FILENAME, ios::binary);
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;
    Student s;
    bool found = false;

    for (int i = 0; i < MAX; ++i) {
        file.read((char*)&s, sizeof(Student));
        if (s.rollNo == roll) {
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";

    file.close();
}

// Deletes a student by roll number
void deleteStudent() {
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;
    Student s;
    bool found = false;

    for (int i = 0; i < MAX; ++i) {
        file.seekg(i * sizeof(Student), ios::beg);
        file.read((char*)&s, sizeof(Student));
        if (s.rollNo == roll) {
            Student blank;
            file.seekp(i * sizeof(Student), ios::beg);
            file.write((char*)&blank, sizeof(Student));
            cout << "Record deleted.\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";

    file.close();
}

// Edits a student by roll number
void editStudent() {
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    int roll;
    cout << "Enter Roll No to edit: ";
    cin >> roll;
    Student s;
    bool found = false;

    for (int i = 0; i < MAX; ++i) {
        file.seekg(i * sizeof(Student), ios::beg);
        file.read((char*)&s, sizeof(Student));
        if (s.rollNo == roll) {
            cout << "Existing Record:\n";
            s.display();
            cout << "Enter new details:\n";
            s.input();
            file.seekp(i * sizeof(Student), ios::beg);
            file.write((char*)&s, sizeof(Student));
            cout << "Record updated.\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";

    file.close();
}

// Displays all students
void displayAll() {
    ifstream file(FILENAME, ios::binary);
    Student s;
    bool anyFound = false;

    for (int i = 0; i < MAX; ++i) {
        file.read((char*)&s, sizeof(Student));
        if (s.rollNo != -1) {
            s.display();
            anyFound = true;
        }
    }

    if (!anyFound)
        cout << "No records to display.\n";

    file.close();
}

int main() {
    // Create the file with 100 empty records only if it doesn't exist
    ifstream check(FILENAME, ios::binary);
    if (!check) {
        ofstream file(FILENAME, ios::binary);
        Student s;
        for (int i = 0; i < MAX; ++i)
            file.write((char*)&s, sizeof(Student));
        file.close();
        cout << "Initialized student database.\n";
    }
    check.close();

    int choice;
    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n2. Search Student\n3. Edit Student\n4. Delete Student\n5. Display All\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: editStudent(); break;
            case 4: deleteStudent(); break;
            case 5: displayAll(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (choice != 0);

    return 0;
}


// Your program is an excellent example of using **Direct Access Files (Random Access Files)** in C++ to manage a **fixed-size student record system**. Here's a detailed breakdown of what your program is doing:

// ---

// ## 🧠 Core Concept: What is a Direct Access File?

// Unlike sequential files, where you must read from start to end, **direct access files** allow jumping directly to a specific record using:

// ```cpp
// file.seekg(i * sizeof(RecordType), ios::beg);
// ```

// This enables **efficient search, update, or deletion** of fixed-size records by their position.

// ---

// ## ✅ What Your Program Does

// | Operation      | Function              | Summary                                                |
// | -------------- | --------------------- | ------------------------------------------------------ |
// | 🆕 Add         | `addStudent()`        | Inserts a student into the first available blank slot. |
// | 🔍 Search      | `searchStudent()`     | Finds and displays a student by roll number.           |
// | ✏️ Edit        | `editStudent()`       | Edits an existing record by roll number.               |
// | ❌ Delete       | `deleteStudent()`     | Deletes (blank-fills) a student record.                |
// | 📄 Display All | `displayAll()`        | Displays all non-deleted student records.              |
// | 🗂️ File Init  | `main()` (first-time) | Initializes the file with 100 blank records.           |

// ---

// ## 🧱 Record Structure

// ```cpp
// class Student {
// public:
//     int rollNo;
//     char name[30];
//     char division;
//     char address[50];
// };
// ```

// Each record:

// * Is **fixed-size** (`sizeof(Student)`).
// * Can be located directly using record index `i`.

// ---

// ## 📥 File Used

// ```cpp
// const char* FILENAME = "students.dat";
// ```

// You open this file in:

// * `ios::in | ios::out | ios::binary` mode for updating.
// * `ios::binary` mode for reading all.

// ---

// ## 🔄 File Initialization (First Run)

// ```cpp
// if (!check) {
//     ofstream file(FILENAME, ios::binary);
//     for (int i = 0; i < MAX; ++i)
//         file.write((char*)&s, sizeof(Student));
// }
// ```

// On first run, you:

// * Pre-fill the file with 100 blank student objects (rollNo = -1).

// This creates a structure that supports **random indexing**.

// ---

// ## 📦 Record Handling Logic

// ### ➕ Add

// * Scans the file from start to end.
// * Finds the first `rollNo == -1`.
// * Overwrites that slot with new data.

// ### 🔍 Search

// * Scans the file from start.
// * Prints data if `rollNo == input`.

// ### ✏️ Edit

// * Same as search.
// * If found, prompts user and overwrites the same slot.

// ### ❌ Delete

// * Replaces the found record with a blank `Student` object.

// ---

// ## 🧪 Sample Run (Illustration)

// ```
// --- Student Information System ---
// 1. Add Student
// 2. Search Student
// 3. Edit Student
// 4. Delete Student
// 5. Display All
// 0. Exit
// Enter choice: 1
// Enter Roll No: 101
// Enter Name: Alice
// Enter Division: A
// Enter Address: Pune
// => Student added successfully

// Enter choice: 5
// Roll No: 101, Name: Alice, Division: A, Address: Pune
// ```

// ---

// ## ✅ Pros of This Design

// | Strength              | Why it helps                     |
// | --------------------- | -------------------------------- |
// | 🔄 Direct access      | Fast search, update, and delete  |
// | 💾 Binary file        | Compact and efficient            |
// | ⛔ RollNo -1 for blank | Simple way to mark deleted slots |
// | 🛠️ Modular           | All logic is cleanly separated   |

// ---

// ## ⚠️ Improvements (Optional)

// 1. **Use file locking** in a multi-user environment.
// 2. Add **roll number uniqueness check** before insertion.
// 3. Display students in **sorted order** (if needed — would require reading all into memory).
// 4. Allow changing roll number (right now you can’t edit it).

// ---

// ## 🧾 Summary

// You’ve built a **fully functioning student record system** with:

// * Persistent storage (`students.dat`)
// * Efficient direct access
// * Insert, search, edit, delete, display operations
// * File initialization and record management

// Let me know if you'd like to:

// * Add roll number validation?
// * Upgrade to dynamic record size using linked files?
// * Export records to a text file?
