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
#include "BoardView.hpp"

class Board {
    BoardView * board;
    int boardSize;
public:
    Board();
    Board(int boardSize);

    void setBoardSize(int boardSize);
    
    //Getter and setters
    void setBoard(BoardView board);
    BoardView getBoardView();
    
    //Draws the current board
    void drawBoard();
    
    //Moves
    bool isValidMove();
};

#endif /* Board_hpp */
