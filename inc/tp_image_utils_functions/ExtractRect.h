#ifndef tp_image_utils_functions_ExtractRect_h
#define tp_image_utils_functions_ExtractRect_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/Point.h"
#include "tp_image_utils/Grid.h"
#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
struct ExtractRect
{
  //################################################################################################
  //! Extract an area of data from a source image
  /*!
  This will extract a region of data from the source image and then fit it to the output image. The
  list of sourcePoints needs to contain exactly 4 points of type PointTypeRectCorner these will be
  placed into the output image in the following order (top left, top right, bottom right, bottom
  left).

  Any points of type PointTypeRectSide will be evenly placed along the side formed by the
  PointTypeRectCorner points either side of them. This allows you to fit a curved region in to a
  rectangle.
  */
  static tp_image_utils::ColorMap extractRect(const tp_image_utils::ColorMap& sourceImage,
                                              const std::vector<tp_image_utils::Point>& sourcePoints,
                                              size_t width,
                                              size_t height,
                                              std::vector<std::string>& errors);


  //################################################################################################
  static tp_image_utils::ColorMap extractRect(const tp_image_utils::ColorMap& sourceImage,
                                              const tp_image_utils::Grid& clippingGrid,
                                              size_t width,
                                              size_t height,
                                              std::vector<std::string>& errors);

  //################################################################################################
  static tp_image_utils::ColorMap extractRect(const tp_image_utils::ColorMap& sourceImage,
                                              size_t x,
                                              size_t y,
                                              size_t w,
                                              size_t h,
                                              TPPixel pad);

  //################################################################################################
  static tp_image_utils::ColorMap extractRect(const tp_image_utils::ColorMap& sourceImage,
                                              size_t x,
                                              size_t y,
                                              size_t w,
                                              size_t h);




};

}

#endif
