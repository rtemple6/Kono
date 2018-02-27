//
//  Board.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Board.hpp"
#include "BoardView.hpp"

Board::Board() {
}

int Board::getPieceCount(string color) {
    int count = 0;
    for (int i = 0; i < getBoardSize(); i++) {
        for (int j = 0; j < getBoardSize(); j++) {
            string piece = pieceAt(i, j);
            if (piece == color || piece == color + color) {
                count++;
            }
        }
    }
    return count;
}

int Board::getPiecesScoredCount(string color) {
    int tmp = getBoardSize() - 1;
    int count = 0;
    //See if all black pieces are in top row/first-last position in second row
    for (int i = 0; i < getBoardSize(); i++) {
        for (int j = 0; j < getBoardSize(); j++) {
            string piece = pieceAt(i, j);
            if (color == "B") {
                
                //Black pieces
                if (i == 0) {
                    if (piece == color || piece == color + color) {
                        count++;
                    }
                } else if (i == 1) {
                    if (j == 0 || j == tmp) {
                        if (piece == color || piece == color + color) {
                            count++;
                        }
                    }
                }
            } else {
                
                //White pieces
                if (i == tmp) {
                    if (piece == color || piece == color + color) {
                        count++;
                    }
                } else if (i == tmp - 1) {
                    if (j == 0 || j == tmp) {
                        if (piece == color || piece == color + color) {
                            count++;
                        }
                    }
                }
            }
            
        }
    }
    return count;
}

void Board::createBoard(int size) {
    this->boardSize = size;
    
    //Used to determine end piece.
    int tmp = size -1;
    
    //This creates a 1-Dimensional Array of pointers
    //Each pointer points to an array of values
    this->board = new string *[size];
    for(int i = 0; i < size; i++) {
        this->board[i] = new string[size];
    }
    
    //Fill the board
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if (i == 0) {
                //First row
                this->board[i][j] = "W";
            } else if (i == 1) {
                //Second row
                if (j == 0) {
                    //First piece
                    this->board[i][j] = "W";
                } else if (j == tmp) {
                    //Last piece
                    this->board[i][j] = "W";
                } else {
                    //Filler piece
                    this->board[i][j] = "O";
                }
            } else if (i == tmp - 1) {
                //Second to last row
                if (j == 0) {
                    //First piece
                    this->board[i][j] = "B";
                } else if (j == tmp) {
                    //Last piece
                    this->board[i][j] = "B";
                } else {
                    //Filler piece
                    this->board[i][j] = "O";
                }
            } else if (i == tmp) {
                //Last row
                this->board[i][j] = "B";
            } else {
                //Filler spaces
                this->board[i][j] = "O";
            }
        }
    }
}

void Board::setBoard(int size, string **data) {
    boardSize = size;
    board = data;
}

string ** Board::getBoard() {
    return board;
}

int Board::getBoardSize() {
    return this->boardSize;
}

string Board::pieceAt(int row, int column) {
    string piece = board[row][column];
    if (piece == "O") {
        return "+";
    }
    return piece;
}

void Board::drawBoard() {
    BoardView view;
    view.setBoard(this);
    view.draw();
}

bool Board:: movePiece(int row, int column, Direction d) {
    //N goes up, so subtract from row
    //S goes down, so add to row
    //E goes left, so subtract from column
    //W goes right, so add from to column

    string piece = pieceAt(row, column);
    bool retVal = false;
    switch (d) {
        case NE:
            if (piece.substr(0, 1) == "B" && row - 1 == 0) {
                board[row - 1][column + 1] = "BB";
            } else {
                board[row - 1][column + 1] = piece;
            }
            board[row][column] = 'O';
            retVal = true;
            break;
        case NW:
            if (piece.substr(0, 1) == "B" && row - 1 == 0) {
                board[row - 1][column - 1] = "BB";
            } else {
                board[row - 1][column - 1] = piece;
            }
            board[row][column] = 'O';
            retVal = true;
            break;
        case SE:
            if (piece.substr(0, 1) == "W" && row + 1 == getBoardSize() - 1) {
                board[row + 1][column + 1] = "WW";
            } else {
                board[row + 1][column + 1] = piece;
            }
            board[row][column] = 'O';
            retVal = true;
            break;
        case SW:
            if (piece.substr(0, 1) == "W" && row + 1 == getBoardSize() - 1) {
                board[row + 1][column - 1] = "WW";
            } else {
                board[row + 1][column - 1] = piece;
            }
            board[row][column] = 'O';
            retVal = true;
            break;
        default:
            break;
    }
    return retVal;
}

