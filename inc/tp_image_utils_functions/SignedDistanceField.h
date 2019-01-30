#ifndef tp_image_utils_functions_SignedDistanceField_h
#define tp_image_utils_functions_SignedDistanceField_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
//! Generate a signed distance field image
/*!
This will generate a signed distance filed image the generated image will be grey with the red,
green, and blue channels each set to the same SDF value. The alpha channel will be set to 255.

\param src - The source image only the red channel will be used, values >0 will be cosidered white.
\param radius - This controls the radius at which the generated value will saturate.
\return The generated signed distance field.
*/
tp_image_utils::ColorMap signedDistanceField(const tp_image_utils::ColorMap& src, int radius);

//##################################################################################################
//! Generate a signed distance field image
/*!
This will generate a signed distance filed image the generated image will be grey with the red,
green, and blue channels each set to the same SDF value. The alpha channel will be set to 255.

\param src - The source image only the red channel will be used, values >0 will be cosidered white.
\param radius - This controls the radius at which the generated value will saturate.
\param width - The width of the destination image, may be less than the source width.
\param height - The height of the destination image, may be less than the source height.
\return The generated signed distance field.
*/
tp_image_utils::ColorMap signedDistanceField(const tp_image_utils::ColorMap& src, int radius, int width, int height);

//##################################################################################################
tp_image_utils::ByteMap signedDistanceField(const tp_image_utils::ByteMap& src, int radius);

//##################################################################################################
tp_image_utils::ByteMap distanceField(const tp_image_utils::ByteMap& src, int radius);

//##################################################################################################
tp_image_utils::ByteMap signedDistanceField(const tp_image_utils::ByteMap& src, int radius, int width, int height);

}

#endif
