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

//bool Board:: movePiece(int row, int column, Direction d) {
//    //N goes up, so subtract from row
//    //S goes down, so add to row
//    //E goes left, so subtract from column
//    //W goes right, so add from to column
//
//    //Check to see if it is their piece
//    if (user->getIsTurn()) {
//        string color = user->getColor();
//        string userPiece = pieceAt(row, column);
//        if (color != userPiece) {
//            cout << endl << "Invalid Move: Must select your piece (" << color << ")." << endl << endl;
//            return false;
//        }
//    } else {
//        string color = computer->getColor();
//        string computerPiece = pieceAt(row, column);
//        if (color != computerPiece) {
//            cout << endl << "Silly computer that's not your piece" << endl;
//            return false;
//        }
//    }
//
//    bool retVal = false;
//    switch (d) {
//        case NE:
//            if (isValidMove(row - 1, column + 1)) {
//                cout << "Moving piece at row: " << row << " column: " << column;
//                cout << " to row: " << row - 1 << " column: " << column + 1 << endl;
//                board[row][column] = 'O';
//                //Set the appropriate piece
//                board[row - 1][column + 1] = (user->getIsTurn()) ? user->getColor() : computer->getColor();
//                retVal = true;
//            }
//            break;
//        case NW:
//            if (isValidMove(row - 1, column - 1)) {
//                cout << "Moving piece at row: " << row << " column: " << column;
//                cout << " to row: " << row - 1 << " column: " << column - 1 << endl;
//                board[row][column] = 'O';
//                //Set the appropriate piece
//                board[row - 1][column - 1] = (user->getIsTurn()) ? user->getColor() : computer->getColor();
//                retVal = true;
//            }
//            break;
//        case SE:
//            if (isValidMove(row + 1, column + 1)) {
//                cout << "Moving piece at row: " << row << " column: " << column;
//                cout << " to row: " << row + 1 << " column: " << column + 1 << endl;
//                board[row][column] = 'O';
//                //Set the appropriate piece
//                board[row + 1][column + 1] = (user->getIsTurn()) ? user->getColor() : computer->getColor();
//                retVal = true;
//            }
//            break;
//        case SW:
//            if (isValidMove(row + 1, column - 1)) {
//                cout << "Moving piece at row: " << row << " column: " << column;
//                cout << " to row: " << row + 1 << " column: " << column - 1 << endl;
//                board[row][column] = 'O';
//                //Set the appropriate piece
//                board[row + 1][column - 1] = (user->getIsTurn()) ? user->getColor() : computer->getColor();
//                retVal = true;
//            }
//            break;
//        default:
//            break;
//    }
//    return retVal;
//}

void Human::play() {
    
    bool correctPiece = false;
    int row, column;
    while (!correctPiece) {
        
        cout << endl << "Move Piece" << endl;
        cout << "   Row: ";
        cin >> row;
        cout << "Column: ";
        cin >> column;
        
        string color = getColor();
        string userPiece = getBoard()->pieceAt(row - 1, column - 1);
        if (color != userPiece) {
            cout << endl << "Invalid Move: Must select your piece (" << color << ")." << endl;
        } else {
            correctPiece = true;
        }
    }

    //Found this line of code here https://www.daniweb.com/programming/software-development/tutorials/71858/user-input-strings-and-numbers-c
    //Allows for the string input after the 2 integer inputs
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout <<  "Valid Directions (NE/NW/SE/SW)" << endl;
    bool isValid = false;
    Direction d;
    while (!isValid) {
        cout << "Direction: ";
        string direction;
        getline (cin, direction);
        
        tie(isValid, d) = validateDirection(direction);
    }
    
    getBoard()->movePiece(row-1, column -1, d);
    getBoard()->drawBoard();
    
    //Subtract 1 to fix array position starting at 0
//    return make_tuple(row - 1, column - 1, d);
}

bool Human::isValidMove(int row, int column) {

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
        cout << endl << "Computer piece occupies this space." << endl;
        cout << "This is where capture functionality should go" << endl;
        return false;
    } else if (userPiece == piece) {
        cout << endl << "Your piece occupies this space." << endl;
        return false;
    } else {
        cout << "Valid move!" << endl;
        return true;
    }
    
    return false;
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
