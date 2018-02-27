//
//  Round.cpp
//  Kono
//
//  Created by Ryan Temple on 2/24/18.
//  Copyright © 2018 Ryan Temple. All rights reserved.
//

#include "Round.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <ctype.h>

using namespace std;

/* *********************************************************************
 Function Name: Round()
 Purpose: Initializes a new round
 Parameters:
 none
 Return Value: new round
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
Round::Round() {
    this->board = new Board();
}

/* *********************************************************************
 Function Name: setPlayers:h:c
 Purpose: Sets the players of the game
 Parameters:
 h, the human player object
 c, the compuer player object
 Return Value: none
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round::setPlayers(Human *h, Computer *c) {
    this->user = h;
    this->computer = c;
}

/* *********************************************************************
 Function Name: setRound:round
 Purpose: Sets the round number of the game they are on
 Parameters:
 round, the round number they are on
 Return Value: none
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round::setRound(int round) {
    this->round = round;
}

/* *********************************************************************
 Function Name: getRound
 Purpose: gets the round number
 Parameters:none
 Return Value: the round number
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
int Round::getRound() {
    return this->round;
}

/* *********************************************************************
 Function Name: setUpBoard
 Purpose: Asks for board size, validates, then creates / draws the board
 Parameters:none
 Return Value: none
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round::setUpBoard() {
    int size = 5;
    bool validSize = false;
    while (!validSize) {
        cout << "Select board size (5, 7, or 9): ";
        cin >> size;
        while(cin.fail()) {
            cout << "Select board size (5, 7, or 9): ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> size;
        }
        if (size == 5 || size == 7 || size == 9) {
            validSize = true;
        } 
    }
    
    cout << endl;
    this->board->createBoard(size);
    this->user->setBoard(board);
    this->computer->setBoard(board);
    this->board->drawBoard();
}

/* *********************************************************************
 Function Name: loadBoard:size:data
 Purpose: This is for when they load board from file, sets board then draws it
 Parameters:
 size, the size of board(5/7/9)
 data, the board data
 Return Value: none
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round:: loadBoard(int size, string **data) {
    this->board->setBoard(size, data);
    this->user->setBoard(board);
    this->computer->setBoard(board);
    this->board->drawBoard();
}

/* *********************************************************************
 Function Name: nextRound:winner
 Purpose: Used for determining who starts next round.
 Parameters:
 winner, the winner of the previous round
 Return Value: none
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round::nextRound(string winner) {
    if (winner == "Human") {
        user->setTurn(true);
        computer->setTurn(false);
    } else {
        cout << endl << "Computer won the previous round so he chooses color." << endl;
        computer->setTurn(true);
        user->setTurn(false);
    }
    
    chooseColor();
}

/* *********************************************************************
 Function Name: rollDice:fromConfig
 Purpose: Rolling dice for the game to see who goes first. Used to call FileReader
 to read dice from file. Will call set color after the order is determined.
 Parameters:
 fromConfig, if you want to read from file set to true
 Return Value: none
 Local Variables:
 r, the fileReader that will read form file
 player1Score = the random score for the user
 player2Score = the random score for the computer
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round::rollDice(bool fromConfig) {
    cout << endl << "Round " << getRound() << endl << endl;
    //Seed the random time
    srand(time(0));
    
    FileReader r;
    
    //Determine if reading from file
    if (fromConfig) {
        
        //Set file name
        r.setFileName("Dice.txt");
        
        //Get winner
        string winner = r.loadDice();
        
        //Based on winner choose the colors
        if (winner == "Human") {
            cout << "You will go first!" << endl;
            chooseColor();
        } else {
            cout << "Computer will go first and choose color." << endl;
            computerChooseColor();
        }
    } else {
        
        //Get random numbers for each player
        int player1Score = rand() % 12 + 1;
        int player2Score = rand() % 12 + 1;
        
        cout << "* Rolling dice to see who goes first *" << endl << endl;
        cout << "You Rolled: " << player1Score << endl;
        cout << "Computer Rolled: " << player2Score << endl;
        
        //If they are same value, recursively call determine order.
        if (player1Score == player2Score) {
            cout << "You tied." << endl;
            rollDice(fromConfig);
            return;
        }
        
        //Determine highest score.
        if (player1Score > player2Score) {
            cout << "You will go first!" << endl;
            chooseColor();
        } else {
            cout << "Computer will go first and choose color." << endl;
            computerChooseColor();
        }
    }
}

/* *********************************************************************
 Function Name: chooseColor
 Purpose: Function for user to pick what color they want to be
 Parameters:none
 Return Value: none
 Local Variables:
 ss, the string stream to read in color
 color, the input for the user color
 upperColor, the upper version of color
 tmpColor = the character converted to string
 colorToSet, the color to set for the player
 computerColor, the color to set for computer
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round::chooseColor() {
    //Print who goes first
    stringstream ss;
    cout << endl;
    
    //Get color
    cout << "Choose your color (B or W): ";
    char color, upperColor;
    cin >> color;
    
    //Convert to upper
    upperColor = toupper(color);
    if (upperColor != 'B') {
        if (upperColor != 'W') {
            chooseColor();
            return;
        }
    }
    
    //Was using Chars initially, switched to Strings.
    //This converts my char to a string
    ss << upperColor;
    string tmpColor;
    ss >> tmpColor;
    
    //Set color based of letter
    string colorToSet, computerColor;
    if (upperColor == 'B') {
        colorToSet = "B";
        computerColor = "W";
    } else {
        colorToSet = "W";
        computerColor = "B";
    }
    
    //Init users
    user = new Human(colorToSet);
    computer = new Computer(computerColor);
    
    //Set the players
    setPlayers(user,computer);
    user->setTurn(true);
    
    cout << "You are " << user->getColor() << "." << endl;
    cout << "Computer is " << computer->getColor() << "." << endl << endl;
}

/* *********************************************************************
 Function Name: computerChooseColor
 Purpose: Function for the computer picking color.
 Parameters:none
 Return Value: none
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round::computerChooseColor() {
    user = new Human("B");
    computer = new Computer("W");
    
    setPlayers(user,computer);
    computer->setTurn(true);
}

/* *********************************************************************
 Function Name: provideMenu
 Purpose: Draws menu for the human and allows for selecting option
 Parameters:none
 Return Value: none
 Local Variables:
 choice, the input value for the menu
 validChoice, input validatino bool for input
 write, the writer to save the file data
 nextPlayer, the next player
 directionWord, the directoin in a string word
 
 row, the row for the suggestion move
 column, the column for the suggestin move
 d, the directoin for the suggestion move
 m, the movetype for the suggestionmove
 Algorithm:
 Switch choice and do that action based on choice
 Assistance Received: none
 ********************************************************************* */
