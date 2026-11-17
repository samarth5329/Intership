#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const string BOOK_FILE = "books.txt";
const string MEMBER_FILE = "members.txt";
const string ISSUE_FILE = "issues.txt";

struct Book {
    int id;
    string title;
    string author;
    int totalCopies;
    int availableCopies;
};

struct Member {
    int id;
    string name;
    string phone;
};

struct IssueRecord {
    int bookId;
    int memberId;
};

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

int readPositiveInt(const string& prompt) {
    while (true) {
        string input;
        cout << prompt;
        getline(cin, input);
        stringstream stream(input);
        int value;
        char extra;
        if ((stream >> value) && !(stream >> extra) && value > 0) return value;
        cout << "Please enter a valid positive number.\n";
    }
}

vector<string> splitLine(const string& line) {
    vector<string> fields;
    string field;
    stringstream stream(line);
    while (getline(stream, field, '|')) fields.push_back(field);
    return fields;
}

vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file(BOOK_FILE.c_str());
    string line;
    while (getline(file, line)) {
        vector<string> f = splitLine(line);
        if (f.size() != 5) continue;
        try {
            Book b;
            b.id = stoi(f[0]); b.title = f[1]; b.author = f[2];
            b.totalCopies = stoi(f[3]); b.availableCopies = stoi(f[4]);
            if (b.id > 0 && !b.title.empty() && !b.author.empty() &&
                b.totalCopies > 0 && b.availableCopies >= 0 &&
                b.availableCopies <= b.totalCopies) books.push_back(b);
        } catch (...) { /* Skip malformed records. */ }
    }
    return books;
}

vector<Member> loadMembers() {
    vector<Member> members;
    ifstream file(MEMBER_FILE.c_str());
    string line;
    while (getline(file, line)) {
        vector<string> f = splitLine(line);
        if (f.size() != 3) continue;
        try {
            Member m;
            m.id = stoi(f[0]); m.name = f[1]; m.phone = f[2];
            if (m.id > 0 && !m.name.empty()) members.push_back(m);
        } catch (...) { /* Skip malformed records. */ }
    }
    return members;
}

vector<IssueRecord> loadIssues() {
    vector<IssueRecord> issues;
    ifstream file(ISSUE_FILE.c_str());
    string line;
    while (getline(file, line)) {
        vector<string> f = splitLine(line);
        if (f.size() != 2) continue;
        try {
            IssueRecord r;
            r.bookId = stoi(f[0]); r.memberId = stoi(f[1]);
            if (r.bookId > 0 && r.memberId > 0) issues.push_back(r);
        } catch (...) { /* Skip malformed records. */ }
    }
    return issues;
}

bool saveBooks(const vector<Book>& books) {
    ofstream file(BOOK_FILE.c_str());
    if (!file) { cout << "Error: Cannot save book records.\n"; return false; }
    for (const Book& b : books)
        file << b.id << '|' << b.title << '|' << b.author << '|'
             << b.totalCopies << '|' << b.availableCopies << '\n';
    return static_cast<bool>(file);
}

bool saveMembers(const vector<Member>& members) {
    ofstream file(MEMBER_FILE.c_str());
    if (!file) { cout << "Error: Cannot save member records.\n"; return false; }
    for (const Member& m : members)
        file << m.id << '|' << m.name << '|' << m.phone << '\n';
    return static_cast<bool>(file);
}

bool saveIssues(const vector<IssueRecord>& issues) {
    ofstream file(ISSUE_FILE.c_str());
    if (!file) { cout << "Error: Cannot save issue records.\n"; return false; }
    for (const IssueRecord& r : issues)
        file << r.bookId << '|' << r.memberId << '\n';
    return static_cast<bool>(file);
}

int findBook(const vector<Book>& books, int id) {
    for (size_t i = 0; i < books.size(); ++i)
        if (books[i].id == id) return static_cast<int>(i);
    return -1;
}

int findMember(const vector<Member>& members, int id) {
    for (size_t i = 0; i < members.size(); ++i)
        if (members[i].id == id) return static_cast<int>(i);
    return -1;
}

void addBook() {
    vector<Book> books = loadBooks();
    cout << "\n--- Add Book ---\n";
    Book b;
    b.id = readPositiveInt("Enter book ID: ");
    if (findBook(books, b.id) != -1) { cout << "Book ID already exists.\n"; return; }
    b.title = readText("Enter book title: ");
    b.author = readText("Enter author name: ");
    if (b.title.empty() || b.author.empty()) { cout << "Title and author cannot be empty.\n"; return; }
    b.totalCopies = readPositiveInt("Enter number of copies: ");
    b.availableCopies = b.totalCopies;
    books.push_back(b);
    if (saveBooks(books)) cout << "Book added successfully.\n";
}

void registerMember() {
    vector<Member> members = loadMembers();
    cout << "\n--- Register Member ---\n";
    Member m;
    m.id = readPositiveInt("Enter member ID: ");
    if (findMember(members, m.id) != -1) { cout << "Member ID already exists.\n"; return; }
    m.name = readText("Enter member name: ");
    m.phone = readText("Enter phone number: ");
    if (m.name.empty()) { cout << "Member name cannot be empty.\n"; return; }
    members.push_back(m);
    if (saveMembers(members)) cout << "Member registered successfully.\n";
}

