# hku_casino

An ENGG1340/COMP2113 (2022/2023 Semester 2) project

## Contributors

samchong0302 -> Chong Chak Yu 3035691602 (Game Menu and Bank system)

k-kwong -> Kwong Tsz Kong 3035924126 (texa_rule.txt,test_compare.cpp,main2.cpp,but finally not adopted.)

LTree0703 -> Pang Tin Hei 3036100179 (texpoker.cpp and main.cpp)

jaimielee14 ->

dawon92 ->

## About Our Game
Our game is a collection of three mini casino games, including slot machine, roulette and texas poker. In this game, users are able to create a local profile that is initialized with 100 chips to enter our casino. Yet, if the player has lost all the chips, he/she will be considered game over and the user profile will be deleted.

1. Roulette

- This is a simple number guessing game, in which players can guess a number ranging from 1 to 10. *The number of bet is decided by the players.* If they guessed correctly, they will be awarded three times of thier betting amount.

2. Slot machine

- This is a simple slot machine, containing 7 symbols. *The number of bet is 1 per each round.* At each round, the slot machine will randomly generate 3 symbols. If two of them are the same, 10 chips will be awarded and 100 chips will be awarded if three of them are the same (i.e., jackpot).

3. Texas Poker (Texas Hold'em)

- This is a simple Texas poker game with simplified rules. 
- For each game round, the players have to bet 3 times (known as flop, turn and river), and the default amount of bet is 1 chip (*call* option, yet the amount could be increased by doing *raise* option). Also, the players could choose to skip one bet (*check* option), bet 0 amounts if they would like to give up on that round (*fold* option), or bet all their chips if they are feeling good (*all-in* option).
- The players have to obtain a specific pattern of 5 poker cards from a combination of 7 poker cards (hole cards + community cards) with the pattern rank as high as possible in order to win the game round. 
- **For details of the game rule, please refer to [texa_rule.txt](https://github.com/LTree0703/hku_casino/blob/main/texa_rule.txt)**

## Game Features
1. Generation of random game sets or events


2. Data structures for storing game status

3. Dynamic memory management

4. File input/output 

5. Program codes in multiple files

## Quick Start
- Note: our game will create a local .txt file to store the username well as the number of chips, please do not amend unless necessary.
- Please enter the following on the terminal to start the game (a larger terminal size is preferred)

        make casino
        ./casino

- After successful compilation and execution, you should see a game menu. After entering your own username, you can enjoy three mini-games within our casino!

## [Demonstration Video](https://youtu.be/u7m6LBkFRbQ)

<br>

### <center> -END OF README- <center>

---
