//
//  Human.hpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef Human_hpp
#define Human_hpp

#include <stdio.h>
#include <iostream>
#include "Player.hpp"
#include <locale>
using namespace std;


class Human: public Player {
public:
    Human();
    void play();
    bool isValidMove(int row, int column, Direction d);
};

#endif /* Human_hpp */
