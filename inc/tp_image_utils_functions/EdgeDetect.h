#ifndef tp_image_utils_functions_EdgeDetect_h
#define tp_image_utils_functions_EdgeDetect_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
tp_image_utils::ByteMap edgeDetect(const tp_image_utils::ColorMap& src, int threshold);

//##################################################################################################
tp_image_utils::ByteMap edgeDetect(const tp_image_utils::ByteMap& src, uint8_t threshold);

//##################################################################################################
tp_image_utils::ByteMap edgeDetectCorner(const tp_image_utils::ByteMap& src, uint8_t threshold);

}

#endif
