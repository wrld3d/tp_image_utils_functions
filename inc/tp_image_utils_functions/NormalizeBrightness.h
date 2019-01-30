#ifndef tp_image_utils_functions_NormalizeBrightness_h
#define tp_image_utils_functions_NormalizeBrightness_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ColorMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
enum class NormalizationMode
{
  None,
  Normalize,
  Exaggerate
};

//##################################################################################################
enum class ShiftBrightnessMode
{
  None,
  ByValue,
  ByMean,
  ByMode,
  ByMedian,
  BySoftMode
};

//##################################################################################################
const char* shiftBrightnessModeToString(ShiftBrightnessMode mode);

//##################################################################################################
ShiftBrightnessMode shiftBrightnessModeFromString(const std::string& mode);

//##################################################################################################
//!
/*!

\param image - The source image
\param radius - The radius in pixels to use for the normalization sample
*/
void normalizeBrightness(tp_image_utils::ColorMap& image,
                         int radius,
                         NormalizationMode mode=NormalizationMode::Normalize,
                         float exaggeration=3.0f);

//##################################################################################################
void shiftBrightness(tp_image_utils::ColorMap& image, ShiftBrightnessMode mode, uint8_t value);

}

#endif
