/**
 * @file maze.h
 * SquareMaze class.
 * @date Spring 2017
 */

#ifndef MAZE_H
#define MAZE_H

#include "png.h"
#include "dsets.h"

using namespace std;

class SquareMaze
{
  public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
  private:
    int width, height, size;
    DisjointSets cells;
    vector<bool> downWalls, rightWalls;
};

#endif
