//
//  Game.hpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Board.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include <sstream>

class Game {
    Board *board;
    Human *user;
    Computer *computer;
public:
    Game(Human * u, Computer * c);
    void setUpBoard();
    void rollDice();
    void chooseColor();
    void assignRandomColor();
    void provideMenu();
    void move();
    void swapTurns();
};

#endif /* Game_hpp */
