/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include "kdtree.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    vector<Point<3>> pixels;
    map<Point<3>, TileImage> colorMap;
    KDTree<3> tree(pixels);
    int rows = theSource.getRows();
    int cols = theSource.getColumns();
    MosaicCanvas * canvas = new MosaicCanvas(rows, cols);

    for(size_t i = 0; i < theTiles.size(); i++) {
        RGBAPixel pixel = theTiles[i].getAverageColor();
        Point<3> pixVals(pixel.red, pixel.green, pixel.blue);
        colorMap[pixVals] = theTiles[i];
        pixels.push_back(pixVals);
    }

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            RGBAPixel color = theSource.getRegionColor(i, j);
            Point<3> pt(color.red, color.green, color.blue);
            Point<3> nearest = tree.findNearestNeighbor(pt);
            TileImage tile = colorMap[nearest];
            canvas->setTile(i, j, tile);
        }
    }
    
    return canvas;
}

