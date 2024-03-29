#include <iostream>
#include <string> 
#include <cstdlib> 
#include <ctime>
using namespace std;

#include "func.h"
void rules();

void roulette_init(string &player_name, int &balance)
{
    string playerName = player_name;
    int bettingAmount;
    int guess;
    int dice; 
    string choice;
    srand((unsigned) time(NULL)); 
    do
    {
        clear();
        rules();
        cout << "\n\nYour current balance is $ " << balance << "\n";
        do
        {
            cout << "Hey, " << playerName <<", enter amount to bet : $";
            cin >> bettingAmount;
            if(bettingAmount > balance)
                cout << "Betting balance can't be more than current balance!\n"
                       <<"\nRe-enter balance\n ";
        }while(bettingAmount > balance);
        do
        {
            cout << "Guess any betting number between 1 & 10 :";
            cin >> guess;
            if(guess <= 0 || guess > 10)
                cout << "\nNumber should be between 1 to 10\n"
                    <<"Re-enter number:\n ";
        }while(guess <= 0 || guess > 10);
        dice = rand()%10 + 1;
        if(dice == guess)
        {
            cout << "\n\nYou are in luck!! You have won Rs." << bettingAmount * 10;
            balance = balance + bettingAmount * 3;
        }
        else
        {
            cout << "Oops, better luck next time !! You lost $ "<< bettingAmount <<"\n";
            balance = balance - bettingAmount;
        }
        cout << "\nThe winning number was : " << dice <<"\n";
        cout << "\n"<< playerName <<", You have balance of $ " << balance << "\n";
        if(balance <= 0)
        {
            cout << "You have no money to play ";
            cin.get(); cin.get();
            break;
        }
        cout << "\n\n-->Do you want to play again (y/n)? ";
        cin >> choice;
    }while(choice == "Y" || choice == "y");
    cout << "\n\n\n";
    cout << "\n\nThanks for playing the game. Your balance is $ " << balance << "\n\n";
    
}
void rules()
{
    clear();
    cout << "\t\t======CASINO NUMBER GUESSING RULES!======\n";
    cout << "\t1. Choose a number between 1 to 10\n";
    cout << "\t2. Winner gets 3 times of the money bet\n";
    cout << "\t3. Wrong bet, and you lose the amount you bet\n\n";
}
