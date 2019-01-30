#ifndef tp_image_utils_functions_SlotFill_h
#define tp_image_utils_functions_SlotFill_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
struct SlotFillParameters
{
  uint8_t solid  {0};  //!< The value of a solid pixel
  uint8_t slot {255}; //!< The value of a slot pixel

  size_t endMinEach  {1}; //!< Both ends should be at least this long
  size_t endMinEither{5}; //!< One or both ends should be at least this long
  size_t endMinSum   {6}; //!< The sum of both ends should be at lest this lone

  size_t borderMinEach  {1}; //!< Both ends should have a border at least this long
  size_t borderMinEither{1}; //!< One or both ends should have a border at least this long
  size_t borderMinSum   {2}; //!< The sum of both ends should have a border at lest this long

  size_t startAngle {0}; //!< The start angle to rotate the image from
  size_t maxAngle  {90}; //!< The maximum rotation
  size_t stepAngle {10}; //!< The amount to increment the angle by
};

//##################################################################################################
tp_image_utils::ByteMap slotFill(const tp_image_utils::ByteMap& src, const SlotFillParameters& params);

}

#endif
