// nim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <iomanip>

using namespace std;

void clear() {
    cout << "\x1b[2J\x1b[H";
}

int randint(int s, int e = 0) {
    if (s < e) {
        return s + rand() % (e - s) + 1;
    }
    else if (e == 0) {
        return rand() % s + 1;
    }
    else {
        return e + rand() % s + 1;
    }
}

void game(bool comp) {
    int stones = randint(20, 30);

    bool player_one_turn = true;
    bool playing_computer = comp;
    int take;
    while (stones > 0) {
        if (player_one_turn) {
            cout << "Player one, it's your turn! \n";
        }
        else {
            if (!playing_computer) {
                cout << "Player two, it's your turn! \n";
            }
        }
        if (!playing_computer || (playing_computer && player_one_turn)) {
            cout << "There are " << stones << " stones remaining. \nHow many stones would you like to take? (1/2/3)\n";
            cin >> take;
            while (take < 0 || take > 3) {
                clear();
                cout << "I'm sorry, but you can't take " << take << " stones!\n";
                if (player_one_turn) {
                    cout << "Player one, it's still your turn! \n";
                }
                else {
                    cout << "Player two, it's still your turn! \n";
                }
                cout << "There are " << stones << " stones remaining. \nHow many stones would you like to take? (1/2/3)\n";
                cin >> take;
            }
        }
        else {
            take = stones % 4;
        }
        stones = stones - take;
        clear();
        player_one_turn = not(player_one_turn);
        cout << take << " stones were just taken.\n";
    }
    if (not(player_one_turn)) {
        cout << "Player one has taken the last stone and won!\n";
    }
    else {
        if (!playing_computer) {
            cout << "Player two has taken the last stone and won!\n";
        }
        else {
            cout << "The computer won! You suck!";
        }
    }
}

int mod(int n, int M) {
    return ((n % M) + M) % M;
}

void printSquare(vector<vector<int>> square, int N) {
    for (int p = 0; p < N; p++) {
        for (int k = 0; k < N; k++) {
            cout << setfill('0') << setw(log10(N * N) + 1) << square[p][k] << " ";
        }
        cout << "\n";
    }
}

vector<vector<int>> magicSquares(int N) {
    int n = 1;

    vector<vector<int>> magic_square;
    for (int i = 0; i < N; i++) {
        vector<int> v1;

        for (int j = 0; j < N; j++) {
            v1.push_back(0);
        }
        magic_square.push_back(v1);
    }

    int i = 0;
    int j = floor(N / 2);

    int newI;
    int newJ;

    while (n <= pow(N, 2)) {
        magic_square[i][j] = n;
        n += 1;

        newI = mod(i - 1, N);
        newJ = mod(j + 1, N);

        if (magic_square[newI][newJ]) {
            i += 1;
        }
        else {
            i = newI;
            j = newJ;
        }
    }
    return magic_square;
}

void nim(bool comp) {
    clear();
    game(comp);
}

void getSquare() {
    int size;
    cout << "What size would you like your square? (odd numbers only, please!)\n";
    cin >> size;
    if (size % 2 == 0) { size++; }
    printSquare(magicSquares(size), size);
}

int main()
{
    srand(time(nullptr));
    int choice;
    char comp;
    bool a_comp = false;
    cout << "Press ENTER to continue.\n";
    cin.get();
    clear();
    cout << "Welcome to MiniCode Madness, where the excellent Chaim will show off a few fun minigames!\n";
    cout << "To play a game, enter the corresponding number:\n";
    cout << "    1. Nim\n    2. Magic Squares\n";
    cin >> choice;
    while (choice < 0 || choice > 2) {
        clear();
        cout << "That's not an option!\n";
        cout << "To play a game, enter the corresponding number:\n";
        cout << "    1. Nim\n    2. Magic Squares";
        cin >> choice;
    }
    switch (choice) {
    case 1:
        clear();
        cout << "Welcome to Nim! \nThe goal of the game is to take the final stone. \nDuring play, two players go head to head removing either 1, 2, or 3 stones. \nThe computer handles everything else! \nSo get ready to have some fun playing NIM!\n\n\nPress ENTER to begin the game, or type in [C] (without the brackets) and hit ENTER to play the computer!\n";
        cin >> comp;
        if (comp == 'C') { a_comp = true; }
        nim(a_comp);
        break;
    case 2:
        getSquare();
        break;
    }
}