#ifndef tp_image_utils_functions_ReduceColors_h
#define tp_image_utils_functions_ReduceColors_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{
//##################################################################################################
//! Reduce the number of colors in an image
/*!
This will produce an image with a reduced color palette.

\param src - The source image;
\return A copy of the source image rendered with.
*/
tp_image_utils::ColorMap reduceColors(const tp_image_utils::ColorMap& src, int colorCount);


//##################################################################################################
tp_image_utils::ByteMap reduceColors(const tp_image_utils::ByteMap& src);

}

#endif
