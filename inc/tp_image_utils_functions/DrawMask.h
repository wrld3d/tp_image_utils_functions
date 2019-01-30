#ifndef tp_image_utils_functions_DrawMask_h
#define tp_image_utils_functions_DrawMask_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ColorMap.h"
#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
void drawMask(tp_image_utils::ColorMap& image,
              TPPixel color,
              const tp_image_utils::ByteMap& mask,
              uint8_t maskValue);

}

#endif
