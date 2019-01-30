#ifndef tp_image_utils_functions_DrawShapes_h
#define tp_image_utils_functions_DrawShapes_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ColorMap.h"
#include "tp_image_utils/Point.h"
#include "tp_image_utils/Grid.h"

#include <stdint.h>
#include <utility>
#include <vector>

namespace tp_image_utils_functions
{

//##################################################################################################
//! Draws a series of points to an image
tp_image_utils::ColorMap drawPoints(const tp_image_utils::ColorMap& image,
                                    const std::vector<tp_image_utils::Point>& points,
                                    const tp_image_utils::PointStyle& style = tp_image_utils::PointStyle());

//##################################################################################################
//! Draws a series of points to an image
tp_image_utils::ColorMap drawPoints(const tp_image_utils::ColorMap& image,
                                    const std::vector<std::vector<tp_image_utils::Point>>& points,
                                    const tp_image_utils::PointStyle& style = tp_image_utils::PointStyle());


//##################################################################################################
//! Draws a series of points to an image
tp_image_utils::ColorMap drawGrid(const tp_image_utils::Grid& grid,
                                  const tp_image_utils::ColorMap& image,
                                  const tp_image_utils::GridStyle& style = tp_image_utils::GridStyle());
}

#endif
