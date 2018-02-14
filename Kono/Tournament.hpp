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
using namespace std;

class Tournament {
    Human *user;
    Computer *computer;
public:
    Tournament();
    void startGame();
    void provideMenu();
    void computerMove();
};

#endif /* Tournament_hpp */
