//
//  Computer.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Computer.hpp"

Computer:: Computer(string color) : Player(color) {
    setColor(color);
}

tuple<int, int, Direction,MoveType> Computer::play() {
    //Does the computer have any super pieces?
    int row, column;
    Direction d;
    MoveType m;
    tie(row, column, d, m) = Player::play();
    string directionWord;
//    row++;
//    column++;
    switch (d) {
        case NE:
            directionWord = "northeast";
            break;
        case NW:
            directionWord = "northwest";
            break;
        case SE:
            directionWord = "southeast";
            break;
        case SW:
            directionWord = "southwest";
            break;
        default:
            break;
    }
    switch (m) {
        case capture:
            cout << "Computer is capturing your piece. " << endl;
            break;
        case block:
            cout << "Computer is blocking your piece. " << endl;
            break;
        case MoveType::advance:
            cout << endl << "Computer moved piece at (" << row + 1 << ", " << column + 1 << ") " << directionWord << " to advance towards your home field." << endl  << endl;
            break;
        default:
            break;
    }
    
    return make_tuple(row,column,d, m);
}





