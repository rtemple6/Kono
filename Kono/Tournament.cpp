//
//  Tournament.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Tournament.hpp"
#include "Game.hpp"
#include <iostream>
#include "FileReader.hpp"
using namespace std;

Tournament::Tournament() {
    this->user = new Human();
    this->computer = new Computer();
    this->game = new Game(user, computer);
}

void Tournament::startGame() {
    cout << "Welcome to Kono!" << endl << endl;
    
    char resume;
    cout << "Would you like to resume a previous game? (Y / N): ";
    cin >> resume;
    cout << endl;
    if (resume == 'Y') {
        resumeGame();
    } else {
        game->rollDice();
        game->setUpBoard();
        game->provideMenu();
    }
    
}

void Tournament::resumeGame() {
    FileReader f;
    f.setFileName("SavedGame.txt");
    
    int round = f.getRound();
    cout << "Round: " << round << endl;
    
    string nextPlayer = f.getNextPlayer();
    cout << "Next Player: " << nextPlayer << endl;
    
    int computerScore = f.getComputerScore();
    cout << "Computer score: " << computerScore << endl;
    
    string computerColor = f.getComputerColor();
    cout << "Computer color: " << computerColor << endl;
    
    int playerScore = f.getPlayerScore();
    cout << "Player score: " << playerScore << endl;
    
    string playerColor = f.getPlayerColor();
    cout << "Player color: " << playerColor << endl;
    
    
}

void Tournament::setRound(int round) {
    
}
