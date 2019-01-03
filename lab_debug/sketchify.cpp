#include <iostream>
#include <cstdlib>
#include "png.h"
using namespace std;

//
// sets up the output image
PNG* setupOutput(int w, int h)
{
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
RGBAPixel* myFavoriteColor(int intensity)
{
    RGBAPixel color;
    color.red   = 0;
    color.green = intensity / 2;
    color.blue  = intensity;
    return &color;
}

void sketchify()
{
    // Load in.png
    //cout << "Checkpoint 1" << endl;
    
    PNG* original = new PNG();
    original->readFromFile("in.png");
    int width = original->width();
    int height = original->height();
    //cout << width << endl;
    //cout << height << endl;

    // Create out.png
    PNG* output;
    output = setupOutput(width, height);

    // Load our favorite color to color the outline
    RGBAPixel* myPixel = myFavoriteColor(192);
    //int rd = myPixel->red, gn = myPixel->green, be = myPixel->blue;
    //cout << rd << endl;
    //cout << gn << endl;
    //cout << be << endl;

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (int y = 1; y < height; y++) {
        for (int x = 1; x < width; x++) {
            // Calculate the pixel difference
            //cout << "Checkpoint 3" << endl;
            RGBAPixel* prev = (*original)(x - 1, y - 1);
            RGBAPixel* curr = (*original)(x, y);
            int diff = abs(curr->red - prev->red)
                       + abs(curr->green - prev->green)
                       + abs(curr->blue - prev->blue);

            // cout << "Checkpoint 4" << endl;

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            RGBAPixel* currOutPixel = (*output)(x, y);
            if (diff > 100){
                    *currOutPixel = *myPixel;
                }
                //currOutPixel->red = myPixel->red;
                //currOutPixel->green = myPixel->green;
                //currOutPixel->blue = myPixel->blue;
                //int rdc = currOutPixel->red, gnc = currOutPixel->green, bec = currOutPixel->blue;
                //cout << rdc << endl;
                //cout << gnc << endl;
                //cout << bec << endl;
                // cout << "Checkpoint 5" << endl;
        }
    }

    // Save the output file
    output->writeToFile("out.png");

    //cout << "Checkpoint 6" << endl;
    // Clean up memory
    //delete myPixel;
    delete output;
    delete original;
}
