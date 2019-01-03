/**
 * @file dsets.cpp
 * Implmentation of DisjointSets class.
 */

#include "dsets.h"

int DisjointSets::getSize()
{
    int ct = 0;
    for(size_t i = 0; i < sets.size(); i++) {
        if(sets[i] == -1) {
            ct = ct + 1;
        }
    }
    return ct;
}

void DisjointSets::addelements(int num)
{
    for(int i = 0; i < num; i++) {
        sets.push_back(-1);
    }
}

int DisjointSets::find(int elem)
{
    if(sets[elem] < 0) return elem;
    return sets[elem] = find(sets[elem]);
}

void DisjointSets::setunion(int a, int b)
{
    a = find(a);
    b = find(b);
    int size = sets[a] + sets[b];
    if(sets[a] <= sets[b]) {
        sets[b] = a;
        sets[a] = size;
    } else {
        sets[a] = b;
        sets[b] = size;
    }
}
