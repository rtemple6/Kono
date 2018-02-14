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

class Game {
    Board board;
    
public:
    Game();
    void setUpBoard();
    void determineOrder();
    void chooseColor();
    void assignRandomColor();
};

#endif /* Game_hpp */
