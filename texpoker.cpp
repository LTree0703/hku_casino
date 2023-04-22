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
    bool hasFolded = false;
    Card hole_card[2];
};

class Texas {
public:
    Texas();
    Card draw_card();
    void print_table(int phase);
    void bet(string choice, int playeridx, int &bet); // returns an integer indicating the minimum number of chip required for call
    void game_flow();
    int get_winner(); // returns an integer indicating the index of the winner in the array players[]

private:
    int cards[CARD_NUM];
    int pot;
    Card community_cards[PLAYER_NUM];
    Player players[PLAYER_NUM];
};

Texas::Texas()
{
    pot = 0;

    // initialize the card deck: 0 = not drawn; 1 = drawn
    fill(cards, cards+CARD_NUM, 0);

    for (int i = 0; i < PLAYER_NUM; i++)
    {
        players[i].name = "Player " + to_string(i);
        players[i].chips = rand() % 50 + 20;
        players[i].hasFolded = false;
        players[i].hole_card[0] = draw_card();
        players[i].hole_card[1] = draw_card();
        community_cards[i].rank = "# ";
        community_cards[i].suit = "#";
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
            c.suit = "\033[2m♠\033[0m"; // spade
            break;
        case 1:
            c.suit = "\033[31m♥\033[0m"; // heart
            break;
        case 2:
            c.suit = "\033[2m♣\033[0m"; // club
            break;
        case 3:
            c.suit = "\033[31m♦\033[0m"; // diamond
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

void Texas::print_table(int phase)
{
    // TODO: access players' chips and print on console
    
    printf("  ______________________________________________\n");
    printf(" /                                              \\\n");
    printf("/                  Pot = %d chips                 \\\n", pot);   
    printf("|    .-----.  .-----. .-----. .-----. .-----.    |\n");
    printf("|    |%s   |  |%s   | |%s   | |%s   | |%s   |    |\n", community_cards[0].rank.c_str(), community_cards[1].rank.c_str(), community_cards[2].rank.c_str(), community_cards[3].rank.c_str(), community_cards[4].rank.c_str());
    printf("|    |  %s  |  |  %s  | |  %s  | |  %s  | |  %s  |    |\n", community_cards[0].suit.c_str(), community_cards[1].suit.c_str(), community_cards[2].suit.c_str(), community_cards[3].suit.c_str(), community_cards[4].suit.c_str());
    printf("|    |   %s|  |   %s| |   %s| |   %s| |   %s|    |\n", detect10(community_cards[0].rank).c_str(), detect10(community_cards[1].rank).c_str(), detect10(community_cards[2].rank).c_str(), detect10(community_cards[3].rank).c_str(), detect10(community_cards[4].rank).c_str());
    printf("|    `-----'  `-----' `-----' `-----' `-----'    |\n");
    printf("\\                                                /\n");
    printf(" \\______________________________________________/\n");
    printf("\n");

    // render hole card
    for (int i = 0; i < PLAYER_NUM; i++)
    {
        if (i == 0 && players[i].hasFolded)
            cout << "You got: (folded)" << endl;
        else if (i == 0)
            cout << "You got: " << endl;
        else if (players[i].hasFolded)
            cout << players[i].name << " got: (folded)" << endl;
        else
            cout << players[i].name << " got:" << endl;

        Card c1 = players[i].hole_card[0];
        Card c2 = players[i].hole_card[1];
        printf(".-----.    .-----.\n");
        printf("|%s   |    |%s   |\n", c1.rank.c_str(), c2.rank.c_str());
        printf("|  %s  |    |  %s  |\n", c1.suit.c_str(), c2.suit.c_str());
        printf("|   %s|    |   %s|\n", detect10(c1.rank).c_str(), detect10(c2.rank).c_str()); // cater with the situation where card rank = "10"
        printf("`-----'    `-----'\n");
        if (phase != 3)
        {
            break;
        }
    }
}

void Texas::bet(string choice, int playeridx, int &minimum_bet)
{
    if (choice == "1" && players[playeridx].chips > minimum_bet) // call
    {
        cout << "You chose to put " << minimum_bet << " chips!" << endl;
        players[playeridx].chips -= minimum_bet;
        pot += minimum_bet;
    }
    else if (choice == "2" && players[playeridx].chips > minimum_bet)  // raise
    {
        int raise = 0;
        cout << "How many chips would you like to raise?" << endl;
        while (1)
        {
            cin >> raise;
            if (players[playeridx].chips < raise)
                cout << "You don't have enough chips:(" << endl;
            else if (raise <= minimum_bet)
                cout << "The amount of raise cannot be less than the original amount!" << endl;
            else
                break;
        }
        cout << "You chose to put " << raise << " chips!" << endl;
        minimum_bet = raise;
        players[playeridx].chips -= raise;
        pot += raise;

    }
    else if (choice == "3")  // check
    {
        cout << "You chose to check, skipping this round..." << endl;
    }
    else if (choice == "4") // fold
    {
        cout << "You have chosen fold, skipping the remaining rounds..." << endl;
        sleep(1);
        players[playeridx].hasFolded = true;
    }
    else if (choice == "5") // all-in
    {
        pot += players[playeridx].chips;
        players[playeridx].chips = 0;
    }
    else
    {
        cout << "Invalid input. Please try again:(" << endl;
        sleep(1);
        cout << "Choose your bet: ";
        cin >> choice;
        bet(choice, playeridx, minimum_bet);
    }
}

void Texas::game_flow()
{
    int phase;
    for (phase = 0; phase < 3; phase++)
    {
        switch (phase)
        {
            case 0: // flop
                cout << "Round: FLOP" << endl;
                community_cards[0] = draw_card();
                community_cards[1] = draw_card();
                community_cards[2] = draw_card();
                break;
            case 1: // turn
                cout << "Round: TURN" << endl;
                community_cards[3] = draw_card();
                break;
            case 2: // river
                cout << "Round: RIVER" << endl;
                community_cards[4] = draw_card();
                break;
        }
        int minimum_bet = 1;
        if (!players[0].hasFolded)
        {
            print_table(phase);

            // player input bet
            string choice;
            cout << "(1) call" << endl;
            cout << "(2) raise" << endl;
            cout << "(3) check" << endl;
            cout << "(4) fold" << endl;
            cout << "(5) all-in" << endl;
            cout << "Choose your bet: (You have " << players[0].chips << " chips) ";
            cin >> choice; 
            bet(choice, 0, minimum_bet);
            cout << "Heading to another round..." << endl;
            sleep(1);
        }

        // NPC automatic bet
        for (int i = 1; i < PLAYER_NUM; i++)
        {
            if (players[i].hasFolded)
            {
                continue;
            }
            else if (players[i].chips >= minimum_bet)
            {
                players[i].chips -= minimum_bet;
                pot += minimum_bet;
            }
            else 
            {
                players[i].hasFolded = true;
            }
        }

        clear();
    }

    int winner = get_winner();

    cout << "RESULT" << endl;
    print_table(phase);
    cout << "So the winner of this round is: " << players[winner].name << "!" << endl;
    sleep(1);
    cout << players[winner].name << " + " << pot << " chips" << endl;
    players[winner].chips += pot;
}

int get_pattern_rank(int suit[7], int rank[7]);

int Texas::get_winner()
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
    delete[] rank; delete[] suit;
    return highest_rank_player;
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
    Texas *dealer = new Texas;
    cout << "Shuffling the cards and dealing..." << endl;
    sleep(1);

    dealer->game_flow();

    delete dealer;
    string choice;
    cout << "Continue playing? (Y/N) ";
    while (1)
    {
        cin >> choice;
        if (choice == "Y" || choice == "y")
        {
            clear();
            return true;
        }
        else if (choice == "N" || choice == "n")
        {
            clear();
            return false;
        }
        else
        {
            cout << "Invalid input. Please try again:(" << endl;
        }
    }
}

int get_pattern_rank(int suit[7], int rank[7])
{
    return 0;
}

