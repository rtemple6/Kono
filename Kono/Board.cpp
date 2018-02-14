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
                this->board[i][j] = 'W';
            } else if (i == 1) {
                //Second row
                if (j == 0) {
                    //First piece
                    this->board[i][j] = 'W';
                } else if (j == tmp) {
                    //Last piece
                    this->board[i][j] = 'W';
                } else {
                    //Filler piece
                    this->board[i][j] = 'O';
                }
            } else {
                this->board[i][j] = 'R';
            }
        }
    }
}

int Board::getBoardSize() {
    return this->boardSize;
}

char Board::pieceAt(int row, int column) {
    char piece = board[row][column];
    
    return this->board[row][column];
}

void Board::drawBoard() {
    BoardView view;
    view.setBoard(this);
    view.draw();
}
