#include <iostream>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <string>

#include "func.h"
#include "menu.h"
#include "bank.h"
#include "roulette.h"
#include "texpoker.h"
#include "slotmachine.h"

using namespace std;


void game_init();
void game_menu();
void setup_player();
void alter_value(string name, int chips);

int main() 
{
    clear();
    cout << "__   __  ___   _  __   __    _______  _______  _______  ___   __    _  ________ " << endl;
    cout << "|  | |  ||   | | ||  | |  |  |       ||   _   ||       ||   | |  |  | ||       |" << endl;
    cout << "|  |_|  ||   |_| ||  | |  |  |       ||  |_|  ||  _____||   | |   |_| ||   _   |" << endl;
    cout << "|       ||      _||  |_|  |  |       ||       || |_____ |   | |       ||  | |  |" << endl;
    cout << "|       ||     |_ |       |  |      _||       ||_____  ||   | |  _    ||  |_|  |" << endl;
    cout << "|   _   ||    _  ||       |  |     |_ |   _   | _____| ||   | | | |   ||       |" << endl;
    cout << "|__| |__||___| |_||_______|  |_______||__| |__||_______||___| |_|  |__||_______|" << endl;
    cout << "Loading game..." << endl;
    sleep(1);
    game_init();
    return 0;
}

void game_init()
{
    clear();
    // check if user data exists
    bool newGame = false;
    ifstream user("data.txt");
    if (!user.good())
    {
        newGame = true;
    }

    ifstream fin;
    fin.open("menu.txt");
    string menu, line;
    int line_count = 0;
    if (fin.fail())
    {
        cout << "An error occurred, please try again." << endl;
        return;
    }
    while (getline(fin, line))
    {
        line_count++;
        if (line_count == 8 && !newGame)
            menu += "|                  New Profile  (3)                  |\n";
        else if (line_count == 10)
            menu += line;
        else
            menu += line + "\n";
    }
    fin.close();

    string input;
    while (true)
    {
        cout << menu << endl;
        cout << "Please choose an option... ";
        getline(cin, input);
        if (input == "1")
        {
            if (newGame)
                setup_player();
            break;
        }
        else if (input == "2")
        {
            cout << "Thanks for playing!" << endl;
            exit(0);
        }
        else if (input == "3")
        {
            setup_player();
            break;
        }
        cout << "Invalid output, please try again." << endl;
    }
    game_menu();
}

void game_menu()
{
    // load player data
    static string player_name;
    static int chips;
    ifstream fin;

    // load into game menu
    while (true)
    {
        clear();
        // fetch user data
        fin.open("data.txt");
        if (fin.fail())
        {
            cout << "Seems like player data is missing/crashed, please set up a new user profile:(" << endl;
            cout << "Exiting Game..." << endl;
            return;
        }
        fin >> player_name;
        fin >> chips;
        fin.close();

        // print menu on console
        fin.open("game.txt");
        if (fin.fail())
        {
            cout << "An error occurred, please try again." << endl;
            return;
        }
        string line;
        while (getline(fin,line))
        {
            cout << line << endl;
        }
        fin.close();
        cout << "Hello, " << player_name << ". You currently have " << chips << " chips." << endl;
        cout << "Which game do you want to play? ";
        // wait for choice 
        string choice;
        getline(cin, choice);
        if (choice == "1")
        {
            roulette_init(player_name, chips);
        }
        else if (choice == "2")
        {
            slot_init(player_name, chips);
        }
        else if (choice == "3")
        {
            texpoker_init(player_name, chips);
        }
        else if (choice == "4")
        {
            game_init();
        }
        else
        {
            cout << "Invalid input, please try again." << endl;
        }
        alter_value(player_name, chips);
    }
}

void setup_player()
{
    string name;
    int init_chips = 100;

    cout << "Please enter your name: ";
    getline(cin, name);
    cout << "Welcome " << name << "!" << endl;
    cout << "You are given " << init_chips << " chips as your initial fund. Enjoy the game!" << endl;
    cout << "Press enter to continue...";
    cin.get();

    // store data into file
    ofstream fout("data.txt");
    fout << name << endl;
    fout << init_chips;
    fout.close();
}

void alter_value(string player_name, int chips)
{
    ofstream fout("data.txt");
    fout << player_name << endl;
    fout << chips;
    fout.close();
}