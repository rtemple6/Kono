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

void Tournament::startGame() {
    cout << "Welcome to Kono!" << endl;
    cout << "Player 1 vs. Computer" << endl;
    newRound();
}

void Tournament::newRound() {
    Game game;
    game.setUpBoard();
    game.determineOrder();
}

Tournament::Tournament() {
    
}
