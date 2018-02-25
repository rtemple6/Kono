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
    this->board = new string *[size];
    for(int i = 0; i < size; i++) {
        this->board[i] = new string[size];
    }
    
    //Fill the board
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if (i == 0) {
                //First row
                this->board[i][j] = "W";
            } else if (i == 1) {
                //Second row
                if (j == 0) {
                    //First piece
                    this->board[i][j] = "W";
                } else if (j == tmp) {
                    //Last piece
                    this->board[i][j] = "W";
                } else {
                    //Filler piece
                    this->board[i][j] = "O";
                }
            } else if (i == tmp - 1) {
                //Second to last row
                if (j == 0) {
                    //First piece
                    this->board[i][j] = "B";
                } else if (j == tmp) {
                    //Last piece
                    this->board[i][j] = "B";
                } else {
                    //Filler piece
                    this->board[i][j] = "O";
                }
            } else if (i == tmp) {
                //Last row
                this->board[i][j] = "B";
            } else {
                //Filler spaces
                this->board[i][j] = "O";
            }
        }
    }
}

void Board::setBoard(int size, string **data) {
    boardSize = size;
    board = data;
}

string ** Board::getBoard() {
    return board;
}

int Board::getBoardSize() {
    return this->boardSize;
}

string Board::pieceAt(int row, int column) {
    string piece = board[row][column];
    if (piece == "O") {
        return "+";
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
    
    //Check to see if it is their piece
    if (user->getIsTurn()) {
        string color = user->getColor();
        string userPiece = pieceAt(row, column);
        if (color != userPiece) {
            cout << endl << "Invalid Move: Must select your piece (" << color << ")." << endl << endl;
            return false;
        }
    } else {
        string color = computer->getColor();
        string computerPiece = pieceAt(row, column);
        if (color != computerPiece) {
            cout << endl << "Silly computer that's not your piece" << endl;
            return false;
        }
    }
    
    bool retVal = false;
    switch (d) {
        case NE:
            if (isValidMove(row - 1, column + 1)) {
                cout << "Moving piece at row: " << row << " column: " << column;
                cout << " to row: " << row - 1 << " column: " << column + 1 << endl;
                board[row][column] = 'O';
                //Set the appropriate piece
                board[row - 1][column + 1] = (user->getIsTurn()) ? user->getColor() : computer->getColor();
                retVal = true;
            }
            break;
        case NW:
            if (isValidMove(row - 1, column - 1)) {
                cout << "Moving piece at row: " << row << " column: " << column;
                cout << " to row: " << row - 1 << " column: " << column - 1 << endl;
                board[row][column] = 'O';
                //Set the appropriate piece
                board[row - 1][column - 1] = (user->getIsTurn()) ? user->getColor() : computer->getColor();
                retVal = true;
            }
            break;
        case SE:
            if (isValidMove(row + 1, column + 1)) {
                cout << "Moving piece at row: " << row << " column: " << column;
                cout << " to row: " << row + 1 << " column: " << column + 1 << endl;
                board[row][column] = 'O';
                //Set the appropriate piece
                board[row + 1][column + 1] = (user->getIsTurn()) ? user->getColor() : computer->getColor();
                retVal = true;
            }
            break;
        case SW:
            if (isValidMove(row + 1, column - 1)) {
                cout << "Moving piece at row: " << row << " column: " << column;
                cout << " to row: " << row + 1 << " column: " << column - 1 << endl;
                board[row][column] = 'O';
                //Set the appropriate piece
                board[row + 1][column - 1] = (user->getIsTurn()) ? user->getColor() : computer->getColor();
                retVal = true;
            }
            break;
        default:
            break;
    }
    return retVal;
}

bool Board::isValidMove(int row, int column) {
    
    //Check to see if it is out of the bounds.
    if (row >= boardSize || row < 0 || column >= boardSize || column < 0) {
        cout << endl << "Invalid Move: Must stay on the board." << endl;
        return false;
    }
    
    //Check to see if there is a piece there.
    string piece = pieceAt(row, column);
    string userPiece = user->getColor();
    string computerPiece = computer->getColor();
    if (user->getIsTurn()) {
        if (computerPiece == piece) {
            cout << endl << "Computer piece occupies this space." << endl;
            cout << "This is where capture functionality should go" << endl;
            return false;
        } else if (userPiece == piece) {
            cout << endl << "Your piece occupies this space." << endl;
            return false;
        } else {
            cout << "Valid move!" << endl;
            return true;
        }
    } else {
        if (computerPiece == piece) {
            cout << endl << "Computer your piece occupies this spot." << endl;
            return false;
        } else if (userPiece == piece) {
            cout << endl << "User piece occupies this space." << endl;
            cout << "This is where the capture functionality should go" << endl;
            return false;
        } else {
            cout << "Valid move!" << endl;
            return true;
        }
    }
    
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
