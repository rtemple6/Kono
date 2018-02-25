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
#include <iostream>
#include "Direction.cpp"
#include <tuple>
using namespace std;

class Board {
    int boardSize;
    //2 Dimensional array to hold board
    string ** board;
    bool isPieceAtLocation(int row, int column);
    
public:
    Board();
    void createBoard(int size);
    void setBoard(int size, string **data);
    string** getBoard();
    int getBoardSize();
    
    string pieceAt(int row, int column);
    
    //Draws the current board
    void drawBoard();
        
    bool movePiece(int row, int column, Direction d);
    tuple<bool, Direction> validateDirection(string direction);
};

#endif /* Board_hpp */
