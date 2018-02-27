//
//  Human.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Human.hpp"

/* *********************************************************************
 Function Name: Human:color : Player(color)
 Purpose: Creates a human setting the protected player color to the color
 Parameters:color, the color to set
 Return Value: new Human
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
Human:: Human(string color): Player(color) {
    setColor(color);
}

/* *********************************************************************
 Function Name: play
 Purpose: Called when player is going to move piece.  Validates input
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
tuple<int, int, Direction, MoveType> Human::play() {
    
    bool loopForValid = false;
    while (!loopForValid) {
        //Input validations
        bool correctPiece = false;
        bool validInputs = false;
        int row, column;
        while (!correctPiece) {
            cout << endl << "Move Piece" << endl;
            
            while (!validInputs) {
                cout << "   Row: ";
                cin >> row;
                while(cin.fail()) {
                    cout << "   Row: ";
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> row;
                }
                if (row > 0 && row <= getBoard()->getBoardSize()) {
                    while (!validInputs) {
                        cout << "Column: ";
                        cin >> column;
                        while(cin.fail()) {
                            cout << "Column: ";
                            cin.clear();
                            cin.ignore(256,'\n');
                            cin >> column;
                        }
                        if (column > 0 && column <= getBoard()->getBoardSize()) {
                            //Normalize values
                            row--;
                            column--;
                            
                            validInputs = true;
                        }
                    }
                }
            }
            
            //Get the color
            string color = getColor();
            string userPiece = getBoard()->pieceAt(row, column);
            string piece = userPiece.substr(0, 1);
            
            //Recursive validate
            if (color != piece) {
                validInputs = false;
                cout << endl << "Invalid Move: Must select your piece (" << color << ")." << endl;
            } else {
                correctPiece = true;
            }
        }
        
        //Necessary for input string after chars
        //Used assistance on this
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        //Get the direciton
        bool isValid = false;
        Direction d;
        while (!isValid) {
            cout << "Direction (NW/NE/SW/SE): ";
            string direction;
            getline (cin, direction);
            
            //Validate driection
            tie(isValid, d) = getBoard()->validateDirection(direction);
        }
        
        //If valid return, else loop
        if (isValidMove(row, column, d)) {
            loopForValid = true;
            return make_tuple(row, column, d, block);
        }
    }
    
    return make_tuple(1, 1, SE, block);
}

/* *********************************************************************
 Function Name: isValidMove:row:column:d
 Purpose: Check to see if valid move in
 Parameters:
 row, the row
 column, the column
 d, the direciton
 Return Value:
 yes if valid
 false if not valid
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
bool Human::isValidMove(int row, int column, Direction d) {
    
    string selectedPiece = getBoard()->pieceAt(row, column);
    
    switch (d) {
        case NE:
            row--;
            column++;
            break;
        case NW:
            row--;
            column--;
            break;
        case SE:
            row++;
            column++;
            break;
        case SW:
            row++;
            column--;
            break;
        default:
            break;
    }

    //Check to see if it is out of the bounds.
    if (row >= getBoard()->getBoardSize() || row < 0 || column >= getBoard()->getBoardSize() || column < 0) {
        cout << endl << "Invalid Move: Must stay on the board." << endl;
        return false;
    }

    //Check to see if there is a piece there.
    string piece = getBoard()->pieceAt(row, column);
    
    string userPiece = getColor();
    string computerPiece = (userPiece == "B") ? "W" : "B";
    
    if (computerPiece == piece) {
        if (selectedPiece == userPiece + userPiece){
            return true;
        } else {
            cout << "This piece must be a 'super-piece' to capture an opponent." << endl;
        }
        return false;
    } else if (userPiece == piece) {
        cout << endl << "Your piece occupies this space." << endl;
        return false;
    } else {
        return true;
    }
    
    return false;
}


