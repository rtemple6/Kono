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
using namespace std;

Tournament::Tournament() {
    this->user = new Human();
    this->computer = new Computer();
    this->game = new Game(user, computer);
}

void Tournament::startGame() {
    cout << "Welcome to Kono!" << endl << endl;
    
    game->rollDice();
    game->setUpBoard();
    
    //Computer move or show menu
    (computer->getIsTurn()) ? game->move(): provideMenu();
}

void Tournament::provideMenu() {
    int choice;
    cout << "Choose an option below" << endl;
    cout << "1. Save Game" << endl;
    cout << "2. Make A Move" << endl;
    cout << "3. Suggest Move" << endl;
    cout << "4. Quit Game" << endl;
    cout << "Your choice: ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "Saving game..." << endl;
            break;
        case 2:
            game->move();
            break;
        case 3:
            cout << "Suggesting move..." << endl;
            break;
        case 4:
            cout << "Quitting game..." << endl;
            break;
        default:
            cout << "Invalid choice: " << choice << endl << endl;
            provideMenu();
            break;
    }
}


void Tournament::setRound(int round) {
    
}
