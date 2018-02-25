//
//  Round.hpp
//  Kono
//
//  Created by Ryan Temple on 2/24/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef Round_hpp
#define Round_hpp

#include <stdio.h>
#include "Board.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include "FileWriter.hpp"
#include <sstream>

class Round {
    Board *board;
    Human *user;
    Computer *computer;
    int round = 1;
public:
    Round(Human * u, Computer * c);
    
    void setRound(int round);
    int getRound();
    
    void nextRound(string winner);
    
    void setUpBoard();
    void loadBoard(int size, string **data);
    
    void rollDice();
    void chooseColor();

    void provideMenu();
    void computerMenu();
    
    void move();
    void swapTurns();
    
    void endRound(bool didQuit, string quitter);
};

#endif /* Game_hpp */

