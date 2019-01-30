#ifndef tp_image_utils_functions_DrawLine_h
#define tp_image_utils_functions_DrawLine_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ColorMap.h"

#include <stdint.h>
#include <utility>
#include <vector>

namespace tp_image_utils_functions
{

//##################################################################################################
void drawLine(tp_image_utils::ColorMap& image, TPPixel color, int x1, int y1, int x2, int y2);

//##################################################################################################
void drawPolyline(tp_image_utils::ColorMap& image, TPPixel color, const std::vector<std::pair<int,int>>& points);

}

#endif
