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

using namespace std;

Game::Game() {
    this->board = Board();
}

void Game::setUpBoard() {
    int size;
    cout << "Select board size (5, 7, or 9): ";
    cin >> size;
    cout << endl;
    this->board.createBoard(size);
    this->board.drawBoard();
}

void Game::determineOrder() {
    int player1Score = rand() % 10 + 2;
    int player2Score = rand() % 10 + 2;
    
    cout << "* Rolling dice to see who goes first *" << endl;
    cout << "Your Roll: " << player1Score << endl;
    cout << "Computers: " << player2Score << endl;
    
    //If they are same value, recursively call determine order.
    if (player1Score == player2Score) {
        cout << "You tied." << endl;
        determineOrder();
        return;
    }
    
    //Determine highest score.
    int player = (player1Score > player2Score) ? 1 : 2;
    string user = player == 1 ? "You" : "Computer";
    cout << user << " will go first." << endl << endl;
}

void Game::chooseColor() {
    //Determine who first player
    string color;
    cout << "Player 1 you choose color: B or W" << endl;
    cin >> color;
    
    cout << "You are color: " << color << endl;
}

void Game::assignRandomColor() {
    int color = rand() % 2;
    (color == 0) ? cout << "You are B." << endl : cout << "You are W" << endl;
}
