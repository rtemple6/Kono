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

Round::Round(Human * u, Computer * c) {
    this->board = new Board();
    this->user = u;
    this->computer = c;
}

void Round::setRound(int round) {
    this->round = round;
}

int Round::getRound() {
    return this->round;
}

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

void Round:: loadBoard(int size, string **data) {
    this->board->setBoard(size, data);
    this->user->setBoard(board);
    this->computer->setBoard(board);
    this->board->drawBoard();
}

void Round::rollDice(bool fromConfig) {
    cout << endl << "Round " << getRound() << endl << endl;
    srand(time(0));
    FileReader r;
    if (fromConfig) {
        r.setFileName("Dice.txt");
        string winner = r.loadDice();
        (winner == "Human") ? user->setTurn(true) : computer->setTurn(true);
    } else {
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
        (player1Score > player2Score) ? user->setTurn(true) : computer->setTurn(true);
    }
    (user->getIsTurn()) ? cout << "You will go first!" << endl << endl : cout << "Computer will go first." << endl << endl;
    chooseColor();
}

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

void Round::chooseColor() {
    //Print who goes first
    stringstream ss;
    cout << endl;
    if (user->getIsTurn()) {
        cout << "Choose your color (B or W): ";
        char color, upperColor;
        cin >> color;
        
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
        
        user->setColor(tmpColor);
        (upperColor == 'B') ? computer->setColor("W") : computer->setColor("B");
    } else {
        computer->setColor("W");
        user->setColor("B");
    }
    
    cout << "You are " << user->getColor() << "." << endl;
    cout << "Computer is " << computer->getColor() << "." << endl << endl;
}


void Round::provideMenu() {
    //
    if (computer->getIsTurn()) {
        computerMenu();
        return;
    }
    
    cout << "Choose an option below" << endl;
    cout << "1. Save Game" << endl;
    cout << "2. Make A Move" << endl;
    cout << "3. Suggest Move" << endl;
    cout << "4. Quit Game" << endl << endl;
    
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
    
    FileWriter write;
    string nextPlayer;
    switch (choice) {
        case 1:
            (user->getIsTurn()) ? nextPlayer = "Human" : nextPlayer = "Computer";
            write.saveGame(getRound(), user->getScore(), user->getColor(), computer->getScore(), computer->getColor(), board, nextPlayer);
            break;
        case 2:
            move();
            break;
        case 3:
            cout << "Suggesting move..." << endl;
            break;
        case 4:
            endRound(true, "Human");
            break;
        default:
            cout << "Invalid choice: " << choice << endl << endl;
            provideMenu();
            break;
    }
}

void Round:: computerMenu() {
    int choice = 1;
    cout << "Choose an option below" << endl;
    cout << "1. Save Game" << endl;
    cout << "2. Computer Move" << endl;
    cout << "3. Quit Game" << endl << endl;
    
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
    
    FileWriter write;
    string nextPlayer;
    switch (choice) {
        case 1:
            (user->getIsTurn()) ? nextPlayer = "Human" : nextPlayer = "Computer";
            write.saveGame(getRound(), user->getScore(), user->getColor(), computer->getScore(), computer->getColor(), board, nextPlayer);
            break;
        case 2:
            move();
            break;
        case 3:
            endRound(true, "Computer");
            break;
        default:
            cout << "Invalid choice: " << choice << endl << endl;
            computerMenu();
            break;
    }
}

void Round:: move() {
    if (user->getIsTurn()) {
        user->play();
    } else {
        computer->play();
    }
    
    if (board->checkForWinner()) {
        if (user->getColor() == board->getWinnerPiece()) {
            cout << "You got all your pieces in the home points of the computer!" << endl << endl;
        } else {
            cout << "Dang... The computer got all his pieces in your home points. Better luck next round!" << endl;
        }
        endRound(false, "");
    } else{
        swapTurns();
        provideMenu();
    }
}

void Round:: swapTurns() {
    user->setTurn(!user->getIsTurn());
    computer->setTurn(!computer->getIsTurn());
}

void Round::endRound(bool didQuit, string quitter) {
    
    cout << endl << "Round over!" << endl;
    int userScore = board->getScore(user->getColor());
    int computerScore = board->getScore(computer->getColor());
    
    if (didQuit) {
        if (quitter == "Human") {
            userScore = userScore - 5;
        } else {
            computerScore = computerScore - 5;
        }
    }
    
    cout << endl << "You scored: " << userScore << endl;
    cout << "Computer scored: " << computerScore << endl << endl;
    
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
    
    bool validInput = false;
    
    while (!validInput) {
        char input, upperInput;
        cout << "Would you like to play another round? (Y / N): ";
        cin >> input;
        
        upperInput = toupper(input);
        if (upperInput == 'Y' || upperInput == 'N') {
            if (upperInput == 'Y') {
                setRound(getRound() + 1);
                string winner;
                if (userScore >= computerScore) {
                    winner = "Human";
                } else {
                    winner = "Computer";
                }
                nextRound(winner);
                setUpBoard();
                provideMenu();
            } else {
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

