#include "image.h"

void Image::flipleft()
{
  RGBAPixel t;
  for(size_t y = 0; y < this->height(); y++){
    for(size_t x = 0; x < this->width()/2; x++){
      t = *(*this)(x,y);
      *(*this)(x,y) = *(*this)(width()-x-1,y);
      *(*this)(width()-x-1,y) = t;
    }
  }
}

void Image::adjustbrightness(int r, int g, int b)
{
  for(size_t y = 0; y < this->height(); y++){
    for(size_t x = 0; x < this->width(); x++){
      if(r>0){
        (*this)(x,y)->red = std::min((*this)(x,y)->red + r, 255);
      }
      else{
        (*this)(x,y)->red = std::max((*this)(x,y)->red + r, 0);
      }
      if(g>0){
        (*this)(x,y)->green = std::min((*this)(x,y)->green + g, 255);
      }
      else{
        (*this)(x,y)->green = std::max((*this)(x,y)->green + g, 0);
      }
      if(b>0){
        (*this)(x,y)->blue = std::min((*this)(x,y)->blue + b, 255);
      }
      else{
        (*this)(x,y)->blue = std::max((*this)(x,y)->blue + b, 0);
      }
    }
  }
}

void Image::invertcolors()
{
  for(size_t y = 0; y < this->height(); y++){
    for(size_t x = 0; x < this->width(); x++){
        (*this)(x,y)->red = 255 - (*this)(x,y)->red;
        (*this)(x,y)->green = 255 - (*this)(x,y)->green;
        (*this)(x,y)->blue = 255 - (*this)(x,y)->blue;
    }
  }
}
