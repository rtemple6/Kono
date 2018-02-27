//
//  Computer.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Computer.hpp"

/* *********************************************************************
 Function Name: Computer:color : Player(color)
 Purpose: Creates a human setting the protected player color to the color
 Parameters:color, the color to set
 Return Value: new Human
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
Computer:: Computer(string color) : Player(color) {
    setColor(color);
}

/* *********************************************************************
 Function Name: play
 Purpose: Called when computer is going to move piece.  
 Parameters:none
 Return Value:
 a tuple consisting of
 int, the row
 int, the column
 Diection, the direction
 MoveType, capture/block/advance
 Local Variables:none
 Algorithm:none
 Assistance Received:
 https://www.daniweb.com/programming/software-development/tutorials/71858/user-input-strings-and-numbers-c
 ********************************************************************* */
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
            cout << endl << "Computer moved piece at (" << row + 1 << ", " << column + 1 << ") " << directionWord << " to block your piece." << endl  << endl;
            break;
        case MoveType::advance:
            cout << endl << "Computer moved piece at (" << row + 1 << ", " << column + 1 << ") " << directionWord << " to advance towards your home field." << endl  << endl;
            break;
        default:
            break;
    }
    
    return make_tuple(row,column,d, m);
}





