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

void Computer::play() {
    //Does the computer have any super pieces?
    if (areAnySuperPieceMoves()) {
        
    } else if (areAnyBlockMoves()) {
        
    } else {
        //random piece in direction towards opponents home.
    }
}

bool Computer::isValidMove(int row, int column, Direction d) {
    
    string selectedPiece = getBoard()->pieceAt(row, column);
    
    switch (d) {
        case NE:
            row--;
            column++;
            break;
        case NW:
            row--;
            column--;
        case SE:
            row++;
            column++;
        case SW:
            row++;
            column--;
        default:
            break;
    }
    
    
    //Check to see if it is out of the bounds.
    if (row >= getBoard()->getBoardSize() || row < 0 || column >= getBoard()->getBoardSize() || column < 0) {
        return false;
    }
    
    //Check to see if there is a piece there.
    string piece = getBoard()->pieceAt(row, column);
    
    string computerPiece = getColor();
    string userPiece = (computerPiece == "B") ? "W" : "B";
    
    if (userPiece == piece) {
        if (selectedPiece == userPiece + userPiece){
            return true;
        }
        return false;
    } else if (computerPiece == piece) {
        return false;
    } else {
        return true;
    }
    
    return false;
}

bool Computer::areAnySuperPieceMoves() {
    //Find each super piece
    //Check NE/NW/SE/SW
    //If can capture, move and return true
    //Else return false
    string superPiece = getColor() + getColor();
    
    int boardSize = getBoard()->getBoardSize();
    Direction direction;
    string directionWord;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            string piece = getBoard()->pieceAt(i, j);
            if (piece == superPiece){
                for (int d = 0; d < 4; d++) {
                    if (d == 0) {
                        direction = NE;
                        directionWord = "northeast";
                    } else if (d == 1) {
                        direction = NW;
                        directionWord = "northwest";
                    } else if (d == 2) {
                        direction = SE;
                        directionWord = "southeast";
                    } else {
                        direction = SW;
                        directionWord = "southwest";
                    }
                    if (isValidMove(i, j, direction)) {
                        cout << endl;
                        getBoard()->movePiece(i, j, direction);
                        getBoard()->drawBoard();
                        cout << "The computer moved piece at (" << i << ", " << j << ") " << directionWord << " to capture your piece." << endl << endl;
                        return true;
                    }
                }
            }
        }
    }
    
    return false;
}

bool Computer::areAnyBlockMoves() {
    //For each computer piece
    //Go each direction
    string userPiece = getColor();
    string superPiece = getColor() + getColor();
    
    int boardSize = getBoard()->getBoardSize();
    Direction direction;
    string directionWord;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            string piece = getBoard()->pieceAt(i, j);
            if (piece == superPiece || piece == userPiece){
                for (int d = 0; d < 4; d++) {
                    if (d == 0) {
                        direction = NE;
                        directionWord = "northeast";
                    } else if (d == 1) {
                        direction = NW;
                        directionWord = "northwest";
                    } else if (d == 2) {
                        direction = SE;
                        directionWord = "southeast";
                    } else {
                        direction = SW;
                        directionWord = "southwest";
                    }
                    cout << "Before is valid: (Row, Column) " << i << ", " << j << endl;
                    if (isValidMove(i, j, direction)) {
                        //Check directions
                        //If opponent piece occupies one spot
                        //Move and say your blocking
                        cout << "Direction word: " << directionWord << endl;
                        if (doesHumanOccupyNeighborSpots(i, j, direction)) {
                            return true;
                        }
                        cout << endl;
                    } else {
                        cout << "Invalid direction: " << directionWord << endl;
                    }
                }
            }
        }
    }
    return false;
}

bool Computer::doesHumanOccupyNeighborSpots(int row, int column, Direction d) {
    string directionWord;
    int originalRow = row;
    int originalColumn = column;
    
    cout << "Does occupy: Row/Column/Direction " << row << ", " << column << ", " << d << endl;
    
    //Move piece to new tmp location
    switch (d) {
        case NE:
            row--;
            column++;
            directionWord = "northeast";
            break;
        case NW:
            row--;
            column--;
            directionWord = "northwest";
            break;
        case SE:
            row++;
            column++;
            directionWord = "southeast";
            break;
        case SW:
            row++;
            column--;
            directionWord = "southwest";
            break;
        default:
            break;
    }
    
    int newRow = row;
    int newColumn = column;
    
    int innerRow = newRow;
    int innerColumn = newColumn;
    
    cout << "New (Row, Column): " << row << ", " << column << endl;
    
    Direction direction;
    
    for (int d = 0; d < 4; d++) {
        if (d == 0) {
            direction = NE;
        } else if (d == 1) {
            direction = NW;
        } else if (d == 2) {
            direction = SE;
        } else {
            direction = SW;
        }
        
        switch (direction) {
            case NE:
                innerRow = newRow - 1;
                innerColumn = newColumn + 1;
                break;
            case NW:
                innerRow = newRow - 1;
                innerColumn = newColumn - 1;
                break;
            case SE:
                innerRow = newRow + 1;
                innerColumn = newColumn + 1;
                break;
            case SW:
                innerRow = newRow + 1;
                innerColumn = newColumn - 1;
                break;
            default:
                break;
        }
        
        cout << endl;
        cout << "New Row: " << innerRow << endl;
        cout << "New Colum: " << innerRow << endl;
        cout << "Direction: " << direction << endl;
        
        //Check to see if it is out of the bounds.
        if (innerRow >= getBoard()->getBoardSize() || innerRow < 0 || innerColumn >= getBoard()->getBoardSize() || innerColumn < 0) {
            cout << "Out of bounds" << endl;
        } else {
            
            string piece = getBoard()->pieceAt(innerRow, innerColumn);
            cout << "Le piece: " << piece << endl;
            string opponentPiece;
            (getColor() == "B") ? opponentPiece = "W" : opponentPiece = "B";
            if (piece == opponentPiece) {
                //It will block this piece
                cout << endl;
                getBoard()->movePiece(originalRow, originalColumn, direction);
                getBoard()->drawBoard();
                cout << "The computer moved the piece at (" << originalRow + 1 << ", " << originalColumn + 1 << ") " << directionWord << "." << endl;
                cout << "It wanted to block your piece at (" << innerRow + 1 << ", " << innerColumn + 1 << ")." << endl;
                return true;
            } else {
                //There is no piece to block
            }
        }
        
        
        
    }
    
    return false;
}
