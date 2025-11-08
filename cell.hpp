#ifndef CELL_HPP
#define CELL_HPP
#include <string>

class Cell{
    public:
        static const std::string MINE;
        static const std::string FLAG;
        static const std::string NO_ADJACENT_MINES;
        static const std::string UNKNOWN;
        Cell();
        Cell(bool hasMine);
        bool hasMine() const;
        void toggleFlag();
        bool click();
        bool isCleared() const;
        bool isFlagged() const;
        void setCleared(bool state);
        int getAdjacentMineCount()const;
        void setAdjacentMineCount(int count);
        std::string str() const;
    private:
        bool mine;
        bool flagged;
        bool cleared;
        int adjacentMineCount;
    
    };

    #endif 