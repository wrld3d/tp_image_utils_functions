#ifndef tp_image_utils_functions_ToHue_h
#define tp_image_utils_functions_ToHue_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{
//##################################################################################################
//! Extract the colors and remove shading
/*!
This will produce a rgb image containing the normalized color.

\param src - The color image to extract the color from.
\return A rgb image with the colors normalized.
*/
tp_image_utils::ColorMap toHue(const tp_image_utils::ColorMap& src);

//##################################################################################################
tp_image_utils::ColorMap toHue(const tp_image_utils::ByteMap& src);

//##################################################################################################
tp_image_utils::ByteMap toHueGray(const tp_image_utils::ColorMap& src);

}

#endif
