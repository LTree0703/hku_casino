#include <iostream>

using namespace std;

// Display Game Menu
void displayMenu() {
    system("CLS");
    cout << "      - - - - - - - - - -" << endl;
    cout << "       H K U C A S I N O " << endl;
    cout << "      - - - - - - - - - -" << endl;
    cout << "Menu Options:" << endl;
    cout << "1. Restart Game" << endl;
    cout << "2. Bank" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter the number corresponding to your choice: ";
}

//Remind players' choice of exiting game
void exitGame() {
    cout << "Exiting the game..." << endl;
}

//Check whether players have successfully entered correct usenames and passwords
bool validateCredentials(const string& username, const string& password) {
    // Replace these hardcoded values with your desired account name and password
    const string validUsername = "player";
    const string validPassword = "password";

    return (username == validUsername && password == validPassword);
}

//Login by entering username and password and then check for correctness
bool login() {
    string username, password;

    cout << "Enter your account name: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    return validateCredentials(username, password);
}
