// Department maintains student information. the file contains rollno, name, division, and address.
// Allow user to add, edit, delete, insert and search information of student. use sequential file to
// maintain the data
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Student {
    int rollNo;
    string name;
    string division;
    string address;

    string to_string() const {
        return std::to_string(rollNo) + "," + name + "," + division + "," + address;
    }

    static Student from_string(const string& data) {
        stringstream ss(data);
        string part;
        vector<string> parts;
        while (getline(ss, part, ',')) parts.push_back(part);
        return {stoi(parts[0]), parts[1], parts[2], parts[3]};
    }
};

const string FILE_NAME = "students.txt";

void addStudent(const Student& s) {
    ofstream file(FILE_NAME, ios::app);
    file << s.to_string() << endl;
    file.close();
}

void displayAll() {
    ifstream file(FILE_NAME);
    string line;
    cout << "\nRollNo\tName\tDivision\tAddress" << endl;
    while (getline(file, line)) {
        Student s = Student::from_string(line);
        cout << s.rollNo << "\t" << s.name << "\t" << s.division << "\t\t" << s.address << endl;
    }
    file.close();
}

void searchStudent(int roll) {
    ifstream file(FILE_NAME);
    string line;
    bool found = false;
    while (getline(file, line)) {
        Student s = Student::from_string(line);
        if (s.rollNo == roll) {
            cout << "\nRecord Found:\n";
            cout << "RollNo: " << s.rollNo << "\nName: " << s.name
                 << "\nDivision: " << s.division << "\nAddress: " << s.address << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "Record not found!\n";
    file.close();
}

void deleteStudent(int roll) {
    ifstream file(FILE_NAME);
    ofstream temp("temp.txt");
    string line;
    bool deleted = false;
    while (getline(file, line)) {
        Student s = Student::from_string(line);
        if (s.rollNo == roll) {
            deleted = true;
            continue;
        }
        temp << line << endl;
    }
    file.close();
    temp.close();
    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());
    if (deleted) cout << "Record deleted successfully.\n";
    else cout << "Record not found!\n";
}

void editStudent(int roll, const Student& newDetails) {
    ifstream file(FILE_NAME);
    ofstream temp("temp.txt");
    string line;
    bool edited = false;
    while (getline(file, line)) {
        Student s = Student::from_string(line);
        if (s.rollNo == roll) {
            temp << newDetails.to_string() << endl;
            edited = true;
        } else {
            temp << line << endl;
        }
    }
    file.close();
    temp.close();
    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());
    if (edited) cout << "Record updated successfully.\n";
    else cout << "Record not found!\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Record Manager ---\n";
        cout << "1. Add Student\n2. Display All\n3. Search by RollNo\n4. Delete Record\n5. Edit Record\n6. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            Student s;
            cout << "Roll No: "; cin >> s.rollNo; cin.ignore();
            cout << "Name: "; getline(cin, s.name);
            cout << "Division: "; getline(cin, s.division);
            cout << "Address: "; getline(cin, s.address);
            addStudent(s);
        } else if (choice == 2) {
            displayAll();
        } else if (choice == 3) {
            int roll; cout << "Enter RollNo to search: "; cin >> roll;
            searchStudent(roll);
        } else if (choice == 4) {
            int roll; cout << "Enter RollNo to delete: "; cin >> roll;
            deleteStudent(roll);
        } else if (choice == 5) {
            Student s;
            cout << "Roll No to Edit: "; cin >> s.rollNo; cin.ignore();
            cout << "New Name: "; getline(cin, s.name);
            cout << "New Division: "; getline(cin, s.division);
            cout << "New Address: "; getline(cin, s.address);
            editStudent(s.rollNo, s);
        } else if (choice == 6) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}

// 1. Add Student
// > Roll No: 1
// > Name: John
// > Division: A
// > Address: Pune

// 2. Display All
// > RollNo Name Division Address
// > 1     John    A       Pune
