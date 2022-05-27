#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <thread>
using std::vector;
using BoardType = vector<vector<int>>; //Setting up a using for the boards type of vector<vector<int>> for readability


BoardType board = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0},
    {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
};

int numRows = 10;
int numCols = 20;

int getNeighbor(int row, int col, BoardType& board) {
    return board.at((row + numRows) % numRows).at((col + numCols) % numCols);//modulus to get wrapping around edges
}

void showBoard(BoardType board) {
    for (const vector<int>& row : board)
    {
        std::cout << "|";
        for (int cell : row)
        {
            std::cout << (cell ? "*" : "."); //Display * for cells of value 1,   for cells of value 0;
        }
        std::cout << "|\n";
    }
}

int lifeCheck(BoardType& board, int row, int col) {
    int count = 0;
    std::vector<int> deltas{ -1, 0, 1 }; //Adjacency check mask
    for (int dCol : deltas) {
        for (int dRow : deltas) {
            if (dRow || dCol) {
                count += board.at((row + dRow + numRows) % numRows).at((col + dCol + numCols) % numCols); //increment count by number of adjacent live cells.
            }
        }
    }

    bool isBirthed = !board.at(row).at(col) && count == 3;
    bool isSurvived = board.at(row).at(col) && (count == 2 || count == 3);
    return isBirthed || isSurvived; //returns true if either are fulfilled.
}

void updateBoard(BoardType& board) { //Runs a lifecheck on the whole board, operating on a local copy of the board so it all goes through at the same time.
    BoardType localBoard = board;
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            board.at(row).at(col) = lifeCheck(localBoard, row, col);
        }
    }
}

int main() {
    int year = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        system("cls");
        std::cout << "Year " << year << ":\n";
        showBoard(board);
        updateBoard(board);
        year++;
    }
}