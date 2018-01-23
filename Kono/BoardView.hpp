//
//  BoardView.hpp
//  Kono
//
//  Created by Ryan Temple on 1/23/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#ifndef BoardView_hpp
#define BoardView_hpp

#include <stdio.h>

class BoardView {
    int boardSize = 5;
    
public:
    BoardView();
    void drawBoardWithSize(int boardSize);
};

#endif /* BoardView_hpp */
