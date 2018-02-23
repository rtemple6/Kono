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
    game->provideMenu();
//    //Computer move or show menu
//    (computer->getIsTurn()) ? game->move(): provideMenu();
}


void Tournament::setRound(int round) {
    
}
