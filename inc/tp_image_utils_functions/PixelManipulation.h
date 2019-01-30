#ifndef tp_image_utils_functions_PixelManipulation_h
#define tp_image_utils_functions_PixelManipulation_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"
#include "tp_image_utils/ColorMap.h"

namespace tp_image_utils_functions
{
/*!
All input and output values are floating point in the range 0.0f to 1.0f.

In values for color input images:
- red
- green
- blue
- alpha

In values for byte input images:
- byte

*/
struct PixelManipulation
{
  //Calculation for color image output
  std::string calcRed   {"red"};
  std::string calcGreen {"green"};
  std::string calcBlue  {"blue"};
  std::string calcAlpha {"alpha"};

  //Calculation for byte image output
  std::string calcByte  {"byte"};
};

//##################################################################################################
tp_image_utils::ColorMap pixelManipulationColor(const tp_image_utils::ColorMap& src, const PixelManipulation& params, std::vector<std::string>& errors);

//##################################################################################################
tp_image_utils::ColorMap pixelManipulationColor(const tp_image_utils::ByteMap& src, const PixelManipulation& params, std::vector<std::string>& errors);

//##################################################################################################
tp_image_utils::ByteMap pixelManipulationByte(const tp_image_utils::ColorMap& src, const PixelManipulation& params, std::vector<std::string>& errors);

//##################################################################################################
tp_image_utils::ByteMap pixelManipulationByte(const tp_image_utils::ByteMap& src, const PixelManipulation& params, std::vector<std::string>& errors);

}

#endif
