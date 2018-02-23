//
//  Tournament.hpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef Tournament_hpp
#define Tournament_hpp

#include "Human.hpp"
#include "Computer.hpp"
#include <stdio.h>
#include "Game.hpp"
#include <tuple>
using namespace std;

class Tournament {
    Human *user;
    Computer *computer;
    Game * game;
    int roundNumber = 0;
public:
    Tournament();
    void startGame();
    void resumeGame();
    void setRound(int round);
};

#endif /* Tournament_hpp */
