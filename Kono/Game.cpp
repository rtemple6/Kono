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

Game::Game(Human * u, Computer * c) {
    this->board = new Board();
    this->user = u;
    this->computer = c;
}

void Game::setUpBoard() {
    int size;
    cout << "Select board size (5, 7, or 9): ";
    cin >> size;
    cout << endl;
    this->board->set(user, computer);
    this->board->createBoard(size);
    this->board->drawBoard();
}

void Game::rollDice() {
    int player1Score = 11;//rand() % 10 + 2;
    int player2Score = 9;//rand() % 10 + 2;
    
    cout << "* Rolling dice to see who goes first *" << endl;
    cout << "Your Roll: " << player1Score << endl;
    cout << "Computers: " << player2Score << endl;
    
    //If they are same value, recursively call determine order.
    if (player1Score == player2Score) {
        cout << "You tied." << endl;
        rollDice();
        return;
    }
    
    //Determine highest score.
    (player1Score > player2Score) ? user->setTurn(true) : computer->setTurn(true);
    
    (user->getIsTurn()) ? cout << "You will go first!" << endl << endl : cout << "Computer will go first." << endl << endl;
    chooseColor();
}

void Game::chooseColor() {
    //Print who goes first
    stringstream ss;
    if (user->getIsTurn()) {
        cout << "Choose your color (B or W): ";
        char color, upperColor;
        cin >> color;
        upperColor = toupper(color);
        if (upperColor != 'B') {
            if (upperColor != 'W') {
                cout << "Invalid Input: " << color << endl;
                chooseColor();
                return;
            }
        }
        
        //Was using Chars initially, switched to Strings.
        //This converts my char to a string
        ss << upperColor;
        string tmpColor;
        ss >> tmpColor;
        
        user->setColor(tmpColor);
        (upperColor == 'B') ? computer->setColor("W") : computer->setColor("B");
    } else {
        computer->setColor("W");
        user->setColor("W");
    }
    
    cout << "You are " << user->getColor() << "." << endl;
    cout << "Computer is " << computer->getColor() << "." << endl << endl;
}

void Game::assignRandomColor() {
    int color = rand() % 2;
    (color == 0) ? cout << "You are B." << endl : cout << "You are W" << endl;
}

void Game::provideMenu() {
    //
    if (computer->getIsTurn()) {
        cout << "It's the computers turn!" << endl;
        move();
        return;
    }
    
    int choice;
    cout << "Choose an option below" << endl;
    cout << "1. Save Game" << endl;
    cout << "2. Make A Move" << endl;
    cout << "3. Suggest Move" << endl;
    cout << "4. Quit Game" << endl << endl;
    cout << "Your choice: ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "Saving game..." << endl;
            break;
        case 2:
            move();
            break;
        case 3:
            cout << "Suggesting move..." << endl;
            break;
        case 4:
            cout << "Quitting game..." << endl;
            break;
        default:
            cout << "Invalid choice: " << choice << endl << endl;
            provideMenu();
            break;
    }
}

void Game:: move() {
    //Check to see who turn it is
    int row, column;
    Direction direction;
    if (user->getIsTurn()) {
        //Gets a tuple with the 3 values. They can be individually accessed.
        tie(row, column, direction) = user->play();
        if (board->movePiece(row, column, direction)) {
            cout << "You successfully moved piece!" << endl << endl;
            board->drawBoard();
            swapTurns();
            move();
        } else {
            move();
        }
    } else {
        tie(row, column, direction) = computer->play();
        if (board->movePiece(row, column, direction)) {
            cout << "Computer successfully moved piece!" << endl << endl;
            board->drawBoard();
            swapTurns();
            provideMenu();
        } else {
            cout << "Error moving computer piece: " << endl;
        }
    }
}

void Game:: swapTurns() {
    user->setTurn(!user->getIsTurn());
    computer->setTurn(!computer->getIsTurn());
}


