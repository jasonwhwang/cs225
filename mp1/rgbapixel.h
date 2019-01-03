#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

#include <cstdint>
using std::uint8_t;

class RGBAPixel
{
    public:
        uint8_t red, green, blue, alpha;
        RGBAPixel();
        RGBAPixel(uint8_t red, uint8_t green, uint8_t blue);
};

#endif
