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
#include "Human.hpp"
#include "Computer.hpp"


class Board {
    int boardSize;
    //2 Dimensional array to hold board
    char ** board;
    Human *user;
    Computer *computer;
public:
    Board();
    void createBoard(int size);
    int getBoardSize();
    
    void set(Human *user, Computer *computer);
    
    char pieceAt(int row, int column);
    
    //Draws the current board
    void drawBoard();
        
    bool movePiece(int row, int column, Direction d);
};

#endif /* Board_hpp */
