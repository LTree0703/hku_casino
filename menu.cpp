#include <iostream>

using namespace std;

void displayMenu() {
    system("CLS");
    cout << "Menu Options:" << endl;
    cout << "1. Restart Game" << endl;
    cout << "2. Bank" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter the number corresponding to your choice: ";
}

void exitGame() {
    cout << "Exiting the game..." << endl;
}

bool validateCredentials(const string& username, const string& password) {
    // Replace these hardcoded values with your desired account name and password
    const string validUsername = "player";
    const string validPassword = "password";

    return (username == validUsername && password == validPassword);
}

bool login() {
    string username, password;

    cout << "Enter your account name: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    return validateCredentials(username, password);
}
