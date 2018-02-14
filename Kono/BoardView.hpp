//
//  BoardView.hpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef BoardView_hpp
#define BoardView_hpp

#include "Board.hpp"
#include <stdio.h>

class BoardView {
    Board *board;
public:
    BoardView();
    void setBoard(Board *b);
    void draw();
};

#endif /* BoardView_hpp */
