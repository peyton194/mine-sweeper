#include "cell.hpp"
#include <string>

using namespace std;

const std::string Cell::MINE = "*";
const std::string Cell::FLAG = "\u2691";
const std::string Cell::NO_ADJACENT_MINES = "\u25A2";
const std::string Cell::UNKNOWN = " ";

Cell::Cell(): mine(false), flagged(false), cleared(false), adjacentMineCount(0){}
Cell::Cell(bool hasMine)
    : mine(hasMine), flagged(false), cleared(false) , adjacentMineCount(0){}

bool Cell::hasMine()const{
    return mine;
}

void Cell::toggleFlag(){
     if (!cleared) {
        flagged = !flagged;
    }
}

bool Cell::click(){
    if(flagged || cleared){
        return false;
    }
    cleared = true;
    return true;
}
bool Cell::isCleared()const {return cleared;}
bool Cell::isFlagged()const {return flagged;}
void Cell::setCleared(bool state){
    cleared = state;
}

int Cell::getAdjacentMineCount()const{
    return adjacentMineCount;
}

void Cell::setAdjacentMineCount(int count){
    adjacentMineCount = count;
}

string Cell::str()const{
     if (!cleared) {                           
        if (flagged) return FLAG;            
        else return UNKNOWN;                  
    } else {                                  
        if (mine) return MINE;                
        if (adjacentMineCount == 0) return NO_ADJACENT_MINES; 
        return to_string(adjacentMineCount);             
    }
}