//
//  Human.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Human.hpp"


Human:: Human(string color): Player(color) {
    setColor(color);
}

tuple<int, int, Direction, MoveType> Human::play() {
    
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
        
        string color = getColor();
        string userPiece = getBoard()->pieceAt(row, column);
        string piece = userPiece.substr(0, 1);
        if (color != piece) {
            validInputs = false;
            cout << endl << "Invalid Move: Must select your piece (" << color << ")." << endl;
        } else {
            correctPiece = true;
        }
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    bool isValid = false;
    Direction d;
    while (!isValid) {
        cout << "Direction (NW/NE/SW/SE): ";
        string direction;
        getline (cin, direction);
        
        tie(isValid, d) = getBoard()->validateDirection(direction);
    }
    
    if (isValidMove(row, column, d)) {
        return make_tuple(row, column, d, block);
    } else {
        play();
    }
    return make_tuple(1, 1, SE, block);
}

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


