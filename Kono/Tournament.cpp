//
//  Tournament.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Tournament.hpp"
#include "Round.hpp"
#include <iostream>
using namespace std;

Tournament::Tournament() {
    this->game = new Round();
}

void Tournament::startGame() {
    cout << "Welcome to Kono!" << endl << endl;
    
    char resume;
    bool validChar = false;
    
    while (!validChar) {
        cout << "Would you like to resume a previous game? (Y / N): ";
        cin >> resume;
        
        if (resume == 'Y' || resume == 'y') {
            validChar = true;
            string fileName = f.validateFile();
            resumeGame(fileName);
            
        } else if (resume == 'N' || resume == 'n') {
            validChar = true;
            
            char loadDice;
            bool validDice = false;
            
            while (!validDice) {
                cout << "Load dice from config file (Dice.txt) (Y / N): ";
                cin >> loadDice;
                
                if (loadDice == 'Y' || loadDice == 'y') {
                    validDice = true;
                    game->rollDice(true);
                } else if (loadDice == 'N' || loadDice == 'n') {
                    validDice = true;
                    game->rollDice(false);
                }
            }
            
            game->setUpBoard();
            game->provideMenu();
        }
    }
}

bool Tournament::resumeGame(string filename) {
    f.setFileName(filename);
    
    int round = f.getRound();
    cout << "Round: " << round << endl << endl;
    
    string playerColor = f.getPlayerColor();
    string computerColor = f.getComputerColor();
    
    user = new Human(playerColor);
    computer = new Computer(computerColor);
    
    game->setPlayers(user, computer);
    
    string nextPlayer = f.getNextPlayer();
    if (nextPlayer == "Human") {
        user->setTurn(true);
        computer->setTurn(false);
    } else {
        user->setTurn(false);
        computer->setTurn(true);
    }
    
    int computerScore = f.getComputerScore();
    computer->setScore(computerScore);
    
    
    
    int playerScore = f.getPlayerScore();
    user->setScore(playerScore);
    
   
    
    int count;
    string ** boardData;
    tie(count, boardData) = f.getBoard();
    
    cout << "You are " << user->getColor() << "." << endl;
    cout << "Computer is " << computer->getColor() << "." << endl << endl;
    
    cout << "Your score is: " << user->getScore() << endl;
    cout << "Computer score is: " << computer->getScore() << endl << endl;
    
    game->loadBoard(count, boardData);
    game->setRound(round);
    game->provideMenu();
    return true;
}

