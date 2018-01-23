//
//  Board.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Board.hpp"
#include <iostream>
using namespace std;

Board::Board() {
    this->boardSize = 5;
}

Board::Board(int boardSize) {
    this->boardSize = boardSize;
}

void Board::setBoardSize(int boardSize) {
    this->boardSize = boardSize;
}

void Board::drawBoard() {
    cout << "Drawing board with size: " << boardSize << endl;
}
