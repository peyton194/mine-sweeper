#include "text-menu-app.hpp"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void TextMenuApp::run() {
    string fileName;
    bool loaded = false;

    while (!loaded) {
        cout << prompt;
        getline(cin, fileName);
        loaded = load(fileName);
    }

    while (!gameOver) {
        cout << prompt;
        string line;
        getline(cin, line);

        if (line.length() < 5) { 
            prompt = "Invalid move. Please enter your next move: ";
            continue;
        }

        char action;
        int r, c;
        istringstream iss(line);
        iss >> action >> r >> c;

        if (!move(action, r, c)) {
            continue; 
        }

        
        if (gameOver) break;
    }

    cout << prompt << endl;
}

TextMenuApp::TextMenuApp() : gameOver(false) {
    prompt = "Please enter a file name with the minefield information: ";
}

void TextMenuApp::updatePrompt(const std::string &message) {
    if (!message.empty()) {
        prompt = message;
    } else {
        prompt = board.str() +
            "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";
    }
}

bool TextMenuApp::load(const std::string &fileName) {
    if (!board.load(fileName)) {
        prompt = "Please enter a file name with the minefield information: ";
        return false;
    }
    gameOver = false;
    updatePrompt();
    return true;
}

std::string TextMenuApp::getPrompt() const {
    return prompt;
}

bool TextMenuApp::gameIsOver() const {
    return gameOver;
}

bool TextMenuApp::move(char action, int r, int c) {
    if (action == 'C') action = 'c';
    if (action == 'F') action = 'f';

    if ((action != 'c' && action != 'f') ||
        r < 0 || r >= board.getRows() ||
        c < 0 || c >= board.getColumns()) {
        prompt = "Invalid move. Please enter your next move: ";
        return false;
    }

    if (action == 'c') {
        if (!board.click(r, c)) { 
            prompt = "Invalid move. Please enter your next move: ";
            return false;
        }

        if (board.getCell(r, c).hasMine()) {
            board.revealAllMines(); 
            prompt = board.str() + "Game Over!";
            gameOver = true;
            return true;
        }

        bool won = true;
        for (int i = 0; i < board.getRows(); ++i) {
            for (int j = 0; j < board.getColumns(); ++j) {
                Cell &cell = board.getCell(i, j);
                if (!cell.hasMine() && !cell.isCleared()) {
                    won = false;
                    break;
                }
            }
            if (!won) break;
        }

        if (won) {
            board.revealAllMines(); 
            prompt = board.str() + "You Win!";
            gameOver = true;
            return true;
        }

        updatePrompt();
        return true;

    } else if (action == 'f') {
        if (!board.flag(r, c)) {
            prompt = "Invalid move. Please enter your next move: ";
            return false;
        }
        prompt = board.str() +
                 "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";
        return true;
    }

    return false; 
}
