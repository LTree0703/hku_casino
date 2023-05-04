#include <iostream>

using namespace std;

void bankMenu() {
    system("CLS");
    cout << "Bank Options:" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "Enter the number corresponding to your choice: ";
}

void deposit(double &balance) {
    double amount;
    cout << "Enter the amount to deposit: ";
    cin >> amount;

    if (amount > 0) {
        balance += amount;
        cout << "Deposited " << amount << " successfully. New balance: " << balance << endl;
    } else {
        cout << "Invalid amount. Try again." << endl;
    }
}

void withdraw(double &balance) {
    double amount;
    cout << "Enter the amount to withdraw: ";
    cin >> amount;

    if (amount > 0 && amount <= balance) {
        balance -= amount;
        cout << "Withdrawn " << amount << " successfully. New balance: " << balance << endl;
    } else {
        cout << "Invalid amount. Try again." << endl;
    }
}
