//
//  Board.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Board.hpp"
#include "BoardView.hpp"
#include <iostream>
using namespace std;

Board::Board() {
}

void Board::createBoard(int size) {
    this->boardSize = size;
    
    //Used to determine end piece.
    int tmp = size -1;
    
    //This creates a 1-Dimensional Array of pointers
    //Each pointer points to an array of values
    this->board = new char *[size];
    for(int i = 0; i < size; i++) {
        this->board[i] = new char[size];
    }
    
    //Fill the board
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if (i == 0) {
                //First row
                this->board[i][j] = this->computer->getColor();
            } else if (i == 1) {
                //Second row
                if (j == 0) {
                    //First piece
                    this->board[i][j] = this->computer->getColor();
                } else if (j == tmp) {
                    //Last piece
                    this->board[i][j] = this->computer->getColor();
                } else {
                    //Filler piece
                    this->board[i][j] = 'O';
                }
            } else if (i == tmp - 1) {
                //Second to last row
                if (j == 0) {
                    //First piece
                    this->board[i][j] = this->user->getColor();
                } else if (j == tmp) {
                    //Last piece
                    this->board[i][j] = this->user->getColor();
                } else {
                    //Filler piece
                    this->board[i][j] = 'O';
                }
            } else if (i == tmp) {
                //Last row
                this->board[i][j] = this->user->getColor();
            } else {
                //Filler spaces
                this->board[i][j] = 'O';
            }
        }
    }
}

int Board::getBoardSize() {
    return this->boardSize;
}

char Board::pieceAt(int row, int column) {
    char piece = board[row][column];
    if (piece == 'O') {
        return '+';
    }
    return piece;
}

void Board::drawBoard() {
    BoardView view;
    view.setBoard(this);
    view.draw();
}

void Board::set(Human *user, Computer *computer) {
    this->user = user;
    this->computer = computer;
}

bool Board:: movePiece(int row, int column, Direction d) {
    //N goes up, so subtract from row
    //S goes down, so add to row
    //E goes left, so subtract from column
    //W goes right, so add from to column
    char piece = pieceAt(row, column);
    cout << "The user selected piece: " << piece << endl;
    bool retVal = false;
    switch (d) {
        case NE:
            if (isValidMove(row - 1, column + 1)) {
                cout << "Valid move!" << endl;
                retVal = true;
            }
            break;
        case NW:
            if (isValidMove(row - 1, column - 1)) {
                cout << "Valid move!" << endl;
                retVal = true;
            }
            break;
        case SE:
            if (isValidMove(row + 1, column + 1)) {
                cout << "Valid move!" << endl;
                retVal = true;
            }
            break;
        case SW:
            if (isValidMove(row + 1, column - 1)) {
                cout << "Valid move!" << endl;
                retVal = true;
            }
            break;
        default:
            break;
    }
    return retVal;
}

bool Board::isValidMove(int row, int column) {
    
    //Check to see if it is their piece
//    if (user->getIsTurn()) {
//        char color = user->getColor();
//        char userPiece = pieceAt(row, column);
//        if (color != userPiece) {
//            cout << "Invalid Move: Must select your piece (" << color << ")." << endl;
//            return false;
//        }
//    }
    
    //Check to see if it is out of the bounds.
    if (row >= boardSize || row < 0 || column >= boardSize || column < 0) {
        cout << endl << "Invalid Move: Must stay on the board." << endl;
        return false;
    }
    
    //Check to see if there is a piece there.
    char piece = pieceAt(row, column);
    cout << "Piece at " << row << ", " << column << " is " << piece << endl;
    return false;
}

bool Board::isPieceAtLocation(int row, int column) {
    if (row > boardSize || row < 0 || column > boardSize || column < 0) {
        cout << endl << "Invalid Move: Must stay on the board!" << endl;
        return false;
    }
    //Check to see if there is a piece there.
    //Check to see if it is out of the bounds.
    return false;
}
