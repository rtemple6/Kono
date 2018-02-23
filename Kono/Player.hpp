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
#include "Direction.cpp"
using namespace std;


class Player {
    bool isTurn = false;
    string color;
public:
    Player();
    void setTurn(bool turn);
    bool getIsTurn();
    
    void setColor(string color);
    string getColor();
    
    virtual tuple<int, int, Direction> play();    
};

#endif /* Player_hpp */
