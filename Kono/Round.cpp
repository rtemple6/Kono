//
//  Round.cpp
//  Kono
//
//  Created by Ryan Temple on 2/24/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Round.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <ctype.h>

using namespace std;

Round::Round(Human * u, Computer * c) {
    this->board = new Board();
    this->user = u;
    this->computer = c;
}

void Round::setRound(int round) {
    this->round = round;
}

int Round::getRound() {
    return this->round;
}

void Round::setUpBoard() {
    int size;
    cout << "Select board size (5, 7, or 9): ";
    cin >> size;
    cout << endl;
    this->board->createBoard(size);
    this->user->setBoard(board);
    this->computer->setBoard(board);
    this->board->drawBoard();
}

void Round:: loadBoard(int size, string **data) {
    this->board->setBoard(size, data);
    this->user->setBoard(board);
    this->computer->setBoard(board);
    this->board->drawBoard();
}

void Round::rollDice() {
    int player1Score = 11;//rand() % 10 + 2;
    int player2Score = 9;//rand() % 10 + 2;
    
    cout << endl << "* Rolling dice to see who goes first *" << endl;
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

void Round::chooseColor() {
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

void Round::assignRandomColor() {
    int color = rand() % 2;
    (color == 0) ? cout << "You are B." << endl : cout << "You are W" << endl;
}

void Round::provideMenu() {
    //
    if (computer->getIsTurn()) {
        computerMenu();
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
    
    FileWriter write;
    string nextPlayer;
    switch (choice) {
        case 1:
            (user->getIsTurn()) ? nextPlayer = "Human" : nextPlayer = "Computer";
            write.saveGame(getRound(), user->getScore(), user->getColor(), computer->getScore(), computer->getColor(), board, nextPlayer);
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

void Round:: computerMenu() {
    int choice;
    cout << "Choose an option below" << endl;
    cout << "1. Save Game" << endl;
    cout << "2. Computer Move" << endl;
    cout << "3. Quit Game" << endl << endl;
    cout << "Your choice: ";
    cin >> choice;
    
    FileWriter write;
    string nextPlayer;
    switch (choice) {
        case 1:
            (user->getIsTurn()) ? nextPlayer = "Human" : nextPlayer = "Computer";
            write.saveGame(getRound(), user->getScore(), user->getColor(), computer->getScore(), computer->getColor(), board, nextPlayer);
            break;
        case 2:
            move();
            break;
        case 3:
            cout << "Quitting game..." << endl;
            break;
        default:
            cout << "Invalid choice: " << choice << endl << endl;
            computerMenu();
            break;
    }
}

void Round:: move() {
    //Check to see who turn it is
    int row, column;
    Direction direction;
    if (user->getIsTurn()) {
        user->play();
        swapTurns();
        provideMenu();
        //Gets a tuple with the 3 values. They can be individually accessed.
//        tie(row, column, direction) = user->play();
//        if (board->movePiece(row, column, direction)) {
//            cout << "You successfully moved piece!" << endl << endl;
//            board->drawBoard();
//            swapTurns();
//            provideMenu();
//        } else {
//            provideMenu();
//        }
    } else {
        computer->play();
//        tie(row, column, direction) = computer->play();
//        if (board->movePiece(row, column, direction)) {
//            cout << "Computer successfully moved piece!" << endl << endl;
//            board->drawBoard();
//            swapTurns();
//            provideMenu();
//        } else {
//            cout << "Error moving computer piece: " << endl;
//        }
    }
}

void Round:: swapTurns() {
    user->setTurn(!user->getIsTurn());
    computer->setTurn(!computer->getIsTurn());
}



