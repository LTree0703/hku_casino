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
