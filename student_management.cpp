#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const string DATA_FILE = "students.txt";

struct Student {
    string rollNumber;
    string name;
    int age;
    string course;
    string email;
};

vector<string> splitRecord(const string& line) {
    vector<string> fields;
    string field;
    stringstream stream(line);
    while (getline(stream, field, '|')) fields.push_back(field);
    return fields;
}

string cleanField(string value) {
    for (char& ch : value) if (ch == '|') ch = '/';
    return value;
}

string readText(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return cleanField(value);
}

int readAge() {
    while (true) {
        string input;
        cout << "Enter age: ";
        getline(cin, input);
        stringstream stream(input);
        int age;
        char extra;
        if ((stream >> age) && !(stream >> extra) && age > 0 && age <= 120)
            return age;
        cout << "Please enter a valid age between 1 and 120.\n";
    }
}

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file(DATA_FILE.c_str());
    string line;

    while (getline(file, line)) {
        vector<string> fields = splitRecord(line);
        if (fields.size() != 5) continue;

        try {
            Student student;
            student.rollNumber = fields[0];
            student.name = fields[1];
            student.age = stoi(fields[2]);
            student.course = fields[3];
            student.email = fields[4];

            if (!student.rollNumber.empty() && student.age > 0 && student.age <= 120)
                students.push_back(student);
        } catch (...) {
            // Skip malformed records instead of stopping the application.
        }
    }
    return students;
}

bool saveStudents(const vector<Student>& students) {
    ofstream file(DATA_FILE.c_str());
    if (!file) {
        cout << "Error: Could not open " << DATA_FILE << " for writing.\n";
        return false;
    }

    for (const Student& student : students) {
        file << student.rollNumber << '|'
             << student.name << '|'
             << student.age << '|'
             << student.course << '|'
             << student.email << '\n';
    }

    if (!file) {
        cout << "Error: A problem occurred while saving student records.\n";
        return false;
    }
    return true;
}

int findStudent(const vector<Student>& students, const string& rollNumber) {
    for (size_t i = 0; i < students.size(); ++i)
        if (students[i].rollNumber == rollNumber) return static_cast<int>(i);
    return -1;
}

void addStudent() {
    vector<Student> students = loadStudents();
    Student student;

    cout << "\n--- Add Student ---\n";
    student.rollNumber = readText("Enter roll number: ");
    if (student.rollNumber.empty()) {
        cout << "Roll number cannot be empty.\n";
        return;
    }
    if (findStudent(students, student.rollNumber) != -1) {
        cout << "A student with this roll number already exists.\n";
        return;
    }

    student.name = readText("Enter student name: ");
    if (student.name.empty()) {
        cout << "Name cannot be empty. Student was not added.\n";
        return;
    }
    student.age = readAge();
    student.course = readText("Enter course: ");
    student.email = readText("Enter email: ");

    students.push_back(student);
    if (saveStudents(students)) cout << "Student record added successfully.\n";
}

void displayStudents() {
    vector<Student> students = loadStudents();
    cout << "\n--- Student Records ---\n";
    if (students.empty()) {
        cout << "No student records found.\n";
        return;
    }

    cout << left << setw(15) << "Roll Number"
         << setw(24) << "Name" << setw(8) << "Age"
         << setw(20) << "Course" << "Email\n";
    cout << string(85, '-') << '\n';

    for (const Student& student : students) {
        cout << left << setw(15) << student.rollNumber
             << setw(24) << student.name << setw(8) << student.age
             << setw(20) << student.course << student.email << '\n';
    }
}

void updateStudent() {
    vector<Student> students = loadStudents();
    cout << "\n--- Update Student ---\n";
    string rollNumber = readText("Enter the roll number to update: ");
    int index = findStudent(students, rollNumber);

    if (index == -1) {
        cout << "Student record not found.\n";
        return;
    }

    cout << "Enter the new details:\n";
    Student updated;
    updated.rollNumber = rollNumber;
    updated.name = readText("Enter student name: ");
    if (updated.name.empty()) {
        cout << "Name cannot be empty. Update cancelled.\n";
        return;
    }
    updated.age = readAge();
    updated.course = readText("Enter course: ");
    updated.email = readText("Enter email: ");

    students[index] = updated;
    if (saveStudents(students)) cout << "Student record updated successfully.\n";
}

void deleteStudent() {
    vector<Student> students = loadStudents();
    cout << "\n--- Delete Student ---\n";
    string rollNumber = readText("Enter the roll number to delete: ");
    int index = findStudent(students, rollNumber);

    if (index == -1) {
        cout << "Student record not found.\n";
        return;
    }

    cout << "Delete record for " << students[index].name
         << " (Roll No: " << students[index].rollNumber << ")? (y/n): ";
    string confirmation;
    getline(cin, confirmation);

    if (confirmation != "y" && confirmation != "Y") {
        cout << "Deletion cancelled.\n";
        return;
    }

    students.erase(students.begin() + index);
    if (saveStudents(students)) cout << "Student record deleted successfully.\n";
}

int readMenuChoice() {
    string input;
    int choice;
    char extra;
    cout << "\nEnter your choice: ";
    getline(cin, input);
    stringstream stream(input);
    if ((stream >> choice) && !(stream >> extra)) return choice;
    return -1;
}

int main() {
    cout << "====================================\n";
    cout << "       STUDENT MANAGEMENT SYSTEM    \n";
    cout << "====================================\n";

    while (true) {
        cout << "\n1. Add Student\n";
        cout << "2. Update Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Display Students\n";
        cout << "5. Exit\n";

        switch (readMenuChoice()) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: displayStudents(); break;
            case 5:
                cout << "Thank you for using the Student Management System!\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 5.\n";
        }
    }
}
