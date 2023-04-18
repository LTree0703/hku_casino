#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <alogorithm>

// #include "func.h"
/*Please use g++ -std=c++11 tpoker.cpp -o tpoker to test the program*/

using namespace std;

#define CARD_NUM 52
#define PLAYER_NUM 5

void read_file(string filename, string &text) // read the file and store it in a string
{
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        text += line + "\n";
    }
}

void clear() // clear console output
{
    cout << "\x1B[2J\x1B[H";
}

struct Card {
    int suitidx;
    int rankidx;
    string suit;
    string rank;
};

struct Player {
    string name;
    int chips;
    bool hasFolded;
    Card hole_card[2];
};

class Texas {
public:
    Texas();
    Card draw_card();
    void print_table();
    Player get_winner();

private:
    int phase; // 0 = start; 1 = fold; 2 = turn; 3 = river
    Card *community_cards;
    Player *players;
    int cards[CARD_NUM];
};

Texas::Texas()
{
    phase = 0;
    community_cards = new Card[5];
    players = new Player[CARD_NUM];

    // initialize the card deck: 0 = not drawn; 1 = drawn
    fill(cards, cards+CARD_NUM, 0);
    for (int i = 0; i < PLAYER_NUM; i++)
    {
        players[i].chips = rand() % 50 + 20;
        players[i].hasFolded = false;
        players[i].hole_card[0] = draw_card();
        players[i].hole_card[1] = draw_card();
        community_cards[i] = draw_card();
    }
}

Card Texas::draw_card()
{
    /* define indices:
        0~12 spade
        13~25 heart
        26~38 club
        29~51 diamond*/
    Card c;
    int idx = rand() % CARD_NUM;
    while (cards[idx] != 0)
    {
        idx = rand() % CARD_NUM;
    }
    cards[idx] = 1;
       
    c.suitidx = idx / 13;
    c.rankidx = idx % 13 + 2;

    switch (idx / 13) /*suit*/
    {
        case 0:
            c.suit = "♠"; // spade
            break;
        case 1:
            c.suit = "♥"; // heart
            break;
        case 2:
            c.suit = "♣"; // club
            break;
        case 3:
            c.suit = "♦"; // diamond
            break;
    }

    switch (idx % 13) /*rank*/
    {
        case 8:
            c.rank = "10";
            break;
        case 9:
            c.rank = "J "; // jack
            break;
        case 10:
            c.rank = "Q "; // queen
            break;
        case 11:
            c.rank = "K "; // king
            break;
        case 12:
            c.rank = "A "; // ace
            break;
        default:
            c.rank = to_string((idx+2) % 13) + " ";
            break;
    }
    return c;
}

string detect10(string rank)
{
    if (rank != "10")
    {
        rank = " " + rank.erase(1);
    }
    return rank;
}

void Texas::print_table()
{
    // TODO: access chips, player hole cards and community cards and print on terminal

    // TODO: render community cards



    // render hole cards
    cout << "You got:" << endl;
    Card c1 = players[0].hole_card[0];
    Card c2 = players[1].hole_card[1];
    cout << c1.rankidx << " " << c1.suitidx << " " << c2.rankidx << " " << c2.suitidx << endl;
    printf(".-------.    .-------.\n");
    printf("|%s     |    |%s     |\n", c1.rank.c_str(), c2.rank.c_str());
    printf("|       |    |       |\n");
    printf("|   %s   |    |   %s   |\n", c1.suit.c_str(), c2.suit.c_str());
    printf("|       |    |       |\n");
    printf("|     %s|    |     %s|\n", detect10(c1.rank).c_str(), detect10(c2.rank).c_str()); // cater with the situation where card rank = "10"
    printf("`-------'    `-------'\n");
}

int get_pattern_rank(int suit[7], int rank[7]);

Player Texas::get_winner()
{
    int highest_rank_player = -1;
    int highest_rank = 0;
    int *rank = new int[7];
    int *suit = new int[7];
    // store the data from the community cards
    for (int i = 0; i < 5; i++)
    {
        rank[i] = community_cards[i].rankidx;
        suit[i] = community_cards[i].suitidx;
    }

    for (int i = 0; i < PLAYER_NUM; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            rank[5+j] = players[i].hole_card[j].rankidx;
            suit[5+j] = players[i].hole_card[j].suitidx;
        }

        int current_rank = get_pattern_rank(suit, rank);
        if (current_rank > highest_rank)
        {
            highest_rank = current_rank;
            highest_rank_player = i;
        }
        else if (current_rank == highest_rank)
        {
            // TODO: declare another function here  
        }
    }
    return players[highest_rank_player];
}

