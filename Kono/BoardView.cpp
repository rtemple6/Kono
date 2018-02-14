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
    int size = this->board->getBoardSize();
    int tmp = size - 1;
    
    cout << "N" << endl;
    for(int i = 0; i < size; i++) {
        cout << i << "  ";
        for(int j = 0; j < size; j++) {
            cout << this->board->pieceAt(i, j);
            
            //This prints the in-between fields minus the last one
            (j == tmp) ? cout << "" : cout << " - ";
        }
        //New line
        cout << endl;
        
        //Print in-between rows minus the last one
        (i == tmp) ? cout << endl : cout << "   |   |   |   |   |" << endl;
    }
    
    //Draw out bottom bar
    cout << "W  ";
    for (int i = 1; i <= size; i++) {
        cout << i;
        (i - 1 == tmp) ? cout << "" : cout << "   ";
    }
    cout << "  E" << endl;
}
