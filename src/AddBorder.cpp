#include "tp_image_utils_functions/AddBorder.h"

#include "tp_image_utils/ColorMap.h"

namespace tp_image_utils_functions
{
//##################################################################################################
tp_image_utils::ByteMap addBorder(const tp_image_utils::ByteMap& src, size_t width, uint8_t value)
{
  tp_image_utils::ByteMap dst = src;

  if((2*width)>dst.height())
    width = dst.height()/2;

  if((2*width)>dst.width())
    width = dst.width()/2;

  //Top
  for(size_t i=0; i<width; i++)
  {
    uint8_t* d = dst.data() + (dst.width()*i);
    uint8_t* dMax = d + dst.width();
    for(; d<dMax; d++)
      (*d) = value;
  }

  //Bottom
  for(size_t i=dst.height()-width; i<dst.height(); i++)
  {
    uint8_t* d = dst.data() + (dst.width()*i);
    uint8_t* dMax = d + dst.width();
    for(; d<dMax; d++)
      (*d) = value;
  }

  //Left and Right
  {
    size_t gap = dst.width() - (2*width);
    size_t iMax = dst.height()-width;
    for(size_t i=width; i<iMax; i++)
    {
      uint8_t* d = dst.data() + (dst.width()*i);
      uint8_t* dMax = d + width;
      for(; d<dMax; d++)
        (*d) = value;

      d+=gap;
      dMax = d + width;
      for(; d<dMax; d++)
        (*d) = value;
    }
  }

  return dst;
}

//##################################################################################################
tp_image_utils::ColorMap addBorder(const tp_image_utils::ColorMap& src, size_t width, const TPPixel& color)
{
  tp_image_utils::ColorMap dst = src;

  if((2*width)>dst.height())
    width = dst.height()/2;

  if((2*width)>dst.width())
    width = dst.width()/2;

  uint8_t r = color.r;
  uint8_t g = color.g;
  uint8_t b = color.b;
  uint8_t a = color.a;

  //Top
  for(size_t i=0; i<width; i++)
  {
    TPPixel* d = dst.data()+ (dst.width()*i);
    TPPixel* dMax = d + dst.width();
    for(; d<dMax; d++)
    {
      d->r = r;
      d->g = g;
      d->b = b;
      d->a = a;
    }
  }

  //Bottom
  for(size_t i=dst.height()-width; i<dst.height(); i++)
  {
    TPPixel* d = dst.data() + (dst.width()*i);
    TPPixel* dMax = d + dst.width();
    for(; d<dMax; d++)
    {
      d->r = r;
      d->g = g;
      d->b = b;
      d->a = a;
    }
  }

  //Left and Right
  {
    size_t gap = dst.width() - (2*width);
    size_t iMax = dst.height()-width;
    for(size_t i=width; i<iMax; i++)
    {
      TPPixel* d = dst.data()+ (dst.width()*i);
      TPPixel* dMax = d + width;
      for(; d<dMax; d++)
      {
        d->r = r;
        d->g = g;
        d->b = b;
        d->a = a;
      }

      d+=gap;
      dMax = d + width;
      for(; d<dMax; d++)
      {
        d->r = r;
        d->g = g;
        d->b = b;
        d->a = a;
      }
    }
  }

  return dst;
}

}
