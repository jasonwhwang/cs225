/**
 * @file dsets.cpp
 * Implmentation of DisjointSets class.
 */

#include "dsets.h"

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
