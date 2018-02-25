//
//  Board.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Board.hpp"
#include "BoardView.hpp"

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

bool Board:: movePiece(int row, int column, Direction d) {
    //N goes up, so subtract from row
    //S goes down, so add to row
    //E goes left, so subtract from column
    //W goes right, so add from to column

    bool retVal = false;
    switch (d) {
        case NE:
            cout << "Moving piece at row: " << row << " column: " << column;
            cout << " to row: " << row - 1 << " column: " << column + 1 << endl;
            board[row - 1][column + 1] = pieceAt(row, column);
            board[row][column] = 'O';
            retVal = true;
            break;
        case NW:
            cout << "Moving piece at row: " << row << " column: " << column;
            cout << " to row: " << row - 1 << " column: " << column - 1 << endl;
            //Set the appropriate piece
            board[row - 1][column - 1] = pieceAt(row, column);
            board[row][column] = 'O';
            retVal = true;
            break;
        case SE:
            cout << "Moving piece at row: " << row << " column: " << column;
            cout << " to row: " << row + 1 << " column: " << column + 1 << endl;
            //Set the appropriate piece
            board[row + 1][column + 1] = pieceAt(row, column);
            board[row][column] = 'O';
            retVal = true;
            break;
        case SW:
            cout << "Moving piece at row: " << row << " column: " << column;
            cout << " to row: " << row + 1 << " column: " << column - 1 << endl;
            //Set the appropriate piece
            board[row + 1][column - 1] = pieceAt(row, column);
            board[row][column] = 'O';
            retVal = true;
            break;
        default:
            break;
    }
    return retVal;
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

tuple<bool, Direction> Board:: validateDirection(string direction){
    
    if (direction.empty()) {
        return make_tuple(false, NE);
    }
    
    Direction d;
    
    //Make it uppercase
    transform(direction.begin(), direction.end(), direction.begin(), ::toupper);
    
    if (direction == "NE") {
        d = NE;
    } else if (direction == "NW") {
        d = NW;
    } else if (direction == "SE") {
        d = SE;
    } else if (direction == "SW") {
        d = SW;
    } else {
        return make_tuple(false, NE);
    }
    
    return make_tuple(true, d);
}
