#ifndef tp_image_utils_functions_ToFloat_h
#define tp_image_utils_functions_ToFloat_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ColorMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
enum class ChannelMode
{
  Interleaved,
  Separate
};

//##################################################################################################
enum class ChannelOrder
{
  RGB,
  BGR
};

//##################################################################################################
std::vector<std::string> channelModes();

//##################################################################################################
std::string channelModeToString(ChannelMode channelMode);

//##################################################################################################
ChannelMode channelModeFromString(const std::string& channelMode);

//##################################################################################################
std::vector<std::string> channelOrders();

//##################################################################################################
std::string channelOrderToString(ChannelOrder channelOrder);

//##################################################################################################
ChannelOrder channelOrderFromString(const std::string& channelOrder);


//##################################################################################################
//! Convert an image to floating point array
/*!

*/
void toFloat(const tp_image_utils::ColorMap& src,
             ChannelMode channelMode,
             ChannelOrder channelOrder,
             std::vector<float>& outData);
}

#endif
