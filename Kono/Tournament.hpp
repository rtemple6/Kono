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
#include "Round.hpp"
#include <tuple>
#include "FileReader.hpp"
using namespace std;

class Tournament {
    Human *user;
    Computer *computer;
    Round * game;
    FileReader f;
public:
    Tournament();
    void startGame();
    void resumeGame(string filename);
};

#endif /* Tournament_hpp */
