//
//  Player.hpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <tuple>
#include <sstream>
#include "Board.hpp"

using namespace std;


class Player {
protected:
    string color;
    Player(string color);
private:
    bool isTurn = false;
    int score = 0;
    Board *board;
public:
    
    void setTurn(bool turn);
    bool getIsTurn();
    
    void setBoard(Board *b);
    Board* getBoard();
    
    void setScore(int score);
    int getScore();
    
    void setColor(string color);
    string getColor();
    
    virtual tuple<int, int, Direction, MoveType> play();
    bool isValidMove(int row, int column, Direction d, bool capture);
    
    tuple<int, int, Direction, bool> areAnySuperPieceMoves();
    tuple<int, int, Direction, bool> areAnyBlockMoves();
    
    tuple<int, int, Direction, bool> doesHumanOccupyNeighborSpots(int row, int column, Direction d);
};

#endif /* Player_hpp */
