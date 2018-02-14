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

class Game {
    Board board;
    
public:
    Game();
    void setUpBoard(Human *user, Computer *computer);
    void rollDice(Human *user, Computer *computer);
    void chooseColor(Human *user, Computer *computer);
    void assignRandomColor();
    void move();
};

#endif /* Game_hpp */
