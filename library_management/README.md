# Library Management System (C++)

A menu-driven console application for managing a small library using C++ structures, vectors, and file handling.

## Features

- Add books with unique IDs, titles, authors, and copy counts.
- Register library members with unique IDs.
- Display the book catalogue and registered members.
- Search books by title or author (partial text matches are supported).
- Issue a book to a registered member when a copy is available.
- Return a book using its book ID and member ID.
- Prevent duplicate IDs, duplicate active issues for the same member/book, and issuing unavailable books.
- Persist books, members, and active issue records between program runs.

## Concepts used

- C++ structures (struct)
- Vectors for in-memory collections
- Functions and modular program design
- File handling with ifstream and ofstream
- Input validation and searching

## Requirements

A C++ compiler supporting C++11 or later.

## Compile and run

### Windows (MinGW g++)

~~~bash
g++ -std=c++11 -Wall -Wextra -pedantic LibraryManagement.cpp -o LibraryManagement.exe
LibraryManagement.exe
~~~

### Linux / macOS

~~~bash
g++ -std=c++11 -Wall -Wextra -pedantic LibraryManagement.cpp -o LibraryManagement
./LibraryManagement
~~~

### Visual Studio

1. Create a C++ Console App project.
2. Add LibraryManagement.cpp.
3. Build and run the project.

## Menu

~~~text
1. Add Book
2. Register Member
3. Display Books
4. Display Members
5. Search Book by Title or Author
6. Issue Book
7. Return Book
8. Exit
~~~

## Data files

The program creates these files in its current working directory:

- books.txt — book details and copy availability.
- members.txt — registered member details.
- issues.txt — active book/member issue pairs.

Keep these files in the same working directory to retain data between runs. They are plain text files intended for this educational project only; do not store sensitive personal information in them.

## Project structure

~~~text
Intership/
└── library_management/
    ├── LibraryManagement.cpp
    └── README.md
~~~
