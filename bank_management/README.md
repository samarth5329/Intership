# Bank Management Application (C++)

A console-based banking application built with object-oriented C++ and file handling.

## Features

- Create customer accounts with unique account numbers.
- Deposit money into an account.
- Withdraw money, with an insufficient-balance check.
- Check an account balance.
- Display all customer accounts.
- Save account records to a text file so data persists between runs.
- Validate account numbers, amounts, and menu selections.

## Concepts used

- Classes and objects
- Encapsulation using private data members and public methods
- Constructors
- Vectors for managing account records in memory
- File handling with ifstream and ofstream
- Input validation and conditional statements

## Requirements

A C++ compiler supporting C++11 or later (GCC, MinGW, or Visual Studio).

## Compile and run

### Windows (MinGW g++)

~~~bash
g++ -std=c++11 -Wall -Wextra -pedantic BankManagement.cpp -o BankManagement.exe
BankManagement.exe
~~~

### Linux / macOS

~~~bash
g++ -std=c++11 -Wall -Wextra -pedantic BankManagement.cpp -o BankManagement
./BankManagement
~~~

### Visual Studio

1. Create a C++ Console App project.
2. Add BankManagement.cpp to the project.
3. Build and run.

## Menu

~~~text
1. Create Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. Display All Accounts
6. Exit
~~~

## Data storage

The application creates bank_accounts.txt in the program's current working directory when an account is saved. Keep this file in that directory to retain account records between runs.

The text file is intended only for this educational demonstration. It is not encrypted and this project is not suitable for real banking or storing real customer financial information. It does not implement authentication, authorization, transaction auditing, or production-grade security.

## Project structure

~~~text
Intership/
└── bank_management/
    ├── BankManagement.cpp
    └── README.md
~~~
