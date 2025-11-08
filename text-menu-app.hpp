#ifndef TEXT_MENU_APP_HPP
#define TEXT_MENU_APP_HPP

#include "board.hpp"
#include <string>
#include <sstream>



class TextMenuApp {
private:
    Board board;
    std::string prompt;
    bool gameOver;

    void updatePrompt(const std::string &message = "");

public:
    TextMenuApp();
    void run();

    bool load(const std::string &fileName);
    std::string getPrompt() const;
    bool gameIsOver() const;
    bool move(char action, int r, int c);
};

#endif
