//
//  Player.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Player.hpp"

Player:: Player(string color) {
    setColor(color);
}

void Player:: setTurn(bool turn) {
    this->isTurn = turn;
}

bool Player:: getIsTurn() {
    return this->isTurn;
}

void Player::setBoard(Board *b) {
    this->board = b;
}

Board* Player::getBoard() {
    return board;
}

void Player::setScore(int score) {
    this->score = score;
}

int Player::getScore() {
    return score;
}

void Player::setColor(string color) {
    this->color = color;
}

string Player::getColor() {
    return this->color;
}

tuple<int, int, Direction, MoveType> Player::play() {
    int r, c;
    Direction d;
    bool areSuperPieces, areBlockMoves;
    
    tie(r, c, d, areSuperPieces) = areAnySuperPieceMoves();
    tie(r, c, d, areBlockMoves) = areAnyBlockMoves();
    
    if (areSuperPieces) {
        return make_tuple(r, c, d, capture);
    } else if (areBlockMoves) {
        return make_tuple(r, c, d, block);
    } else {
        if (getColor() == "B") {
            //get lowest row index piece and move it up.
            for(int i = 0; i < getBoard()->getBoardSize();i++) {
                for (int j = 0; j < getBoard()->getBoardSize();j++) {
                    string piece = getBoard()->pieceAt(i, j);
                    if (piece.substr(0, 1) == "B") {
                        if(!isValidMove(i, j, NW, false)) {
                            if(!isValidMove(i, j, NE, false)) {
//                                cout << "No advance moves." << endl;
                            } else {
                                
                                return make_tuple(i, j, NE, MoveType::advance);
                            }
                        } else {
//                            cout << "Computer moved piece (" << i + 1 << ", " << j + 1 << ") northwest to advance towards your home points." << endl << endl;
                            return make_tuple(i, j, NW, MoveType::advance);
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
//                                cout << "No advance moves." << endl;
                            } else {
//                                cout << "Computer moved piece (" << i + 1 << ", " << j + 1 << ") southwest to advance towards your home points." << endl << endl;
                                return make_tuple(i, j, SW, MoveType::advance);
                            }
                        } else {
//                            cout << "Computer moved piece (" << i + 1 << ", " << j + 1 << ") southeast to advance towards your home points." << endl << endl;
                            return make_tuple(i, j, SE, MoveType::advance);
                        }
                    }
                }
            }
        }
        
        //random piece in direction towards opponents home.
        
    }
    return make_tuple(1, 1, SE, MoveType::advance);
}

bool Player::isValidMove(int row, int column, Direction d, bool capture) {
    
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

tuple<int, int, Direction, bool> Player::areAnySuperPieceMoves() {
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
//                        cout << endl;
//                        getBoard()->movePiece(i, j, direction);
//                        getBoard()->drawBoard();
//                        cout << "The computer moved piece at (" << i + 1 << ", " << j + 1 << ") " << directionWord << " to capture your piece." << endl << endl;
                        return make_tuple(i, j, direction, true);
                    }
                }
            }
        }
    }
    
    return make_tuple(1, 1, SE, false);
}

tuple<int, int, Direction, bool> Player::areAnyBlockMoves() {
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
                
                //for each direction
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
                    //See if its valid
                    if (isValidMove(i, j, direction, false)) {
                        //See if neighbor is human
                        bool doesOccupy;
                        tie(i, j, direction, doesOccupy) = doesHumanOccupyNeighborSpots(i, j, direction);
                        if (doesOccupy) {
                        return make_tuple(i, j, direction, doesOccupy);
                        }
                        
                        
                    } else {
                        //Invalid direction, do nothing
                    }
                }
            }
        }
    }
    return make_tuple(1, 1, SE, false);
}

tuple<int, int, Direction, bool> Player::doesHumanOccupyNeighborSpots(int row, int column, Direction d) {
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
//
//            cout << "Inner row: " << innerRow << " <= " << getBoard()->getBoardSize() - 1 << endl;
//            cout << "Inner row: " << innerRow << " >= " << 0 << endl;
//
//            cout << "Inner column: " << innerColumn << " <= " << getBoard()->getBoardSize() - 1 << endl;
//            cout << "Inner column: " << innerColumn << " >= " << 0 << endl;
//
//            cout << endl;
        } else {
            
            cout << endl;
            string piece = getBoard()->pieceAt(innerRow, innerColumn);
            cout << "Piece at: "<< piece << endl;
            string opponentPiece;
            
            (getColor() == "B") ? opponentPiece = "W" : opponentPiece = "B";
            cout << "Opponent piece: "<< opponentPiece << endl;
            if (piece == opponentPiece) {
                //It will block this piece
//                cout << endl;
//                getBoard()->movePiece(originalRow, originalColumn, direction);
//                getBoard()->drawBoard();
//                cout << "The computer moved the piece at (" << originalRow + 1 << ", " << originalColumn + 1 << ") " << directionWord << "." << endl;
//                cout << "It wanted to block your piece at (" << innerRow + 1 << ", " << innerColumn + 1 << ")." << endl << endl;
                return make_tuple(originalRow, originalColumn, direction, true);
            } else {
                //There is no piece to block
                cout << "No piece. " << endl;
            }
        }
    }
    
    return make_tuple(1, 1, SE, false);
}
