//
//  Board.hpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>


class Board {
    int boardSize;
    //2 Dimensional array to hold board
    char ** board;
public:
    Board();
    
    void createBoard(int size);
    int getBoardSize();
    
    char pieceAt(int row, int column);
    
    //Draws the current board
    void drawBoard();
};

#endif /* Board_hpp */
