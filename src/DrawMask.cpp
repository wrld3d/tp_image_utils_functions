#include "tp_image_utils_functions/DrawMask.h"

namespace tp_image_utils_functions
{

//##################################################################################################
void drawMask(tp_image_utils::ColorMap& image,
              TPPixel color,
              const tp_image_utils::ByteMap& mask,
              uint8_t maskValue)
{
  if(image.size() != mask.size())
    return;

  TPPixel* i = image.data();
  const uint8_t* m = mask.constData();
  TPPixel* iMax = i + image.size();
  for(; i<iMax; i++, m++)
    if((*m) == maskValue)
      (*i) = color;
}

}
