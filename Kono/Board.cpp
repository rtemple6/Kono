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

int Board::getBoardSize() {
    return this->boardSize;
}

void Board::createBoard(int size) {
    this->boardSize = size;
    
    //This creates a 1-Dimensional Array of pointers
    //Each pointer points to an array of values
    this->board = new char *[size];
    for(int i = 0; i < size; i++) {
        this->board[i] = new char[size];
    }
    
    //Fill the board
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            this->board[i][j] = 'O';
        }
    }
}

void Board::drawBoard() {
    BoardView view;
    view.setBoard(this);
    view.draw();
}
