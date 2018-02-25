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
    bool isTurn = false;
    string color;
    int score = 0;
    Board *board;
public:
    Player();
    void setTurn(bool turn);
    bool getIsTurn();
    
    void setBoard(Board *b);
    Board* getBoard();
    
    void setScore(int score);
    int getScore();
    
    void setColor(string color);
    string getColor();
    
    virtual void play();
};

#endif /* Player_hpp */