void game_init();
bool game_round();

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
    
    cout << "♦" << endl;
    cout << R"( _____                       ___      _             )" << endl;
    cout << R"(/__   \_____  ____ _ ___    / _ \___ | | _____ _ __ )" << endl;
    cout << R"(  / /\/ _ \ \/ / _` / __|  / /_)/ _ \| |/ / _ \ '__|)" << endl;
    cout << R"( / / |  __/>  < (_| \__ \ / ___/ (_) |   <  __/ |   )" << endl;
    cout << R"( \/   \___/_/\_\__,_|___/ \/    \___/|_|\_\___|_|   )" << endl;
    cout << "\nWelcome to Texas Poker:)" << endl;
    cout << "Press \033[2menter\033[0m to continue...";
    cin.get();
    clear();

    int round_count = 1;
    while (1)
    {
        cout << "\n\033[1;34mGetting ready for round: " << round_count << "\033[0m" << endl;
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

bool game_round()
{
    int player_turn = 0;
    Texas dealer;
    cout << "Shuffling the cards and dealing..." << endl;
    sleep(1);
    dealer.print_table();
    // TODO: flop: rand three community cards + ask for input

    // TODO: turn: rand one community card + ask for input

    // TODO: river: rand one community card + ask for input

    // TODO: compare the rank of the players who doesn't fold
    dealer.get_winner();
    // TODO: break if the player chose fold

    // TODO: ask for command 
    return false;
}

int get_pattern_rank(int suit[7], int rank[7]){
    /*check rank,straight 
    2=2,3=3,...,J=11,Q=12,K=13,A=14;*/
    
    sort(rank, rank + 7);

    int str_rank = 0;
    for (int a = 2; a > -1; a--){
        int count_rank =0;
        for (int b = a; b < a + 5; b++){
        if (rank[b] + 1 == rank[b + 1]){
            count_rank ++;
        }}
        if (count_rank == 4){
            str_rank = 1;
            break;
        }}  
// check suit, flush
/* define card indices:
        0~12 spade
        13~25 heart
        26~38 diamond
        39~51 club*/
    int S = 0,H = 0,D = 0,C = 0,str_suit = 0;    
    for (int c = 0; c < 7; c ++){
        
        if (suit[c] <= 12){
            S++;
        }
        else if (suit[c] > 12 && suit[c] <= 25){
            H++;
        }
        else if (suit[c] > 25 && suit[c] <= 38){
            D++;
        }
        else{
            C++;
        }}      
    if (S >= 5 || H >= 5 || D >= 5 || C >= 5) {
        str_suit = 1;
    }   

    // check the three of a kind,two pair,one pair, fullhouse 

int three_of_a_kind = 0, two_pairs = 0, one_pairs = 0,  Four_of_a_kind = 0;
for (int d = 0; d < 7; d++) {
    int count_pattern = 1;
    for (int e = d + 1; e < 7; e++) {
        if (rank[d] == rank[e] && d != e && (rank[d] != -1 || rank[e] != -1)) {
            count_pattern++;
            rank[e] = -1;
        } 




    }
    if (count_pattern == 2) {
        one_pairs++; }
    else if (count_pattern == 3 ) {
            three_of_a_kind++;}  
    else if (count_pattern == 4) {
        Four_of_a_kind++;
    }

}  





    
    
    if (str_suit == 1 && str_rank == 1){
        cout << "Straight Flush !" << endl;
        return 8;        
    }
    else if (Four_of_a_kind >= 1){
        cout << "Four of a Kind !" << endl;
        return 7; }

    else if ((one_pairs > 0 && three_of_a_kind > 0) || three_of_a_kind == 2){
        cout << "Full House !" << endl;
        return 6;}

    else if (str_suit ==1 && str_rank != 1){
        cout << "Flush !" << endl;
        return 5;
    }
    else if (str_suit != 1 && str_rank == 1){
        cout << "Straight !" << endl;
        return 4;}

    else if (three_of_a_kind == 1 && one_pairs == 0){
        cout << "Three of a Kind !" << endl;
        return 3;}    

    else if (one_pairs >= 2 && three_of_a_kind == 0 ){
        cout << "Two Pairs !" << endl;
        return 2;} 

    else if (one_pairs == 1 && three_of_a_kind == 0){
        cout << "One Pairs !" << endl;
        return 1;}    
    else {
        cout << "No Special Pattern !";
        return 0;}
}

