# Student Management System (C++)

A menu-driven console application for managing student records, created for the C++ Programming internship task.

## Features

- Add a student record.
- Update student details using the roll number.
- Delete a record after confirmation.
- Display all saved student records.
- Store records in a text file so they remain available after the program closes.
- Validate menu choices and student ages.
- Prevent duplicate roll numbers.

## Student information

Each record contains a roll number, name, age, course, and email.

## Requirements

- A C++ compiler supporting C++11 or later.
- Windows, macOS, or Linux.

## Compile and run

### Windows (MinGW g++)

Open Command Prompt or the VS Code terminal in this folder:

~~~bash
g++ -std=c++11 -Wall -Wextra -pedantic student_management.cpp -o student_management.exe
student_management.exe
~~~

### Linux / macOS

~~~bash
g++ -std=c++11 -Wall -Wextra -pedantic student_management.cpp -o student_management
./student_management
~~~

### Visual Studio

1. Create or open a C++ Console App project.
2. Add student_management.cpp to the project.
3. Build and run the project.

## Data storage

The application creates students.txt in the program's current working directory when records are saved. Each line stores one student record. Keep this file in the same working directory when reopening the application to retain records.

The data file is intentionally not committed to Git because it may contain personal information.

## Menu

~~~text
1. Add Student
2. Update Student
3. Delete Student
4. Display Students
5. Exit
~~~

## Notes

- Roll numbers must be unique.
- Names and course names can contain spaces.
- The application asks for confirmation before deleting a record.
- The program uses C++ file streams (ifstream and ofstream) to load and save records.

## Project structure

~~~text
Intership/
├── student_management.cpp
├── README.md
└── .gitignore
~~~
