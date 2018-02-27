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

/* *********************************************************************
 Function Name: Tournament
 Purpose: initialization of the Tournament, creates the game
 Parameters:
 non
 Return Value: new Tournament
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
Tournament::Tournament() {
    //Creates a new game
    this->game = new Round();
}

/* *********************************************************************
 Function Name: startGame
 Purpose: First called when game starts, handles resuming a game or starting new one
 Parameters:
 none
 Return Value: none
 Local Variables:
 resume, char used for input when resuming game
 validChar, boolean value for input validation
 filename, name of file for resumegame
 loadDice, char used for input when loading dice
 validDice, bool value for input validation
 Algorithm:
 1)If resume game, get resume file and open
 2)Else if new game, ask for dice config and startgame
 3)else repeat
 Assistance Received: none
 ********************************************************************* */
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
            
            char loadDice;
            bool validDice = false;
            
            while (!validDice) {
                cout << "Load dice from config file (Dice.txt) (Y / N): ";
                cin >> loadDice;
                
                if (loadDice == 'Y' || loadDice == 'y') {
                    validDice = true;
                    game->rollDice(true);
                } else if (loadDice == 'N' || loadDice == 'n') {
                    validDice = true;
                    game->rollDice(false);
                }
            }
            
            game->setUpBoard();
            game->provideMenu();
        }
    }
}

/* *********************************************************************
 Function Name: resumeGame
 Purpose: Opens file from prevoius game and inits game with these values
 Parameters:
 filename, the name of the file that they will be opening
 Return Value: none
 Local Variables:
 round, the round they got from file
 playercolor, the player color from file
 computerColor, the computer color from file
 nextPlayer, the nextPlayer from file
 computerScore = computer score from file
 playerScore = playerScore from file
 count, the size of the board
 boardData, the 2d string array of the board
 Algorithm:
 1) Load data
 2) Init the board
 3) Show the menu to play
 Assistance Received: none
 ********************************************************************* */
void Tournament::resumeGame(string filename) {
    //Set filename inside FileReader for accessing the file
    f.setFileName(filename);
    
    //Get the round from file reader
    int round = f.getRound();
    cout << "Round: " << round << endl << endl;
    
    //Compute the colors for players
    string playerColor = f.getPlayerColor();
    string computerColor = f.getComputerColor();
    
    //Allocate the player/computer with color
    user = new Human(playerColor);
    computer = new Computer(computerColor);
    
    //Set the players of the game
    game->setPlayers(user, computer);
    
    //Get the nextPlayer and set turn
    string nextPlayer = f.getNextPlayer();
    if (nextPlayer == "Human") {
        user->setTurn(true);
        computer->setTurn(false);
    } else {
        user->setTurn(false);
        computer->setTurn(true);
    }
    
    //Get the scores for computer/user
    int computerScore = f.getComputerScore();
    computer->setScore(computerScore);
    int playerScore = f.getPlayerScore();
    user->setScore(playerScore);
    
    //Get the board data
    int count;
    string ** boardData;
    tie(count, boardData) = f.getBoard();
    
    //Let player know the details about game
    cout << "You are " << user->getColor() << "." << endl;
    cout << "Computer is " << computer->getColor() << "." << endl << endl;
    cout << "Your score is: " << user->getScore() << endl;
    cout << "Computer score is: " << computer->getScore() << endl << endl;
    
    //Set up game state.
    game->loadBoard(count, boardData);
    game->setRound(round);
    game->provideMenu();
}

