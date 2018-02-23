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

//
//gameData.close();
//gameData.open("SavedGame.txt");
//

//
//gameData.close();
//gameData.open("SavedGame.txt");
//
//string humanIn, human;
//for (int i = 1; !gameData.eof() ; i++)
//{
//    getline(gameData, humanIn);
//
//    if (i < 8 || i > 9)  continue;
//
//    human.append(humanIn);
//}
//cout << "Human: " << human << endl;
//
//gameData.close();
//gameData.open("SavedGame.txt");
//

//
//gameData.close();
//gameData.open("SavedGame.txt");
//
//string boardIn, board;
//for (int i = 1; !gameData.eof() ; i++) {
//    gameData >> boardIn;
//    if (i < 13) continue;
//    board.append(boardIn);
//}
//string delimiter = "NextPlayer";
//board = board.substr(0, board.find(delimiter));
//board.erase(0, 6);
//cout << "Board: " << board << endl;
//gameData.close();

