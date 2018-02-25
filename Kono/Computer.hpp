//
//  Computer.hpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef Computer_hpp
#define Computer_hpp

#include <stdio.h>
#include "Player.hpp"
using namespace std;

class Computer: public Player {
public:
    Computer();
    void play();
};

#endif /* Computer_hpp */
