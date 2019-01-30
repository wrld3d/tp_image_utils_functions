#ifndef tp_image_utils_functions_ExtractRect_h
#define tp_image_utils_functions_ExtractRect_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"

#include "tp_math_utils/Polygon.h"

namespace tp_image_utils_functions
{

//##################################################################################################
struct ExtractPolygon
{
  //################################################################################################
  static void simplePolygonExtraction(const tp_image_utils::ByteMap& sourceImage,
                                      std::vector<tp_math_utils::Polygon>& results,
                                      bool annotate=false);

  //################################################################################################
  static void simplePolygonExtraction(const tp_image_utils::ColorMap& sourceImage,
                                      std::vector<tp_math_utils::Polygon>& results,
                                      bool annotate=false);
};

}

#endif
