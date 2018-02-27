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

/* *********************************************************************
 Function Name: play
 Purpose: This is called when the player is asking for advice or when the compute ris making a move
 Parameters:none
 Return Value:
 a tuple consisting of
 int, the row
 int, the column
 Diection, the direction
 MoveType, capture/block/advance
 Local Variables:none
 Algorithm:
 1) check to see if there is any super pieces that can move
 2) if no super then check to see if we can block a piece
 3) if we cant block any piece just advance towards opponents home piece
 Assistance Received:
 https://www.daniweb.com/programming/software-development/tutorials/71858/user-input-strings-and-numbers-c
 ********************************************************************* */
tuple<int, int, Direction, MoveType> Player::play() {
    int r, c;
    Direction d;
    bool areSuperPieces, areBlockMoves;
    
    //See if there is any super pieces
    tie(r, c, d, areSuperPieces) = areAnySuperPieceMoves();
    
    //See if there is any block moves
    tie(r, c, d, areBlockMoves) = areAnyBlockMoves();
    
    if (areSuperPieces) {
        return make_tuple(r, c, d, capture);
    } else if (areBlockMoves) {
        return make_tuple(r, c, d, block);
    } else {
        //M
        if (getColor() == "B") {
            //get lowest row index piece and move it up.
            for(int i = 0; i < getBoard()->getBoardSize();i++) {
                for (int j = 0; j < getBoard()->getBoardSize();j++) {
                    string piece = getBoard()->pieceAt(i, j);
                    if (piece.substr(0, 1) == "B") {
                        if(!isValidMove(i, j, NW, false)) {
                            if(isValidMove(i, j, NE, false)) {
                                return make_tuple(i, j, NE, MoveType::advance);
                            }
                        } else {
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
                                return make_tuple(i, j, SW, MoveType::advance);
                            }
                        } else {
                            return make_tuple(i, j, SE, MoveType::advance);
                        }
                    }
                }
            }
        }
    }
    return make_tuple(1, 1, SE, MoveType::advance);
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

/* *********************************************************************
 Function Name: areAnySuperPieceMoves
 Purpose: Finds all the super pieces and checks to see if any surrending directions are opponents
 Parameters:none
 Return Value:
 tuple consisting of
 int the row
 int the column
 direction the direction
 bool if there is any or not
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
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
                        return make_tuple(i, j, direction, true);
                    }
                }
            }
        }
    }
    
    return make_tuple(1, 1, SE, false);
}

/* *********************************************************************
 Function Name: areAnyBlockMoves
 Purpose: Finds all the user pieces and checks to see if any surrending surronding directions are opponents
 Parameters:none
 Return Value:
 tuple consisting of
 int the row
 int the column
 direction the direction
 bool if there is any or not
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
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
                        int r, c;
                        Direction dd;
                        tie(r, c, dd, doesOccupy) = doesHumanOccupyNeighborSpots(i, j, direction);
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

/* *********************************************************************
 Function Name: doesHumanOccupyNeighborSpots:row:column:d
 Purpose: Finds all the super pieces and checks to see if any surrending directions are opponents
 Parameters:none
 Return Value:
 tuple consisting of
 int the row
 int the column
 direction the direction
 bool if there is any or not
 Local Variables:none
 Algorithm:
 for each direction surronding a piece
 check to see if that piece is an enemy piece. if it is then you are good because your blocking it.
 Assistance Received: none
 ********************************************************************* */
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
        } else {
            
            string piece = getBoard()->pieceAt(innerRow, innerColumn);
            string opponentPiece;
            
            (getColor() == "B") ? opponentPiece = "W" : opponentPiece = "B";
            if (piece == opponentPiece) {
                //Block this piece
                return make_tuple(originalRow, originalColumn, direction, true);
            } else {
                //There is no piece to block
            }
        }
    }
    
    return make_tuple(1, 1, SE, false);
}
