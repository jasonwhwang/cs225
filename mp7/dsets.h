/**
 * @file dsets.h
 * DisjointSets data structure.
 * @date Spring 2017
 */

#ifndef DSETS_H
#define DSETS_H

#include <vector>
using namespace std;

class DisjointSets
{
  public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int getSize();
  private:
    vector<int> sets;
};

#endif
