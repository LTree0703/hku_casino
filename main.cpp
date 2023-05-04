#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

#include "func.h"

using namespace std;

int main()
{
    clear();
    string menu;
    read_file("menu.txt", menu);
    while (1)
    {
        cout << menu;
        cin.get();
        clear();
    }
}

#include <iostream>
#include <conio.h>
#include "menu.hpp"
#include "bank.hpp"

using namespace std;

int main() {
    double balance = 1000.0;
    char input;

    cout << "Welcome to the Casino Game!" << endl;

    while (!login()) {
        cout << "Invalid account name or password. Please try again." << endl;
    }

    cout << "Login successful. Enjoy the game!" << endl;

    while (true) {
        cout << "Press ESC to open the menu." << endl;
        input = _getch();

        if (input == 27) { // ASCII code for ESC key
            displayMenu();
            input = _getch();

            switch (input) {
                case '1':
                    restartGame();
                    break;
                case '2':
                    bankMenu();
                    input = _getch();
                    if (input == '1') {
                        deposit(balance);
                    } else if (input == '2') {
                        withdraw(balance);
                    }
                    break;
                case '3':
                    exitGame();
                    return 0;
                default:
                    cout << "Invalid input. Try again." << endl;
            }
        }
    }
    return 0;
}