void Round::provideMenu() {
    //Show computer menu if its turn
    if (computer->getIsTurn()) {
        computerMenu();
        return;
    }
    
    cout << "Choose an option below" << endl;
    cout << "1. Save Game" << endl;
    cout << "2. Make A Move" << endl;
    cout << "3. Suggest Move" << endl;
    cout << "4. Quit Game" << endl << endl;
    
    //Validate input
    int choice = 1;
    bool validChoice = false;
    while (!validChoice) {
        cout << "Your choice: ";
        cin >> choice;
        while(cin.fail()) {
            cout << "Your choice: ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> choice;
        }
        
        if (!cin.fail()) {
            if (choice == 1 || choice == 2 || choice == 3 || choice == 4) {
                validChoice = true;
            }
        }

    }
    
    //Variables for writing to file
    FileWriter write;
    string nextPlayer;
    string directionWord;
    
    switch (choice) {
        case 1:
            //Save the game to file
            (user->getIsTurn()) ? nextPlayer = "Human" : nextPlayer = "Computer";
            write.saveGame(getRound(), user->getScore(), user->getColor(), computer->getScore(), computer->getColor(), board, nextPlayer);
            break;
        case 2:
            //Move the player
            move();
            break;
        case 3:
            //Varaibales to store values in tuple
            int row, column;
            Direction d;
            MoveType m;
            
            //Call the Player:: player to get suggestoin
            tie(row, column, d, m) = user->Player::play();
            row++;
            column++;
            
            //Get the direction for the enum
            switch (d) {
                case NE:
                    directionWord = "northeast";
                    break;
                case NW:
                    directionWord = "northwest";
                    break;
                case SE:
                    directionWord = "southeast";
                    break;
                case SW:
                    directionWord = "southwest";
                    break;
                default:
                    break;
            }
            
            //Describe suggestion move
            switch (m) {
                case capture:
                    cout << "Move piece at (" << row << ", " << column << ") " << directionWord << " to capture opponents piece." << endl;
                    break;
                case block:
                    cout << "Move piece at (" << row << ", " << column << ") " << directionWord << " to block opponents piece." << endl;
                    break;
                case MoveType::advance:
                    cout << "Move piece at (" << row << ", " << column << ") " << directionWord << " to advance to computers home pieces." << endl;
                    break;
                default:
                    break;
            }
            
            //Show the move menu
            move();
            break;
        case 4:
            //End round
            endRound(true, "Human");
            break;
        default:
            //Recursive loop for invalid choice.
            cout << endl << "Invalid choice: " << choice << endl << endl;
            provideMenu();
            break;
    }
}

