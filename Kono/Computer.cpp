//
//  Computer.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Computer.hpp"

Computer:: Computer() {
    
}

void Computer::play() {
    //Get piece to move
    //If white get lowest row, lowest column piece that can move down.
    bool gotPiece = false;
    int row = 0, column = 0;
    
    int boardSize = getBoard()->getBoardSize();
    
    while (!gotPiece) {
        string piece = getBoard()->pieceAt(row, column);
        if (piece == getColor()) {
            //Move piece down NE
            getBoard()->movePiece(row, column, NE);
        } else {
            column++;
            if (column == 5) {
                column = 0;
                row++;
            }
        }
    }
    
}
