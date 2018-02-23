//
//  Human.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Human.hpp"


Human:: Human() {
    
}


tuple<int, int, Direction> Human::play() {
    int row, column;
    cout << endl << "Move Piece - Valid Directions (NE/NW/SE/SW)" << endl;
    cout << "      Row: ";
    cin >> row;
    cout << "   Column: ";
    cin >> column;
    
    //Found this line of code here https://www.daniweb.com/programming/software-development/tutorials/71858/user-input-strings-and-numbers-c
    //Allows for the string input after the 2 integer inputs
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    bool isValid = false;
    Direction d;
    while (!isValid) {
        cout << "Direction: ";
        string direction;
        getline (cin, direction);
        
        tie(isValid, d) = validateDirection(direction);
    }
    
    //Subtract 1 to fix array position starting at 0
    return make_tuple(row - 1, column - 1, d);
}


tuple<bool, Direction> Human:: validateDirection(string direction){
    
    if (direction.empty()) {
        return make_tuple(false, NE);
    }
    
    Direction d;
    
    //Make it uppercase
    transform(direction.begin(), direction.end(), direction.begin(), ::toupper);
    
    if (direction == "NE") {
        d = NE;
    } else if (direction == "NW") {
        d = NW;
    } else if (direction == "SE") {
        d = SE;
    } else if (direction == "SW") {
        d = SW;
    } else {
        return make_tuple(false, NE);
    }
    
    return make_tuple(true, d);
}
