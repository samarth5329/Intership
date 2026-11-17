#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

const string DATA_FILE = "bank_accounts.txt";

class BankAccount {
private:
    long long accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount() : accountNumber(0), accountHolder(""), balance(0.0) {}

    BankAccount(long long number, const string& holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    long long getAccountNumber() const { return accountNumber; }
    string getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }

    bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        return true;
    }

    void display() const {
        cout << left << setw(18) << accountNumber
             << setw(26) << accountHolder
             << fixed << setprecision(2) << balance << '\n';
    }
};

string cleanField(string value) {
    for (char& ch : value) {
        if (ch == '|') ch = '/';
    }
    return value;
}

vector<BankAccount> loadAccounts() {
    vector<BankAccount> accounts;
    ifstream file(DATA_FILE.c_str());
    string line;

    while (getline(file, line)) {
        stringstream stream(line);
        string numberText, holder, balanceText, extra;

        if (!getline(stream, numberText, '|') ||
            !getline(stream, holder, '|') ||
            !getline(stream, balanceText, '|') ||
            getline(stream, extra, '|')) {
            continue;
        }

        try {
            long long number = stoll(numberText);
            double balance = stod(balanceText);

            if (number > 0 && !holder.empty() && balance >= 0.0) {
                accounts.push_back(BankAccount(number, holder, balance));
            }
        } catch (...) {
            // Ignore malformed lines and continue loading other accounts.
        }
    }

    return accounts;
}

bool saveAccounts(const vector<BankAccount>& accounts) {
    ofstream file(DATA_FILE.c_str());
    if (!file) {
        cout << "Error: Unable to save account records.\n";
        return false;
    }

    file << fixed << setprecision(2);
    for (const BankAccount& account : accounts) {
        file << account.getAccountNumber() << '|'
             << cleanField(account.getAccountHolder()) << '|'
             << account.getBalance() << '\n';
    }

    if (!file) {
        cout << "Error: A problem occurred while writing account records.\n";
        return false;
    }
    return true;
}

int findAccount(const vector<BankAccount>& accounts, long long number) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getAccountNumber() == number) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

long long readAccountNumber(const string& prompt) {
    while (true) {
        string input;
        cout << prompt;
        getline(cin, input);

        stringstream stream(input);
        long long number;
        char extra;
        if ((stream >> number) && !(stream >> extra) && number > 0) {
            return number;
        }
        cout << "Please enter a valid positive account number.\n";
    }
}

double readAmount(const string& prompt) {
    while (true) {
        string input;
        cout << prompt;
        getline(cin, input);

        stringstream stream(input);
        double amount;
        char extra;
        if ((stream >> amount) && !(stream >> extra) &&
            amount > 0.0 && amount <= 1000000000000.0) {
            return amount;
        }
        cout << "Please enter a valid amount greater than zero.\n";
    }
}

int readMenuChoice() {
    string input;
    cout << "\nEnter your choice: ";
    getline(cin, input);

    stringstream stream(input);
    int choice;
    char extra;
    if ((stream >> choice) && !(stream >> extra)) return choice;
    return -1;
}

void createAccount() {
    vector<BankAccount> accounts = loadAccounts();

    cout << "\n--- Create New Account ---\n";
    long long number = readAccountNumber("Enter account number: ");

    if (findAccount(accounts, number) != -1) {
        cout << "An account with this number already exists.\n";
        return;
    }

    string holder;
    cout << "Enter account holder name: ";
    getline(cin, holder);
    holder = cleanField(holder);

    if (holder.empty()) {
        cout << "Account holder name cannot be empty.\n";
        return;
    }

    accounts.push_back(BankAccount(number, holder, 0.0));
    if (saveAccounts(accounts)) {
        cout << "Account created successfully. Opening balance: 0.00\n";
    }
}

void depositMoney() {
    vector<BankAccount> accounts = loadAccounts();

    cout << "\n--- Deposit Money ---\n";
    long long number = readAccountNumber("Enter account number: ");
    int index = findAccount(accounts, number);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    double amount = readAmount("Enter deposit amount: ");
    accounts[index].deposit(amount);

    if (saveAccounts(accounts)) {
        cout << "Deposit successful. Updated balance: "
             << fixed << setprecision(2) << accounts[index].getBalance() << '\n';
    }
}

void withdrawMoney() {
    vector<BankAccount> accounts = loadAccounts();

    cout << "\n--- Withdraw Money ---\n";
    long long number = readAccountNumber("Enter account number: ");
    int index = findAccount(accounts, number);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    double amount = readAmount("Enter withdrawal amount: ");

    if (!accounts[index].withdraw(amount)) {
        cout << "Withdrawal failed. Insufficient balance.\n";
        return;
    }

    if (saveAccounts(accounts)) {
        cout << "Withdrawal successful. Updated balance: "
             << fixed << setprecision(2) << accounts[index].getBalance() << '\n';
    }
}

void checkBalance() {
    vector<BankAccount> accounts = loadAccounts();

    cout << "\n--- Balance Enquiry ---\n";
    long long number = readAccountNumber("Enter account number: ");
    int index = findAccount(accounts, number);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    cout << "Account holder: " << accounts[index].getAccountHolder() << '\n';
    cout << "Account number: " << accounts[index].getAccountNumber() << '\n';
    cout << "Available balance: " << fixed << setprecision(2)
         << accounts[index].getBalance() << '\n';
}

void displayAccounts() {
    vector<BankAccount> accounts = loadAccounts();

    cout << "\n--- Customer Accounts ---\n";
    if (accounts.empty()) {
        cout << "No accounts found.\n";
        return;
    }

    cout << left << setw(18) << "Account Number"
         << setw(26) << "Account Holder" << "Balance\n";
    cout << string(58, '-') << '\n';

    for (const BankAccount& account : accounts) {
        account.display();
    }
}

int main() {
    cout << "========================================\n";
    cout << "        BANK MANAGEMENT APPLICATION     \n";
    cout << "========================================\n";

    while (true) {
        cout << "\n1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Exit\n";

        switch (readMenuChoice()) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: displayAccounts(); break;
            case 6:
                cout << "Thank you for using the Bank Management Application.\n";
                return 0;
            default:
                cout << "Invalid choice. Please select a number from 1 to 6.\n";
        }
    }
}
