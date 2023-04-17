#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>

// #include "func.h"
/*Please use g++ -std=c++11 tpoker.cpp -o tpoker to test the program*/

using namespace std;

#define CARD_NUM 52
#define PLAYER_NUM 5

struct Card {
    string suit;
    string rank;
};

struct Player {
    int chips;
    bool hasFolded;
    Card hole_card[2];
};

class Texas {
public:
    Texas();
    Card draw_card();
    void print_table();


private:
    Player players[PLAYER_NUM];
    int cards[CARD_NUM];
};

Texas::Texas()
{
    // initialize the card deck: 0 = not drawn; 1 = drawn
    fill(cards, cards+CARD_NUM, 0);
    for (int i = 0; i < PLAYER_NUM; i++)
    {
        players[i].chips = rand() % 50 + 20;
        players[i].hasFolded = false;
        players[i].hole_card[0] = draw_card();
        players[i].hole_card[1] = draw_card();
    }
}

void sort(int rank[7]){
    int newrank[7];
    for (int i = 0; i < 7;i++){
        for (int j = 0; i < 7; i++){
            if (rank[j] > rank[j + 1]){
                int temp = rank[j];
                rank[j] = rank[j + 1];
                rank[j + 1] = temp;
            }
}}}




Card Texas::draw_card()
{
    /* define card indices:
        0~12 spade
        13~25 heart
        26~38 diamond
        29~51 club*/
    Card c;
    int idx = rand() % CARD_NUM;
    while (cards[idx] != 0)
    {
        idx = rand() % CARD_NUM;
    }
    cards[idx] = 1;

    switch (idx / 13)
    {
        case 0:
            c.suit = "S";
            break;
        case 1:
            c.suit = "H";
            break;
        case 2:
            c.suit = "D";
            break;
        case 3:
            c.suit = "C";
            break;
    }

    switch (idx % 13)
    {
        case 0:
            c.rank = "A";
            break;
        case 10:
            c.rank = "J";
            break;
        case 11:
            c.rank = "Q";
            break;
        case 12:
            c.rank = "K";
            break;
        default:
            c.rank = to_string(idx % 13);
            break;
    }
    return c;
}

void print_table()
{
    // TODO: access chips and community cards and print on terminal
}

void game_init();
bool game_round();

void clear() // clear console output
{
    cout << "\x1B[2J\x1B[H";
}

int main()
{
    game_init();
    return 0;
}

void game_init()
{
    clear();
    // set seed value for generating random numbers
    srand((unsigned) time(NULL));
    
    cout << R"( _____                       ___      _             )" << endl;
    cout << R"(/__   \_____  ____ _ ___    / _ \___ | | _____ _ __ )" << endl;
    cout << R"(  / /\/ _ \ \/ / _` / __|  / /_)/ _ \| |/ / _ \ '__|)" << endl;
    cout << R"( / / |  __/>  < (_| \__ \ / ___/ (_) |   <  __/ |   )" << endl;
    cout << R"( \/   \___/_/\_\__,_|___/ \/    \___/|_|\_\___|_|   )" << endl;
    cout << "\nWelcome to Texas Poker:)" << endl;
    cout << "Press enter to continue..." << endl;
    cin.get();

    int round_count = 1;
    while (1)
    {
        cout << "\033[1;34mGetting ready for round: " << round_count << "\033[0m" << endl;
        if (!game_round()) // return true if continue, false otherwise
        {
            break;
        }
        else
        {
            round_count++;
        }
    }   

}


bool isRoyal_flush(string suit[7], int rank[7]);
bool isStraight_flush(string suit[7], int rank[7]);
bool isFour_of_a_kind(string suit[7], int rank[7]);
bool isFullhouse(string suit[7], int rank[7]);
bool isFlush(string suit[7], int rank[7]);
bool isStraight(string suit[7], int rank[7]);
bool isThree_of_a_kind(string suit[7], int rank[7]);
bool isTwopairs(string suit[7], int rank[7]);
bool isOnepaie(string suit[7], int rank[7]);

bool game_round()
{
    int player_turn = 0;
    Texas dealer;
    cout << "Shuffling the cards and dealing..." << endl;
    dealer.draw_card();


    // TODO: print out the table

    // TODO: flop: rand three community cards + ask for input

    // TODO: turn: rand one community card + ask for input

    // TODO: river: rand one community card + ask for input

    // TODO: compare the rank of the players who doesn't fold -> Paul

    // TODO: break if the player chose fold

    // TODO: ask for command 
    return false;
}

