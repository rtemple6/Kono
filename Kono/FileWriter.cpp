//
//  FileWriter.cpp
//  Kono
//
//  Created by Ryan Temple on 2/24/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "FileWriter.hpp"

FileWriter:: FileWriter() {
    
}

/* *********************************************************************
 Function Name: saveGame:round:playerScore:playerColor:computerScore:computerColor:b:nextPlayer
 Purpose: Helper function for writing game state to file
 Parameters:
 round, the current round
 playerScore, the score of player
 playerColor, the color of the player
 computerScore, the scoreo of computer
 computerColor, the color of computer
 b, the board object
 nextplayer, name of next player
 Return Value:none
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void FileWriter::saveGame(int round, int playerScore, string playerColor, int computerScore, string computerColor, Board *b, string nextPlayer) {
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string filename;
    cout << "Enter a file name: ";
    getline(cin, filename);
    
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "Error saving file." << endl;
    } else {
        file << "Round: " << round << endl << endl;
        
        string computerColorLetter = (computerColor == "W") ? "White" : "Black";
        file << "Computer:" << endl << "   Score: " << computerScore << endl << "   Color: " << computerColorLetter << endl << endl;
        
        string userColorLetter = (playerColor == "W") ? "White" : "Black";
        file << "Human:" << endl << "   Score: " << playerScore << endl << "   Color: " << userColorLetter << endl << endl;
        
        file << "Board: " << endl;
        string **board = b->getBoard();
        for(int i = 0; i < b->getBoardSize(); i++) {
            for(int j = 0; j < b->getBoardSize(); j++) {
                if (j == 0) {
                    file << "   " << board[i][j];
                } else {
                    file << "  " << board[i][j];
                }
            }
            file << endl;
        }
        file << endl;
        
        file << "Next Player: " << nextPlayer << endl;
        
        file.close();
    }
}

