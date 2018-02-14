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
    
}

void Tournament::startGame() {
    cout << "Welcome to Kono!" << endl << endl;
    Game game;
    game.determineOrder();
    game.setUpBoard();
}
