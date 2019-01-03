#include "rgbapixel.h"

/**
 * This file includes the constructors for the RGBAPixel Class
 */

RGBAPixel::RGBAPixel(): red(255), green(255), blue(255), alpha(255)
{
    // do nothing
}

RGBAPixel::RGBAPixel(uint8_t r, uint8_t g, uint8_t b): red(r), green(g), blue(b), alpha(255)
{
    // do nothing
}
