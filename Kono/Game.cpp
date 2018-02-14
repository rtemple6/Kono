//
//  Game.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Game.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <ctype.h>

using namespace std;

Game::Game() {
    this->board = Board();
}

void Game::setUpBoard(Human *user, Computer* computer) {
    
    int size;
    cout << "Select board size (5, 7, or 9): ";
    cin >> size;
    cout << endl;
    this->board.set(user, computer);
    this->board.createBoard(size);
    this->board.drawBoard();
}

void Game::rollDice(Human *user, Computer *computer) {
    int player1Score = 11;//rand() % 10 + 2;
    int player2Score = 9;//rand() % 10 + 2;
    
    cout << "* Rolling dice to see who goes first *" << endl;
    cout << "Your Roll: " << player1Score << endl;
    cout << "Computers: " << player2Score << endl;
    
    //If they are same value, recursively call determine order.
    if (player1Score == player2Score) {
        cout << "You tied." << endl;
        rollDice(user, computer);
        return;
    }
    
    //Determine highest score.
    (player1Score > player2Score) ? user->setTurn(true) : computer->setTurn(true);
    
    (user->getIsTurn()) ? cout << "You will go first!" << endl << endl : cout << "Computer will go first." << endl << endl;
    chooseColor(user, computer);
}

void Game::chooseColor(Human *user, Computer *computer) {
    //Print who goes first
    if (user->getIsTurn()) {
        cout << "Choose your color (B or W): ";
        char color, upperColor;
        cin >> color;
        upperColor = toupper(color);
        if (upperColor != 'B') {
            if (upperColor != 'W') {
                cout << "Invalid Input: " << color << endl;
                chooseColor(user, computer);
                return;
            }
        }
        user->setColor(upperColor);
        (upperColor == 'B') ? computer->setColor('W') : computer->setColor('B');
    } else {
        computer->setColor('W');
        user->setColor('B');
    }
    
    cout << "You are " << user->getColor() << "." << endl;
    cout << "Computer is " << computer->getColor() << "." << endl << endl;
    
}

void Game::assignRandomColor() {
    int color = rand() % 2;
    (color == 0) ? cout << "You are B." << endl : cout << "You are W" << endl;
}

