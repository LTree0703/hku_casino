#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <vector>

#include "func.h"

using namespace std;

#define CARD_NUM 52
#define PLAYER_NUM 5

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
    Texas(string &player_name, int &balance);
    Card draw_card();
    void print_table(int phase);
    void bet(string choice, int playeridx, int &bet); // returns an integer indicating the minimum number of chip required for call
    int game_flow();
    int get_winner(); // returns an integer indicating the index of the winner in the array players[]
    vector<Card> get_pattern(int player_id, int &rank);

private:
    int cards[CARD_NUM];
    int pot;
    Card community_cards[PLAYER_NUM];
    Player players[PLAYER_NUM];
};

bool operator > (const Card &a, const Card &b)
{
    if (a.rankidx > b.rankidx) 
        return true;
    else if (a.rankidx < b.rankidx)
        return false;
    return (a.suitidx > b.suitidx);
}

Texas::Texas(string &player_name, int &balance)
{
    pot = 0;
    // initialize the card deck: 0 = not drawn; 1 = drawn
    fill(cards, cards+CARD_NUM, 0);

    for (int i = 0; i < PLAYER_NUM; i++)
    {   if (i == 0)
        {
            players[i].name = player_name;
            players[i].chips = balance;
        }
        else
        {
            players[i].name = "Player " + to_string(i);
            players[i].chips = rand() % balance + 30;
        }
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

string format(int pot)
{
    if (pot < 10)
        return "  " + to_string(pot);
    else if (pot >= 100)
        return to_string(pot);
    else
        return " " + to_string(pot);

}

void Texas::print_table(int phase)
{

    // print the table of community cards on console
    printf("  ______________________________________________\n");
    printf(" /                                              \\\n");
    printf("/                  Pot = %s chips               \\\n", format(pot).c_str());   
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
        if (phase != 3) // only print other players' hole cards after round river
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
        sleep(1);
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
        minimum_bet = players[playeridx].chips;
        players[playeridx].chips = 0;
        cout << "You have chosen all-in! skipping the remaining rounds..." << endl;
    }
    else if (choice == "man")
    {
        clear();
        string line;
        ifstream man("texa_rule.txt");
        while (getline(man, line))
            cout << line << endl;
        cout << "Press enter to continue...";
        cin.get(); cin.get();
        clear();
        print_table(0);
        cout << "(1) call" << endl;
        cout << "(2) raise" << endl;
        cout << "(3) check" << endl;
        cout << "(4) fold" << endl;
        cout << "(5) all-in" << endl;
        cout << "(Type 'man' for game rules)" << endl;
        cout << "Choose your bet: (You have " << players[0].chips << " chips) ";
        cin >> choice;
        bet(choice, playeridx, minimum_bet);
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

int Texas::game_flow()
{
    int phase, minimum_bet = 1;
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
        if (!players[0].hasFolded && players[0].chips > 0)
        {
            print_table(phase);

            // player input bet
            string choice;
            cout << "(1) call" << endl;
            cout << "(2) raise" << endl;
            cout << "(3) check" << endl;
            cout << "(4) fold" << endl;
            cout << "(5) all-in" << endl;
            cout << "(Type 'man' for game rules)" << endl;
            cout << "Choose your bet: (You have " << players[0].chips << " chips) ";
            cin >> choice; 
            bet(choice, 0, minimum_bet);
            if (!players[0].hasFolded && players[0].chips > 0) // player status does not change
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
            else if (players[0].chips == 0)
            {
                players[i].hasFolded = false;
            }
            else
            {
                players[i].hasFolded = true;
            }
        }

        clear();
    }

    cout << "RESULT" << endl;
    print_table(phase);
    int winner = get_winner();
    sleep(1);
    cout << endl << "So the winner of this round is: " << players[winner].name << "!" << endl;
    sleep(1);
    cout << players[winner].name << " + " << pot << " chips" << endl;
    players[winner].chips += pot;
    
    return players[0].chips;
}

int Texas::get_winner()
{
    int highest_rank_player = -1;
    int highest_rank = 0;
    // int *rank = new int[7];
    // int *suit = new int[7];

    for (int i = 0; i < PLAYER_NUM; i++)
    {
        if (players[i].hasFolded)
            continue;

        int current_rank = 0;
        cout << players[i].name << " got: ";

        vector<Card> c = get_pattern(i, current_rank);

        switch(current_rank)
        {
            case 8:
                cout << "Straight Flush!";
                break;
            case 7:
                cout << "Four of a kind!";
                break;
            case 6:
                cout << "Full House!";
                break;
            case 5:
                cout << "Flush!";
                break;
            case 4:
                cout << "Straight!";
                break;
            case 3:
                cout << "Three of a kind!";
                break;
            case 2:
                cout << "Two pairs!";
                break;
            case 1:
                cout << "One pair!";
                break;
            case 0:
                cout << "No specific pattern!";
                break;
        }
        cout << endl;

        if (current_rank > highest_rank)
        {
            highest_rank = current_rank;
            highest_rank_player = i;
        }
        else if (current_rank == highest_rank)
        {
            vector<Card> highest = get_pattern(highest_rank_player, current_rank);
            // if condition satisfied, change the highest rank player
            if (highest[0].rankidx < c[0].rankidx || (highest[0].rankidx == c[0].rankidx && highest[0].suitidx > c[0].suitidx)) // cards with smaller suitidx are larger
            {
                highest_rank_player = i;
            }
        }
    }
    return highest_rank_player;
}

vector<Card> Texas::get_pattern(int player_id, int &rank)
{
    vector<Card> c;

    // collect hand info
    Card tmp;
    int i, j;
    for (i = 0; i < 5; i++)
    {
        tmp.rankidx = community_cards[i].rankidx;
        tmp.suitidx = community_cards[i].suitidx;
        c.push_back(tmp);
    }
    for (i = 0; i < 2; i++)
    {
        tmp.rankidx = players[player_id].hole_card[i].rankidx;
        tmp.suitidx = players[player_id].hole_card[i].suitidx;
        c.push_back(tmp);
    }
    sort(c.begin(), c.end(), greater<Card>());
    const int size = c.size();
    vector<Card> pattern = {};
    
    // straight flush
    bool isStraightFlush = false;
    for (i = 0; i < size-4; i++)
    {
        for (j = 1; j < 5; j++)
        {
            if ((c[i].rankidx != c[i+j].rankidx - j) || (c[i].suitidx != c[i+j].suitidx))
                break;
            if (j == 4)
                isStraightFlush = true;
        }
        if (isStraightFlush)
        {
            rank = 8;
            for (j = 0; j < 5; j++)
            {
                pattern.push_back(c[i+j]);
            }
            return pattern;
        }
    }

    // Four of a kind
    bool isFour = false;
    for (i = 0; i < size-3; i++)
    {
        if (c[i].rankidx == c[i+1].rankidx && c[i].rankidx == c[i+2].rankidx && c[i].rankidx == c[i+3].rankidx)
        {
            isFour = true;
        }
        if (isFour)
        {
            rank = 7;
            for (j = 0; j < 4; j++)
            {
                pattern.push_back(c[i+j]);
            }
            return pattern;
        }
    }

    // Flush
    int count = 0;
    for (i = 0; i < 4; i++)
    {
        count = 0;
        for (j = 0; j < size; j++)
        {
            if (c[j].suitidx == i)
            {
                count++;
            }
        }
        if (count == 5) // isFlush
        {
            rank = 5;
            for (j = 0; j < size; j++)
            {
                if (c[j].suitidx == i)
                {
                    pattern.push_back(c[j]);
                }
            }
            return pattern;
        }     
    }

    // Straight
    bool isStraight = false;
    for (i = 0; i < 3; i++)
    {
        for (j = 1; j < 5; j++)
        {
            if (c[i].rankidx != c[i+j].rankidx - j)
                break;
            if (j == 4)
                isStraight = true;
        }
        if (isStraight)
        {
            rank = 4;
            for (j = 0; j < 5; j++)
            {
                pattern.push_back(c[i+j]);
            }
            return pattern;
        }
    }

    // Full House OR Three of a kind OR one pair
    bool hasThree = false;
    int three_value = -1;
    for (i = 0; i < size-2; i++)
    {
        if (c[i].rankidx == c[i+1].rankidx && c[i].rankidx == c[i+2].rankidx)
        {
            hasThree = true;
            three_value = c[i].rankidx;
            for (j = 0; j < 3; j++)
            {
                pattern.push_back(c[i+j]);
            }
            break;
        }
    }
    if (hasThree) // has three of a kind, find for a pair to get full house
    {
        for (i = 0; i < size-1; i++)
        {
            if (c[i].rankidx == c[i+1].rankidx && c[i+1].rankidx != three_value)
            {
                rank = 6;
                pattern.push_back(c[i]);
                pattern.push_back(c[i+1]);
                return pattern;
            }
        }
        rank = 3;
    }
    else // find for a pair or two pairs
    {  
        int pair_count = 0;
        for (i = 0; i < size-1; i++)
        {
            if (c[i].rankidx == c[i+1].rankidx && c[i+1].rankidx != three_value)
            { 
                pair_count++;
                pattern.push_back(c[i]);
                pattern.push_back(c[i+1]);
            }
            if (pair_count == 2)  // break if two pairs are found
            {
                break;
            }
        }
        if (pair_count == 2)
        {
            rank = 2;
            return pattern;
        }
        else if (pair_count == 1)
        {
            rank = 1;
            return pattern;
        }
        else 
        {
            rank = 0;
        }
    }
    // No specific pattern, return the largest card
    pattern.push_back(c[0]);
    return pattern;
}

bool game_round(string &player_name, int &balance);

void texpoker_init(string &player_name, int &balance)
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
    cin.get(); cin.get();
    clear();

    int round_count = 1;
    while (1)
    {
        cout << "\n\033[1;34mGetting ready for round: " << round_count << "\033[0m" << endl;
        if (!game_round(player_name, balance)) // return true if continue, false otherwise
        {
            break;
        }
        else
        {
            round_count++;
        }
    }
}

bool game_round(string &player_name, int &balance)
{
    Texas *dealer = new Texas(player_name, balance);
    cout << "Shuffling the cards and dealing..." << endl;
    sleep(1);

    balance = dealer->game_flow();
    
    delete dealer;
    string choice;
    if (balance <= 0)
    {
        cout << "Sorry but you have no chips now..." << endl;
        cout << "Press enter to return to menu...";
        cin.get(); cin.get();
        return false;
    }
    cout << "Do you want to play again? (y/n) ";
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
            cout << "Thanks for playing Texas Poker:)" << endl;
            sleep(1);
            clear();
            return false;
        }
        else
        {
            cout << "Invalid input. Please try again:(" << endl;
        }
    }
}
