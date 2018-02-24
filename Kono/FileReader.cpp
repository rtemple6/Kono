//
//  FileReader.cpp
//  Kono
//
//  Created by Ryan Temple on 2/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "FileReader.hpp"

FileReader:: FileReader() {
    
}

void FileReader::openFile() {
    stream.open(filename);
}

void FileReader::closeFile() {
    stream.close();
}

string ** FileReader:: createBoard(int size, string data[]) {
    //Init board
    string ** board = new string *[size];
    for(int i = 0; i < size; i++) {
        board[i] = new string[size];
    }
    
    //Fill board
    int tmpCounter = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << "Board[" << i << "][" << j << "] is data[" << i + j << "] : " << data[i+j] << endl;
            board[i][j] = data[tmpCounter];
            tmpCounter++;
        }
    }
    
    return board;
}

void FileReader::setFileName(string name) {
    filename = name;
}

int FileReader::getRound() {
    openFile();
    
    //Read in string from the first line.
    string roundIn, round;
    for (int i = 1; !stream.eof() ; i++)
    {
        getline(stream, roundIn);
        
        if (i < 1 || i > 1)  continue;
        
        round.append(roundIn);
    }
    //Remove 'Round: '
    round.erase(0, 7);
    
    closeFile();
    
    //Convert string to int
    return atoi(round.c_str());
}

string FileReader::getNextPlayer() {
    openFile();
    
    string nextPlayer;
    for (int i = 1; !stream.eof(); i++) {
        stream >> nextPlayer;
    }
    
    closeFile();
    
    return nextPlayer;
}

int FileReader::getComputerScore() {
    openFile();
    
    string computerIn, computer;
    for (int i = 1; !stream.eof() ; i++)
    {
        getline(stream, computerIn);
    
        if (i < 4 || i > 4)  continue;
    
        computer.append(computerIn);
    }
    computer.erase(0, 10);
    
    closeFile();
    return atoi(computer.c_str());;
}

string FileReader::getComputerColor() {
    openFile();
    
    string computerIn, computer;
    for (int i = 1; !stream.eof() ; i++)
    {
        getline(stream, computerIn);
        
        if (i < 5 || i > 5)  continue;
        
        computer.append(computerIn);
    }
    computer.erase(0, 10);
    
    
    closeFile();
    return computer;
}

int FileReader::getPlayerScore() {
    openFile();
    
    string playerIn, player;
    for (int i = 1; !stream.eof() ; i++)
    {
        getline(stream, playerIn);
        
        if (i < 8 || i > 8)  continue;
        
        player.append(playerIn);
    }
    player.erase(0, 10);
    
    closeFile();
    return atoi(player.c_str());;
}

string FileReader::getPlayerColor() {
    openFile();
    
    string playerIn, player;
    for (int i = 1; !stream.eof() ; i++)
    {
        getline(stream, playerIn);
        
        if (i < 9 || i > 9)  continue;
        
        player.append(playerIn);
    }
    player.erase(0, 10);
    
    
    closeFile();
    return player;
}

tuple<int, string**> FileReader:: getBoard() {
    
    openFile();
    
    
    //Place all the letters into a 1D array.
    string boardCount[500];
    
    //Keep count to know boardSize (5, 7, 9)
    int tempCounter = 0;
    
    string boardIn;
    for (int i = 1; !stream.eof() ; i++) {
        stream >> boardIn;
        if (i < 13) continue;
        
        //Append to our array if its a piece
        if (boardIn == "B" || boardIn == "BB" || boardIn == "W" || boardIn == "WW" || boardIn == "O") {
            boardCount[tempCounter] = boardIn;
            tempCounter++;
        }
    }
    
    //Extract data in array to be a 2d array.
    switch (tempCounter) {
        case 25:
            //5 x 5
            
            return make_tuple(5, createBoard(5, boardCount));
            break;
        case 49:
            //7 x 7
            return make_tuple(7, createBoard(7, boardCount));
            break;
        case 81:
            //9 x 9
            return make_tuple(9, createBoard(9, boardCount));
            break;
        default:
            break;
    }
    
    
    return make_tuple(0, createBoard(0, boardCount));
}



