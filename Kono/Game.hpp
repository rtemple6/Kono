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
#include "FileWriter.hpp"
#include <sstream>

class Game {
    Board *board;
    Human *user;
    Computer *computer;
    int round = 1;
public:
    Game(Human * u, Computer * c);
    
    void setRound(int round);
    int getRound();
    
    void setUpBoard();
    void loadBoard(int size, string **data);
    
    void rollDice();
    void chooseColor();
    void assignRandomColor();
    
    void provideMenu();
    void computerMenu();
    
    void move();
    void swapTurns();
};

#endif /* Game_hpp */
