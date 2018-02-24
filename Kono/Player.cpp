//
//  Player.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Player.hpp"

Player:: Player() {
    
}

void Player:: setTurn(bool turn) {
    this->isTurn = turn;
}

bool Player:: getIsTurn() {
    return this->isTurn;
}

void Player::setScore(int score) {
    this->score = score;
}

int Player::getScore() {
    return score;
}

void Player::setColor(string color) {
    this->color = color;
}

string Player::getColor() {
    return this->color;
}

tuple<int, int, Direction> Player::play() {
    return make_tuple(0, 0, NW);
}
