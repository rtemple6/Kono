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
        if (getColor() == "B") {
            //get lowest row index piece and move it up.
            for(int i = 0; i < getBoard()->getBoardSize();i++) {
                for (int j = 0; j < getBoard()->getBoardSize();j++) {
                    string piece = getBoard()->pieceAt(i, j);
                    if (piece.substr(0, 1) == "B") {
                        if(!isValidMove(i, j, NW, false)) {
                            if(!isValidMove(i, j, NE, false)) {
                                cout << "No advance moves." << endl;
                            } else {
                                getBoard()->movePiece(i, j, NE);
                                getBoard()->drawBoard();
                                cout << "Computer moved piece (" << i + 1 << ", " << j + 1 << ") northeast to advance towards your home points." << endl << endl;
                                return;
                            }
                        } else {
                            getBoard()->movePiece(i, j, NW);
                            getBoard()->drawBoard();
                            cout << "Computer moved piece (" << i + 1 << ", " << j + 1 << ") northwest to advance towards your home points." << endl << endl;
                            return;
                        }
                    }
                }
            }
        } else {
            //get lowest row index piece and move it up.
            int size = getBoard()->getBoardSize() - 1;
            for(int i = size; i >= 0; i--) {
                for (int j = 0; j < getBoard()->getBoardSize();j++) {
                    string piece = getBoard()->pieceAt(i, j);
                    if (piece.substr(0, 1) == "W") {
                        if(!isValidMove(i, j, SE, false)) {
                            if(!isValidMove(i, j, SW, false)) {
                                cout << "No advance moves." << endl;
                            } else {
                                getBoard()->movePiece(i, j, SW);
                                getBoard()->drawBoard();
                                cout << "Computer moved piece (" << i + 1 << ", " << j + 1 << ") southwest to advance towards your home points." << endl << endl;
                                return;
                            }
                        } else {
                            getBoard()->movePiece(i, j, SE);
                            getBoard()->drawBoard();
                            cout << "Computer moved piece (" << i + 1 << ", " << j + 1 << ") southeast to advance towards your home points." << endl << endl;
                            return;
                        }
                    }
                }
            }
        }
        
        //random piece in direction towards opponents home.
        
    }
}

bool Computer::isValidMove(int row, int column, Direction d, bool capture) {
    
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
        return false;
    }
    
    string piece = getBoard()->pieceAt(row, column);
    
    string computerPiece = getColor();
    string userPiece = (computerPiece == "B") ? "W" : "B";
    
    if (userPiece == piece) {
        if (selectedPiece == computerPiece + computerPiece){
            return true;
        }
        return false;
    } else if (computerPiece == piece) {
        return false;
    } else {
        if (capture){
            return false;
        }
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
                    if (isValidMove(i, j, direction, true)) {
                        cout << endl;
                        getBoard()->movePiece(i, j, direction);
                        getBoard()->drawBoard();
                        cout << "The computer moved piece at (" << i + 1 << ", " << j + 1 << ") " << directionWord << " to capture your piece." << endl << endl;
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
                    if (isValidMove(i, j, direction, false)) {
                        //Check directions
                        //If opponent piece occupies one spot
                        //Move and say your blocking
                        if (doesHumanOccupyNeighborSpots(i, j, direction)) {
                            return true;
                        }
                    } else {
                        //Invalid direction, do nothing
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
        
        
        //Check to see if it is out of the bounds.
        if (innerRow >= getBoard()->getBoardSize() - 1 || innerRow <= 0 || innerColumn >= getBoard()->getBoardSize() - 1 || innerColumn <= 0) {
            //Out of bounds
        } else {
            
            string piece = getBoard()->pieceAt(innerRow, innerColumn);
            string opponentPiece;
            (getColor() == "B") ? opponentPiece = "W" : opponentPiece = "B";
            if (piece == opponentPiece) {
                //It will block this piece
                cout << endl;
                getBoard()->movePiece(originalRow, originalColumn, direction);
                getBoard()->drawBoard();
                cout << "The computer moved the piece at (" << originalRow + 1 << ", " << originalColumn + 1 << ") " << directionWord << "." << endl;
                cout << "It wanted to block your piece at (" << innerRow + 1 << ", " << innerColumn + 1 << ")." << endl << endl;
                return true;
            } else {
                //There is no piece to block
            }
        }
        
        
        
    }
    
    return false;
}
