#ifndef tp_image_utils_functions_FillConcaveHull_h
#define tp_image_utils_functions_FillConcaveHull_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
struct FillConcaveHullParameters
{
  uint8_t solid  {0};  //!< The value of a solid pixel
};

//##################################################################################################
tp_image_utils::ByteMap fillConcaveHull(const tp_image_utils::ByteMap& src,
                                        const FillConcaveHullParameters& params);

}

#endif
