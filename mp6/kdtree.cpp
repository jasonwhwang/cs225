/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if(first[curDim] == second[curDim]) {
        return first < second;
    }
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    int pSum = 0, cSum = 0;
    for(int i = 0; i < Dim; i++) {
        pSum = pSum + (potential[i]-target[i]) * (potential[i]-target[i]);
        cSum = cSum + (currentBest[i]-target[i]) * (currentBest[i]-target[i]);
    }
    return pSum < cSum;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    points = newPoints;
    if(!newPoints.empty()) {
        KDTree(newPoints, 0, newPoints.size()-1, 0);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints, int lowIndex, int highIndex, int d)
{
    if(highIndex < lowIndex || lowIndex > highIndex || lowIndex < 0 || highIndex > (int)points.size()) { return; }
    points[(highIndex+lowIndex)/2] = getPoint(newPoints, (highIndex+lowIndex)/2, d);
    KDTree(newPoints, lowIndex, (highIndex+lowIndex)/2-1, (d+1)%Dim);
    KDTree(newPoints, (highIndex+lowIndex)/2+1, highIndex, (d+1)%Dim);
}

template <int Dim>
Point<Dim> KDTree<Dim>::getPoint(const vector<Point<Dim>>& newPoints, int index, int d)
{
    vector<Point<Dim>> newPts = newPoints;
    sort(newPts, d);
    return newPts[index];
}

template <int Dim>
void KDTree<Dim>::sort(vector<Point<Dim>>& newPts, int d)
{
    size_t j = 0;
    Point<Dim> temp;
    for(size_t i = 0; i < newPts.size(); i++) {
        temp = newPts[i];
        j = i;
        while(j > 0 && newPts[j-1][d] > temp[d]) {
            newPts[j] = newPts[j-1];
            j--;
        }
        newPts[j] = temp;
    }
}



template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    return findNearestNeighbor(query, points[(points.size()-1)/2], 0, points.size()-1, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, const Point<Dim>& currentBest, int lowIndex, int highIndex, int d) const
{
    if(lowIndex == highIndex) {
        if(shouldReplace(query, currentBest, points[lowIndex])) {
            return points[lowIndex];
        }
        return currentBest;
    }

    Point<Dim> potential = currentBest;
    bool inLeft = true;
    int midIndex = (lowIndex+highIndex)/2;
    
    if(smallerDimVal(query, points[midIndex], d) && lowIndex != midIndex) {
        potential = findNearestNeighbor(query, currentBest, lowIndex, midIndex-1, (d+1)%Dim);
    } else if(smallerDimVal(points[midIndex], query, d) && highIndex != midIndex) {
        potential = findNearestNeighbor(query, currentBest, midIndex+1, highIndex, (d+1)%Dim);
        inLeft = false;
    }

    if(shouldReplace(query, potential, points[midIndex])) {
        potential = points[midIndex];
    }

    int dis = 0;
    for(int i = 0; i < Dim; i++) {
        dis = dis + (query[i]-potential[i]) * (query[i]-potential[i]);
    }

    if( (points[midIndex][d]-query[d]) * (points[midIndex][d]-query[d]) <= dis) {
        if(!inLeft && lowIndex != midIndex) {
            potential = findNearestNeighbor(query, potential, lowIndex, midIndex-1, (d+1)%Dim);
        } else if(inLeft && highIndex != midIndex) {
            potential = findNearestNeighbor(query, potential, midIndex+1, highIndex, (d+1)%Dim);
        }
    }

    return potential;
}

