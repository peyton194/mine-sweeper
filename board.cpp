#include "board.hpp"
#include "cell.hpp"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

Board::Board() : rows(0), columns(0), field(nullptr) {}

Board::~Board() {
    if (field) {
        for (int i = 0; i < rows; ++i)
            delete[] field[i];
        delete[] field;
    }
}

bool Board::load(const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) return false;

   
    string line;
    rows = 0;
    columns = 0;
    while (getline(file, line)) {
        if (rows == 0) columns = line.size();
        rows++;
    }

    
    field = new Cell*[rows];
    for (int i = 0; i < rows; ++i)
        field[i] = new Cell[columns];

 
    file.clear();
    file.seekg(0, ios::beg);

    
    int r = 0;
    while (getline(file, line)) {
        for (int c = 0; c < columns; ++c)
            field[r][c] = Cell(line[c] == '*');
        r++;
    }
    file.close();

  
   for(int r = 0; r < rows; ++r){
    for(int c = 0; c < columns; ++c){
        if(!field[r][c].hasMine()){
            int count = 0;
            for(int i = -1; i <= 1; ++i){
                for(int j = -1; j <= 1; ++j){
                    int neighborRow = r + i;
                    int neighborCol = c + j; 

                    if (neighborRow>= 0 && neighborRow < rows && neighborCol >= 0 && neighborCol < columns){
                        if(field[neighborRow][neighborCol].hasMine()) ++count;
                    }
                }
            }
            field[r][c].setAdjacentMineCount(count);
        }
    }
   }

    return true;
}
void Board::revealAllMines() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (field[r][c].hasMine()) {
                field[r][c].setCleared(true);
            }
        }
    }
}
Cell& Board::getCell(int r, int c) {
    return field[r][c];
}
bool Board::click(int r, int c){
    if(r < 0 || r >= rows || c < 0 || c >= columns)
        return false;

    if (!field[r][c].click()) 
        return false; 

    if (field[r][c].hasMine()){
        field[r][c].setCleared(true);
        return true;
    }

    if (field[r][c].getAdjacentMineCount() > 0)
        return true;

    
    bool** visited = new bool*[rows];
    for (int i = 0; i < rows; ++i)
        visited[i] = new bool[columns]();

    expandClear(r, c, visited);

    for (int i = 0; i < rows; ++i)
        delete[] visited[i];
    delete[] visited;

    return true;
}

void Board::expandClear(int r, int c, bool** visited){
    if (r < 0 || r >= rows || c < 0 || c >= columns)
        return;

    if (visited[r][c])
        return;

    visited[r][c] = true;

    if (field[r][c].isFlagged() || field[r][c].hasMine())
        return;
    
    field[r][c].setCleared(true);

    if (field[r][c].getAdjacentMineCount() > 0)
        return;

    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            expandClear(r + dr, c + dc, visited);
        }
    }
}

bool Board::flag(int r, int c) {
    
    if (r < 0 || r >= rows || c < 0 || c >= columns) {
        return false;
    }
    field[r][c].toggleFlag();

    return true;
}

int Board::getRows(){
    return rows;
}

int Board::getColumns(){
    return columns;
}
 

string Board::str() const{
    stringstream result;
    result << "      ";
    for (int c = 0; c < columns; ++c) {
        result << c;
        if (c < columns - 1) result << "   ";
        else result << " ";
    }
    result << "\n";

    for (int r = 0; r < rows; ++r) {
        result << "    +";
        for (int c = 0; c < columns; ++c) {
            result << "---+";
        }
        result << "\n";
        result << "  " << r << " |";
        for (int c = 0; c < columns; ++c) {
            const Cell &cell = field[r][c];
            string cellDisplay;

            if (cell.isFlagged()) {
                cellDisplay = Cell::FLAG;
            } else if (cell.isCleared()) {
                if (cell.hasMine()) {
                    cellDisplay = Cell::MINE;
                } else if (cell.getAdjacentMineCount() == 0) {
                    cellDisplay = Cell::NO_ADJACENT_MINES; 
                } else {
                    cellDisplay = to_string(cell.getAdjacentMineCount());
                }
            } else {
                cellDisplay = " ";
            }

            result << " " << cellDisplay << " |";
        }
        result << "\n";
    }

    result << "    +";
    for (int c = 0; c < columns; ++c) {
        result << "---+";
    }
    result << "\n";

    return result.str();
}