bool Board::isPieceAtLocation(int row, int column) {
    if (row > boardSize || row < 0 || column > boardSize || column < 0) {
        cout << endl << "Invalid Move: Must stay on the board!" << endl;
        return false;
    }
    //Check to see if there is a piece there.
    //Check to see if it is out of the bounds.
    return false;
}

tuple<bool, Direction> Board:: validateDirection(string direction){
    
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

bool Board::checkForWinner() {
    int blackPieces = getPieceCount("B");
    int whitePieces = getPieceCount("W");
    
    int blackHomePieceCount = getPiecesScoredCount("B");
    int whiteHomePieceCount = getPiecesScoredCount("W");
    
    if (blackHomePieceCount == blackPieces) {
        setWinnerPiece("B");
        return true;
    }
    
    if (whiteHomePieceCount == whitePieces) {
        setWinnerPiece("W");
        return true;
    }
    
    return false;
}

void Board::setWinnerPiece(string piece) {
    this->winnerPiece = piece;
}

string Board::getWinnerPiece() {
    return winnerPiece;
}

int Board::getScore(string piece) {
    int tmp = getBoardSize() - 1;
    int score = 0;
    for (int i = 0; i < getBoardSize(); i++) {
        for (int j = 0; j < getBoardSize(); j++) {
            string pieceAtLocation = pieceAt(i, j);
            
            if(piece == "B") {
                if (i == 0) {
                    //First row
                    switch (getBoardSize()) {
                        case 5:
                            switch (j) {
                                case 0:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                case 1:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 2:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 5;
                                    }
                                    break;
                                case 3:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 4:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 7:
                            switch (j) {
                                case 0:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                case 1:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 2:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 5;
                                    }
                                    break;
                                case 3:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 7;
                                    }
                                    break;
                                case 4:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 5;
                                    }
                                    break;
                                case 5:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 6:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 9:
                            switch (j) {
                                case 0:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                case 1:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 2:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 5;
                                    }
                                    break;
                                case 3:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 7;
                                    }
                                    break;
                                case 4:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 9;
                                    }
                                    break;
                                case 5:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 7;
                                    }
                                    break;
                                case 6:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 5;
                                    }
                                    break;
                                case 7:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 8:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                default:
                                    break;
                            }
                            break;
                            
                        default:
                            break;
                    }
                } else if (i == 1) {
                    //Second row
                    if (j == 0 || j == tmp) {
                        if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                            score = score + 1;
                        }
                    }
                }
            } else {
                if (i == getBoardSize() - 1) {
                    //First row
                    switch (getBoardSize()) {
                        case 5:
                            switch (j) {
                                case 0:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                case 1:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 2:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 5;
                                    }
                                    break;
                                case 3:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 4:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 7:
                            switch (j) {
                                case 0:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                case 1:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 2:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 5;
                                    }
                                    break;
                                case 3:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 7;
                                    }
                                    break;
                                case 4:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 5;
                                    }
                                    break;
                                case 5:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 6:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 9:
                            switch (j) {
                                case 0:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                case 1:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 2:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 5;
                                    }
                                    break;
                                case 3:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 7;
                                    }
                                    break;
                                case 4:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 9;
                                    }
                                    break;
                                case 5:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 7;
                                    }
                                    break;
                                case 6:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 5;
                                    }
                                    break;
                                case 7:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 1;
                                    }
                                    break;
                                case 8:
                                    if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                                        score = score + 3;
                                    }
                                    break;
                                default:
                                    break;
                            }
                            break;
                            
                        default:
                            break;
                    }
                } else if (i == tmp - 1) {
                    //Second row
                    if (j == 0 || j == tmp) {
                        if (pieceAtLocation == piece || pieceAtLocation == piece + piece) {
                            score = score + 1;
                        }
                    }
                }
            }
        }
    }
    
    
    //Get the amount of pieces the player captured.
    if (piece == "B") {
        //Get white pieces count
        int whiteCount = getPieceCount("W");
        int elimantedPieces = (getBoardSize() + 2) - whiteCount;
        score = score + (elimantedPieces * 5);
    } else {
        int blackCount = getPieceCount("B");
        int elimatedPieces = (getBoardSize() + 2)  - blackCount;
        score = score + (elimatedPieces * 5);
    }
    
    return score;
}
