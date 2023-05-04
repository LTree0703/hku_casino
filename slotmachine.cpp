#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void slot_init()
{
cout << "\n===============================================================================================";
cout << "\nH    H   K    K   U    U  CCCCC      A        SSSSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO     ";
cout << "\nH    H   K  K     U    U  CC        A  A      SS             III     NN N   NN   OO      OO    ";
cout << "\nHHHHHH   KKK      U    U  CC       A    A     SSSSSSSSS      III     NN  N  NN   OO      OO    ";
cout << "\nH    H   K  K     U    U  CC      AAAAAAAA           SS      III     NN   N NN   OO      OO    ";
cout << "\nH    H   K    K   UUUUUU. CCCCC  A        A   SSSSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO     ";
cout << "\n===============================================================================================\n";

    srand(time(0)); // seed the random number generator with the current time

    const int NUM_SYMBOLS = 7; // number of symbols in the slot machine
    const int JACKPOT_ODDS = 100; // odds of hitting the jackpot (1 in JACKPOT_ODDS)

    char symbols[NUM_SYMBOLS] = {'$', '#', '&', '@', '!', '~', '+'}; // array of symbols
    int credits = 10; // initial number of credits
    char choice; // player's choice to play again or not

    cout << "Welcome to the HKU CASINO Slot Machine!" << endl;

    do {
        cout << "You have " << credits << " credits. ";
        cout << "Press enter to spin the wheel";
        cin.ignore(); // wait for player to press Enter

        char reel1 = symbols[rand() % NUM_SYMBOLS]; // spin the reels
        char reel2 = symbols[rand() % NUM_SYMBOLS];
        char reel3 = symbols[rand() % NUM_SYMBOLS];

        cout << "   " << reel1 << "   " << reel2 << "   " << reel3 << endl;

        if (reel1 == reel2 && reel2 == reel3) { // all three reels match
            cout << "Jackpot!!! You won 100 credits!" << endl;
            credits += 100;
        } else if (reel1 == reel2 || reel1 == reel3 || reel2 == reel3) { // two reels match
            cout << "Two of a kind! You won 10 credits." << endl;
            credits += 10;
        } else { // no reels match
            cout << "Sorry, you didn't win anything this time." << endl;
            credits--;
        }

        if (credits <= 0) { // out of credits
            cout << "You're out of credits. Game over." << endl;
            break;
        }

        // check if player wants to play again
        cout << "Do you want to play again? (y/n)";
        cin >> choice;
        if (choice == 'n') {
            break;
        }

    } while (true);

    cout << "Thanks for playing the HKU Slot Machine! Goodbye!" << endl;

    return 0;
}
