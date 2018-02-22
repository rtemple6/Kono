//
//  Computer.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Computer.hpp"

Computer:: Computer() {
    
}

tuple<int, int, Direction> Computer::play() {
    return make_tuple(1, 1, NE);
}
