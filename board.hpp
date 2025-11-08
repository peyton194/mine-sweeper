#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include "cell.hpp"

class Board {
private:
    int rows;
    int columns;
    Cell **field;
    void expandClear(int r, int c, bool** visited);
    void clearRegion(int r, int c, bool **visited);

public:
    Board();
    ~Board();
    bool flag(int r, int c);
    bool load(const std::string &fileName);
    bool click(int r, int c);
    std::string str()const;
    int getRows();
    int getColumns();
    Cell& getCell(int r, int c);
    void revealAllMines();

};

#endif