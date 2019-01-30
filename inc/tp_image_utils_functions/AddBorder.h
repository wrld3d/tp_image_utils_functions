#ifndef tp_image_utils_functions_AddBorder_h
#define tp_image_utils_functions_AddBorder_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"
#include "tp_utils/TPPixel.h"

namespace tp_image_utils_functions
{
//##################################################################################################
tp_image_utils::ByteMap addBorder(const tp_image_utils::ByteMap& src,
                                  size_t width,
                                  uint8_t value=0);

//##################################################################################################
tp_image_utils::ColorMap addBorder(const tp_image_utils::ColorMap& src,
                                   size_t width,
                                   const TPPixel& color=TPPixel(0,0,0,255));

}

#endif
