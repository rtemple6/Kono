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

BoardView::BoardView() {
    
}

void BoardView::setBoard(Board *b) {
    this->board = b;
}

/* *********************************************************************
 Function Name: draw
 Purpose: To draw the board using Board data
 Parameters:none
 Return Value:none
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void BoardView::draw() {
    //This loops on the rows.
    int size = this->board->getBoardSize();
    int tmp = size - 1;
    
    cout << "N" << endl;
    for(int i = 1; i <= size; i++) {
        cout << i << "  ";
        for(int j = 0; j < size; j++) {
            cout << this->board->pieceAt(i - 1, j);
            
            //This prints the in-between fields minus the last one
            (j == tmp) ? cout << "" : cout << " - ";
        }
        //New line
        cout << endl;
        
        if (i - 1 == tmp) {
            cout << "S" << endl;
        }
        
        //Print in-between rows minus the last one
        for(int r = 0; r < size; r++) {
            (i - 1 == tmp) ? cout << "" : cout << "   |";
        }
        
        //Formatting to keep out bottom
        (i - 1 == tmp) ? cout : cout << endl;
    }
    
    //Draw out bottom bar
    cout << "W  ";
    for (int i = 1; i <= size; i++) {
        cout << i;
        (i - 1 == tmp) ? cout << "" : cout << "   ";
    }
    cout << "  E" << endl << endl;
}

