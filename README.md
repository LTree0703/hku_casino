# hku_casino

An ENGG1340/COMP2113 (2022/2023 Semester 2) project

![](https://img.shields.io/badge/Language-C%2B%2B11-blue.svg)

## Team Members

**Group 100**

samchong0302 - Chong Chak Yu 3035691602 (`main.cpp`)

k-kwong - Kwong Tsz Kong 3035924126 (`texa_rule.txt`, `texpoker.cpp` and `main.cpp`)

LTree0703 - Pang Tin Hei 3036100179 (`texpoker.cpp` and `main.cpp`)

jaimielee14 - Lee Jaimie (`slotmachine.cpp`)

dawon92 - Chung Dawon (`roulette.cpp`)

## Game Description

**This is a single-player text-based game that is to be played on the terminal.**

Our game is a collection of three mini casino games, including **roulette**, **slot machine** and **texas poker**. 
In this game, users need to create a local profile that is initialized with 100 chips to enter our casino. If the player has lost all the chips, he/she will be considered ***game over*** and the user profile will be deleted.

1. Roulette

- This is a simple number guessing game, in which players can guess a number ranging from 1 to 10. *(The number of bet is decided by the players.)* If they guessed correctly, they will be awarded three times of thier betting amount.

2. Slot machine

- This is a simple slot machine, containing 7 symbols. *(The number of bet is 1 per each round.)* At each round, the slot machine will randomly generate 3 symbols. If two of them are the same, 10 chips will be awarded and 100 chips will be awarded if three of them are the same (i.e., jackpot).

3. Texas Poker (Texas Hold'em)

- This is a simple Texas poker game with rules that is *a little bit different* from the real one. 
- For each game round, the players have to bet 3 times (known as **flop**, **turn** and **river**), and the default amount of bet is 1 chip (*call* option, yet the amount could be increased by doing *raise* option). 
- Also, the players could choose to skip one bet (*check* option), stop betting if they would like to give up (*fold* option), or bet all of their chips if they are feeling good (*all-in* option).
- The players have to obtain a specific pattern from 5 poker cards from a combination of 7 poker cards (2 hole cards + 5 community cards). The highest 
- **For details of the game rule, please refer to [texa_rule.txt](https://github.com/LTree0703/hku_casino/blob/main/texa_rule.txt)**

## Game Features
How we meet the 5 coding requirements
### Generation of random game sets or events

`srand()` and `rand()` functions are used in all of our mini-games for randomly generating numbers, symbols and draw cards.

in roulette.cpp

### Data structures for storing game status

As the rule of Texas poker is still quite complicated, self-defined data structures are used for storing game status in `texpoker.cpp`, which would be easier for function adjustments and appendments.
```cpp
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
        void bet(string choice, int playeridx, int &bet);
        int game_flow();
        int get_winner(); 
        vector<Card> get_pattern(int player_id, int &rank);

        private:
        int cards[CARD_NUM];
        int pot;
        Card community_cards[PLAYER_NUM];
        Player players[PLAYER_NUM];
};
```
### Dynamic memory management

- For each round of texas poker, a new Texas variable will be dynamically allocated memory and delete after each round using `new` and `delete`.

```cpp
Texas *dealer = new Texas(player_name, balance);
```

- `vectors` are also used in `texpoker.cpp` for easier implementation of the pattern determination and comparison.

### File input/output

- our game will create a local `data.txt` file to store your own username well as the number of chips. 

- For each time you played a mini-game and returned to the game selection menu, the number of chips will be amended accordingly.

- The detailed rule of texas poker (`texa_rule.txt`) could also be shown during gameplay 

### Program codes in multiple files

Our game is separated into multiple files, each deals with its corrsponding functions, and we use `Makefile` to compile all programs and make this game work.

- program files include: `main.cpp`, `roulette.cpp`, `slotmachine.cpp`, `texpoker.cpp`, `func.cpp`

- *As the function `clear()` is used multiple times, it is put into an individual file called `func.cpp`*

## Quick Start
- **Note:** A large terminal size is recommended in order to display ASCII arts properly. 
- Please enter the following on the terminal to start the game:

        make casino
        ./casino

- After successful compilation and execution, you should see a game menu, and you can enjoy three mini-games within our casino after entering your own username!

- Use `make clean` to remove all generated files.

`please have fun:)`

## [Demonstration Video](https://youtu.be/u7m6LBkFRbQ)

**(END OF README)**
