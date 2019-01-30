#ifndef tp_image_utils_functions_ToPolar_h
#define tp_image_utils_functions_ToPolar_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
tp_image_utils::ByteMap toPolar(const tp_image_utils::ByteMap& src, size_t w, size_t h);

}

#endif
