/**
 * @file main.cpp
 * A simple C++ program that manipulates an image by rotating it 180 degrees.
 */
#include <algorithm>
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

/**
 * This function will rotate the image 180 degrees pixel by pixel
 *
 * @param firstImage    The image that will be transformed
 * @param secondImage    The image that will be copied from
 *
 * @return    The image that was rotated 180 degrees
 */
PNG rotatePNG(PNG firstImage, PNG secondImage)
{
    for (size_t yi = 0; yi < firstImage.height(); yi++) {
        for (size_t xi = 0; xi < firstImage.width(); xi++) {
	  *firstImage(xi, yi) = *secondImage(firstImage.width()-xi-1, firstImage.height()-yi-1);
        }
    }
    return firstImage;
}

/**
 * This is the main function that executes the rotatePNG function on the image
 *
 * @return An integer indicating whether execution was successful.
 */
int main()
{
    // Open a new PNG image.
    PNG image("in.png");
    // Rotate Image 180 Degrees.
    image = rotatePNG(image, image);

    // Save the modified image to a file called out.png, overwriting the file
    // if it already exists.
    image.writeToFile("out.png");

    return 0;
}
