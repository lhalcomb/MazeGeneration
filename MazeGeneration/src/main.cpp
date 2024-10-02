#include <iostream>
#include <vector>
#include <raylib.h>
#include <random>
#include "../Headers/Cell.hpp"


//Constant 
#define DIMENSION 800
#define ROWS (20)
#define COLS (20)

//Source file for Maze Generator


using namespace std;

vector<vector<Cell>> createMazeGrid(){
    vector<vector<Cell>> grid;
    for(int i = 0; i < ROWS; i++){
        vector<Cell> row;
        for(int j = 0; j < COLS; j++){
            row.push_back(Cell(j,i));
        }
        grid.push_back(row);
    }

    return grid;
}

void renderMazeGrid(vector<vector<Cell>> &grid, int cellSize){
    for (auto& row: grid){
        for(auto& cell: row){
            cell.render(cellSize);
        }
    }
}

int main(){


    InitWindow(DIMENSION, DIMENSION, "Maze Generator");
    SetTargetFPS(60);

    

    vector<vector<Cell>> grid = createMazeGrid(); //The grid of cell objects
    Cell& current = grid[0][0];
    current.visit();
    

    Cell* next = current.checkNeighbors(grid, current.getRow(), current.getCol()); 

    while (!WindowShouldClose()){
        
       
        if (next != nullptr){
            next->visit();
            current = *next; 
        }
        next = current.checkNeighbors(grid, current.getRow(), current.getCol());

        BeginDrawing();
        ClearBackground(RAYWHITE);
        renderMazeGrid(grid, 40); //Render those cell objects here 

        EndDrawing();
    }


    CloseWindow();

}