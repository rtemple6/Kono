//
//  FileReader.hpp
//  Kono
//
//  Created by Ryan Temple on 2/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class FileReader {
    ifstream stream;
    string filename;
    
    void openFile();
    void closeFile();
public:
    FileReader();
    
    void setFileName(string name);
    
    int getRound();
    
    string getNextPlayer();
    
    int getComputerScore();
    string getComputerColor();
    
    int getPlayerScore();
    string getPlayerColor();
};

#endif /* FileReader_hpp */
