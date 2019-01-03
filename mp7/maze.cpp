/**
 * @file maze.cpp
 * Implmentation of SquareMaze class.
 */

#include "maze.h"

SquareMaze::SquareMaze()
{
}

void SquareMaze::makeMaze(int width, int height)
{
    this->width = width;
    this->height = height;
    size = width*height;
    cells.addelements(size);
    downWalls = vector<bool>(size, true);
    rightWalls = vector<bool>(size, true);
    srand(time(NULL));
    
    while(cells.getSize() > 1) {
        int rowIdx = rand() % (height-1);
        int colIdx = rand() % (width-1);
        int n = rand() % 2;

        if(downWalls[rowIdx*width + colIdx] == true && n && 
           cells.find(rowIdx*width + colIdx) != cells.find((rowIdx+1)*width + colIdx)) {
            cells.setunion(rowIdx*width + colIdx, ((rowIdx+1)*width + colIdx));
            downWalls[rowIdx*width + colIdx] = false;
        }

        if(rightWalls[rowIdx*width + colIdx] == true && !n &&
           cells.find(rowIdx*width + colIdx) != cells.find(rowIdx*width + colIdx+1)) {
            cells.setunion(rowIdx*width + colIdx, rowIdx*width + colIdx+1);
            rightWalls[rowIdx*width + colIdx] = false;
        }
        cout << cells.getSize() << endl;
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
    if(dir == 0 && x != width-1) {
        return rightWalls[width*y + x] == false;
    }
    if(dir == 1 && y != height-1) {
        return downWalls[width*y + x] == false;
    }
    if(dir == 2 && x != 0) {
        return rightWalls[width*y + x-1] == false;
    }
    if(dir == 3 && y != 0) {
        return downWalls[width*(y-1) + x] == false;
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    if(dir == 0 && x != width-1) {
        rightWalls[x+y+width] = exists? true:false;
    }
    if(dir == 1 && y != height-1) {
        downWalls[x+y+width] = exists? true:false;
    }
}

vector<int> SquareMaze::solveMaze()
{
    return vector<int>();
}

PNG* SquareMaze::drawMaze() const
{
    PNG* img =  new PNG(width*10+1, height*10+1);

    // Draw Top Bar & Left Bar
    for(int i = 0; i < width*10+1; i++) {
        (*img)(i,0)->red = (*img)(i,0)->green = (*img)(i,0)->blue = 0;
    }
    for(int i = 0; i < height*10+1; i++) {
        (*img)(0,i)->red = (*img)(0,i)->green = (*img)(0,i)->blue = 0;
    }

    // Draw Maze based on downWalls & rightWalls bool vectors
    int x, y;
    for(int i = 0; i < size; i++) {
        x = i % width;
        y = i / width;
        if(downWalls[i]) {
            for(int j = 0; j <= 10; j++) {
                (*img)(x*10+j, (y+1)*10)->red = (*img)(x*10+j, (y+1)*10)->green = (*img)(x*10+j, (y+1)*10)->blue = 0;
            }
        }
        if(rightWalls[i]) {
            for(int j = 0; j <= 10; j++) {
                (*img)((x+1)*10, y*10+j)->red = (*img)((x+1)*10, y*10+j)->green = (*img)((x+1)*10, y*10+j)->blue = 0;
            }
        }
    }

    return img;
}

PNG* SquareMaze::drawMazeWithSolution()
{
    return nullptr;
}
