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
    this->user = new Human();
    this->computer = new Computer();
    this->game = new Round(user, computer);
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
            game->rollDice();
            game->setUpBoard();
            game->provideMenu();
        }
    }
}

bool Tournament::resumeGame(string filename) {
    f.setFileName(filename);
    
    int round = f.getRound();
    cout << "Round: " << round << endl << endl;
    
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
    
    string computerColor = f.getComputerColor();
    computer->setColor(computerColor);
    
    int playerScore = f.getPlayerScore();
    user->setScore(playerScore);
    
    string playerColor = f.getPlayerColor();
    user->setColor(playerColor);
    
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

