#include <raylib.h> 
#include "../Headers/Cell.hpp"
#include <random>

//Variable Declarations for this file that stay constant
#define CELLSIZE 20

using namespace std; 

Cell::Cell(int row, int column): row(row), column(column), visited(false){
    walls = {true, true, true, true}; 
}

Cell::~Cell(){}

int Cell::getRow() {return row; }

int Cell::getCol() {return column; }

bool Cell::isVisited() {return visited; }

void Cell::visit() {visited = true;}

void Cell::render(int cellSize){
    int rowPos = row * cellSize;
    int colPos = column * cellSize;

    if (walls[0]){ //top
        DrawLine(rowPos, colPos, rowPos + cellSize, colPos, BLACK);
    }
     if (walls[1]){ //right
        DrawLine(rowPos + cellSize, colPos, rowPos + cellSize, colPos + cellSize, BLACK);
    }
    if (walls[2]){ //bottom
        DrawLine(rowPos, colPos + cellSize, rowPos + cellSize, colPos + cellSize, BLACK);
    }
    if (walls[3]){ //left
        DrawLine(rowPos, colPos, rowPos, colPos + cellSize, BLACK);
    }

    if (visited){
        highlightCell(cellSize);
    }

}


Cell* Cell::checkNeighbors(vector<vector<Cell>>& grid, int row, int col){
    vector<Cell*> unvisitedNeighbors; // Initial empty array of unvistedNeighbors, gonna populate

    int numRows = grid.size(); // size of the number of rows i.e. 20 
    int numCols = grid[0].size(); // same from above but for columns

    //nullptr for the neighboring Cell object on the top, right, bottom, left
    Cell* topCell = nullptr; 
    Cell* rightCell = nullptr;
    Cell* bottomCell = nullptr;
    Cell* leftCell = nullptr;

    /*
    This logic here checks for edge cases so our 
    cell neighbor checking doesn't go out of bounds. 
    */

    if (row - 1 >= 0){
        topCell = &grid[row - 1][col];
    }
    if (col + 1 < numCols){
        rightCell = &grid[row][col + 1];
    }
    if (row + 1 < numRows){
        bottomCell = &grid[row + 1][col];
    }
    if (col - 1 >= 0){
        leftCell = &grid[row][col - 1];
    }

    /*
    Now we check if the neighboring cells are visited or not.
    */

    if (topCell != nullptr && !topCell->isVisited()){
        unvisitedNeighbors.push_back(topCell);
    }
    if (rightCell != nullptr && !rightCell->isVisited()){
        unvisitedNeighbors.push_back(rightCell);
    }
    if (bottomCell != nullptr && !bottomCell->isVisited()){
        unvisitedNeighbors.push_back(bottomCell);
    }
    if (leftCell != nullptr && !leftCell->isVisited()){
        unvisitedNeighbors.push_back(leftCell);
    }

    // If there are unvisited neighbors, return one at random
    if (!unvisitedNeighbors.empty()) {
        random_device rd;  // Seed for random number generation
        mt19937 generator(rd()); 
        uniform_int_distribution<int> distribution(0, unvisitedNeighbors.size() - 1);

        // Select a random index from the unvisited neighbors
        int randomIndex = distribution(generator);

        return unvisitedNeighbors[randomIndex];  // Return the randomly selected neighbor
    }

    return nullptr;

}

void removeWall(){
    ;
}

void Cell::highlightCell(int cellSize){
    int rowPos = row * cellSize;     // Calculate the top-left corner of the cell
    int colPos = column * cellSize;  // Same for the column

    DrawRectangle(rowPos + 1, colPos + 1, cellSize - 2, cellSize - 2, YELLOW);
}

