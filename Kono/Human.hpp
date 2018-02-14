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
using namespace std;

class Human: public Player {
    
public:
    Human();
    void play();
};

#endif /* Human_hpp */
