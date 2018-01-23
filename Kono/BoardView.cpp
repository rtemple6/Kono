//
//  BoardView.cpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "BoardView.hpp"
#include <iostream>
using namespace std;

BoardView::BoardView() {
    
}

void BoardView::drawBoardWithSize(int boardSize) {
    this->boardSize = boardSize;
    cout << "B B B B B" << endl;
    cout << "B O O O B" << endl;
    cout << "O O O O O" << endl;
    cout << "W O O O W" << endl;
    cout << "W W W W W" << endl;
}
