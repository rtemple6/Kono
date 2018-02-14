//
//  BoardView.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "BoardView.hpp"
#include <iostream>
using namespace std;

//N
//1  W - W - W - W - W
//   |   |   |   |   |
//2  W - + - + - + - W
//   |   |   |   |   |
//3  + - + - + - + - +
//   |   |   |   |   |
//4  B - + - + - + - B
//   |   |   |   |   |
//5  B - B - B - B - B
//S
//W  1   2   3   4   5  E

BoardView::BoardView() {
    
}

void BoardView::setBoard(Board *b) {
    this->board = b;
}

void BoardView::draw() {
    
    //This loops on the rows.
    for(int i = 0; i < this->board->getBoardSize(); i++) {
        //This loops through columns
        for(int j = 0; j < this->board->getBoardSize(); j++) {
            cout << "O" << "  ";
        }
        //New line
        cout << endl;
    }
}
