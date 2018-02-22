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
    //Helper method
    tuple<bool, Direction> validateDirection(string direction);
public:
    Human();
    tuple<int, int, Direction> play();
};

#endif /* Human_hpp */
