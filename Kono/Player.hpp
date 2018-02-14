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

class Player {
    bool isTurn = false;
    char color;
public:
    Player();
    void setTurn(bool turn);
    bool getIsTurn();
    
    void setColor(char color);
    char getColor();
    
    virtual void play();
};

#endif /* Player_hpp */
