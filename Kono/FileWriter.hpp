//
//  FileWriter.hpp
//  Kono
//
//  Created by Ryan Temple on 2/24/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef FileWriter_hpp
#define FileWriter_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Board.hpp"
using namespace std;

class FileWriter {
public:
    FileWriter();
    void saveGame(int round, int playerScore, string playerColor, int computerScore, string computerColor, Board *b, string nextPlayer);
};

#endif /* FileWriter_hpp */