/* *********************************************************************
 Function Name: computerMenu
 Purpose: The menu displayed on computers turn
 Parameters:none
 Return Value: none
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round:: computerMenu() {
    int choice = 1;
    cout << "Choose an option below" << endl;
    cout << "1. Save Game" << endl;
    cout << "2. Computer Move" << endl;
    cout << "3. Quit Game" << endl << endl;
    
    //Validate input
    bool validChoice = false;
    while (!validChoice) {
        cout << "Your choice: ";
        cin >> choice;
        while(cin.fail()) {
            cout << "Your choice: ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> choice;
        }
        if (!cin.fail()) {
            if (choice == 1 || choice == 2 || choice == 3) {
                validChoice = true;
            }
        }
    }
    
    //Values for writing to file
    FileWriter write;
    string nextPlayer;
    switch (choice) {
        case 1:
            //Write to file
            (user->getIsTurn()) ? nextPlayer = "Human" : nextPlayer = "Computer";
            write.saveGame(getRound(), user->getScore(), user->getColor(), computer->getScore(), computer->getColor(), board, nextPlayer);
            break;
        case 2:
            //Move
            move();
            break;
        case 3:
            //End round
            endRound(true, "Computer");
            break;
        default:
            //Recursive loop
            cout << "Invalid choice: " << choice << endl << endl;
            computerMenu();
            break;
    }
}

/* *********************************************************************
 Function Name: move
 Purpose: The controller for the game and moves.  This function determines whose turn it is
 Calls the appropriate play function and updates/draws board. Responsible for checking for winner, ending the round
 and swapping turns.
 Parameters:none
 Return Value: none
 Local Variables:
 row, the row for the move
 column, the column for the move
 d, the directoin for the move
 doestMatterIgnoreThisSorry, a variable not used but is required to be passed into my tuple.
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round:: move() {
    int row, column;
    Direction d;
    MoveType doesntMatterIgnoreThisSorry;
    
    //Plays for the correct person
    if (user->getIsTurn()) {
        tie(row, column, d, doesntMatterIgnoreThisSorry) = user->play();
    } else {
        tie(row, column, d, doesntMatterIgnoreThisSorry) = computer->play();
    }
    
    //Update board
    board->movePiece(row, column, d);
    board->drawBoard();
    
    //Check for game over
    if (board->checkForWinner()) {
        if (user->getColor() == board->getWinnerPiece()) {
            cout << "You got all your pieces in the home points of the computer!" << endl << endl;
        } else {
            cout << "Dang... The computer got all his pieces in your home points. Better luck next round!" << endl;
        }
        endRound(false, "");
    } else{
        //If game is not over swap turns and provide menu
        swapTurns();
        provideMenu();
    }
}

/* *********************************************************************
 Function Name: swapTurns
 Purpose: Flips the turns of players
 Parameters:none
 Return Value: none
 Local Variables:none
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round:: swapTurns() {
    user->setTurn(!user->getIsTurn());
    computer->setTurn(!computer->getIsTurn());
}

/* *********************************************************************
 Function Name: endRound:didQuit:quitter
 Purpose: TO end the round wether it be quitting or game over
 Parameters:
 didQuit, bool used to determine if the player quit or the game was won
 quitter, optional value to see which player quit
 Return Value: none
 Local Variables:
 userScore, the score of user
 computerScore, the score of computer
 validInput, boolean used for valid input validatin
 Algorithm:none
 Assistance Received: none
 ********************************************************************* */
void Round::endRound(bool didQuit, string quitter) {
    
    cout << endl << "Round over!" << endl;
    
    //The score of the players
    int userScore = board->getScore(user->getColor());
    int computerScore = board->getScore(computer->getColor());
    
    //Subtract points from the quitter
    if (didQuit) {
        if (quitter == "Human") {
            userScore = userScore - 5;
        } else {
            computerScore = computerScore - 5;
        }
    }
    
    cout << endl << "You scored: " << userScore << endl;
    cout << "Computer scored: " << computerScore << endl << endl;
    
    //Award points for round
    if (userScore > computerScore) {
        int score = userScore - computerScore;
        cout << "You are awarded: " << score << " points" << endl;
        user->setScore(user->getScore() + score);
    } else if(computerScore > userScore) {
        int score = computerScore - userScore;
        cout << "Computer was rewarded: " << score << " points" << endl;
        computer->setScore(computer->getScore() + score);
    } else {
        cout << "No one was rewarded any points." << endl;
    }
    
    cout << endl << "Tournament scores" << endl;
    cout << "You: " << user->getScore() << endl;
    cout << "Computer: " << computer->getScore() << endl << endl;
    
    //Valid inputs
    bool validInput = false;
    while (!validInput) {
        char input, upperInput;
        cout << "Would you like to play another round? (Y / N): ";
        cin >> input;
        
        upperInput = toupper(input);
        if (upperInput == 'Y' || upperInput == 'N') {
            if (upperInput == 'Y') {
                //Set new round
                setRound(getRound() + 1);
                
                //Get winner
                string winner;
                if (userScore >= computerScore) {
                    winner = "Human";
                } else {
                    winner = "Computer";
                }
                
                //Start next round, set up board and provide menu
                nextRound(winner);
                setUpBoard();
                provideMenu();
            } else {
                //Game over, determine and output winner
                cout << endl;
                if (user->getScore() > computer->getScore()) {
                    cout << "Congratulations you beat the computer and won the Kono tournament!" << endl << endl;
                } else if (user->getScore() < computer->getScore()) {
                    cout << "You got beat by the computer and lost the Kono tournament. :(" << endl << endl;
                } else {
                    cout << "It's a draw! You and the computer tied." << endl << endl;
                }
                
                cout << "Final Scores" << endl;
                cout << "You: " << user->getScore() << endl;
                cout << "Computer: " << computer->getScore() << endl << endl;
                
            }
            validInput = true;
        }
    }
}