void displayBooks() {
    vector<Book> books = loadBooks();
    cout << "\n--- Book Catalogue ---\n";
    if (books.empty()) { cout << "No books found.\n"; return; }
    cout << left << setw(8) << "ID" << setw(30) << "Title"
         << setw(24) << "Author" << setw(12) << "Total" << "Available\n";
    cout << string(86, '-') << '\n';
    for (const Book& b : books)
        cout << left << setw(8) << b.id << setw(30) << b.title
             << setw(24) << b.author << setw(12) << b.totalCopies
             << b.availableCopies << '\n';
}

void displayMembers() {
    vector<Member> members = loadMembers();
    cout << "\n--- Library Members ---\n";
    if (members.empty()) { cout << "No members registered.\n"; return; }
    cout << left << setw(12) << "Member ID" << setw(28) << "Name" << "Phone\n";
    cout << string(55, '-') << '\n';
    for (const Member& m : members)
        cout << left << setw(12) << m.id << setw(28) << m.name << m.phone << '\n';
}

void searchBooks() {
    vector<Book> books = loadBooks();
    cout << "\n--- Search Books ---\n1. Search by title\n2. Search by author\n";
    string choice = readText("Choose search type: ");
    if (choice != "1" && choice != "2") { cout << "Invalid search option.\n"; return; }
    string query = readText(choice == "1" ? "Enter title: " : "Enter author: ");
    if (query.empty()) { cout << "Search text cannot be empty.\n"; return; }

    bool found = false;
    for (const Book& b : books) {
        const string& target = (choice == "1") ? b.title : b.author;
        if (target.find(query) != string::npos) {
            if (!found) cout << left << setw(8) << "ID" << setw(30) << "Title"
                             << setw(24) << "Author" << "Available\n";
            cout << left << setw(8) << b.id << setw(30) << b.title
                 << setw(24) << b.author << b.availableCopies << '\n';
            found = true;
        }
    }
    if (!found) cout << "No matching books found.\n";
}

void issueBook() {
    vector<Book> books = loadBooks();
    vector<Member> members = loadMembers();
    vector<IssueRecord> issues = loadIssues();
    cout << "\n--- Issue Book ---\n";
    int bookId = readPositiveInt("Enter book ID: ");
    int bookIndex = findBook(books, bookId);
    if (bookIndex == -1) { cout << "Book not found.\n"; return; }
    int memberId = readPositiveInt("Enter member ID: ");
    if (findMember(members, memberId) == -1) { cout << "Member not found. Register first.\n"; return; }
    if (books[bookIndex].availableCopies <= 0) { cout << "No copies are available.\n"; return; }
    for (const IssueRecord& r : issues)
        if (r.bookId == bookId && r.memberId == memberId) {
            cout << "This member already has this book issued.\n"; return;
        }

    --books[bookIndex].availableCopies;
    issues.push_back({bookId, memberId});
    if (saveBooks(books) && saveIssues(issues)) cout << "Book issued successfully.\n";
}

void returnBook() {
    vector<Book> books = loadBooks();
    vector<IssueRecord> issues = loadIssues();
    cout << "\n--- Return Book ---\n";
    int bookId = readPositiveInt("Enter book ID: ");
    int memberId = readPositiveInt("Enter member ID: ");
    int bookIndex = findBook(books, bookId);
    if (bookIndex == -1) { cout << "Book not found.\n"; return; }

    int issueIndex = -1;
    for (size_t i = 0; i < issues.size(); ++i)
        if (issues[i].bookId == bookId && issues[i].memberId == memberId) {
            issueIndex = static_cast<int>(i); break;
        }
    if (issueIndex == -1) { cout << "No active issue exists for this book and member.\n"; return; }

    issues.erase(issues.begin() + issueIndex);
    if (books[bookIndex].availableCopies < books[bookIndex].totalCopies)
        ++books[bookIndex].availableCopies;
    if (saveBooks(books) && saveIssues(issues)) cout << "Book returned successfully.\n";
}

int readMenuChoice() {
    string input = readText("\nEnter your choice: ");
    stringstream stream(input);
    int choice; char extra;
    if ((stream >> choice) && !(stream >> extra)) return choice;
    return -1;
}

int main() {
    cout << "========================================\n";
    cout << "        LIBRARY MANAGEMENT SYSTEM       \n";
    cout << "========================================\n";
    while (true) {
        cout << "\n1. Add Book\n2. Register Member\n3. Display Books\n4. Display Members\n";
        cout << "5. Search Book by Title or Author\n6. Issue Book\n7. Return Book\n8. Exit\n";
        switch (readMenuChoice()) {
            case 1: addBook(); break;
            case 2: registerMember(); break;
            case 3: displayBooks(); break;
            case 4: displayMembers(); break;
            case 5: searchBooks(); break;
            case 6: issueBook(); break;
            case 7: returnBook(); break;
            case 8: cout << "Thank you for using the Library Management System.\n"; return 0;
            default: cout << "Invalid choice. Select a number from 1 to 8.\n";
        }
    }
}
