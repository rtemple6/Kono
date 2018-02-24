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
    string ** board;
    Human *user;
    Computer *computer;
    bool isValidMove(int row, int column);
    bool isPieceAtLocation(int row, int column);
    
public:
    Board();
    void createBoard(int size);
    void setBoard(int size, string **data);
    string** getBoard();
    int getBoardSize();
    
    void set(Human *user, Computer *computer);
    
    string pieceAt(int row, int column);
    
    //Draws the current board
    void drawBoard();
        
    bool movePiece(int row, int column, Direction d);
};

#endif /* Board_hpp */
