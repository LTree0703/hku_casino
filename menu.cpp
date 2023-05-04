#include "menu.hpp"

using namespace std;

void displayMenu() {
    system("CLS");
    cout << "Menu Options:" << endl;
    cout << "1. Restart Game" << endl;
    cout << "2. Bank" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter the number corresponding to your choice: ";
}

void restartGame() {
    // Code to restart the game
    cout << "Restarting the game..." << endl;
}

void exitGame() {
    cout << "Exiting the game..." << endl;
}

bool login() {
    std::string username, password;

    cout << "Enter your account name: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    return validateCredentials(username, password);
}

bool validateCredentials(const std::string& username, const std::string& password) {
    // Replace these hardcoded values with your desired account name and password
    const std::string validUsername = "player";
    const std::string validPassword = "password";

    return username == validUsername && password == validPassword;
}
