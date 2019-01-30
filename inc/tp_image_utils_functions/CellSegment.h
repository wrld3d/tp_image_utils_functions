#ifndef tp_image_utils_functions_CellSegment_h
#define tp_image_utils_functions_CellSegment_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
enum class CellGrowMode
{
  Box,
  Flood
};

//##################################################################################################
const char* cellGrowModeToString(CellGrowMode mode);

//##################################################################################################
CellGrowMode cellGrowModeFromString(const std::string& mode);

//##################################################################################################
struct CellSegmentParameters
{
  int distanceFieldRadius{512};
  int minRadius{10};
  int maxInitialCells{20};

  int growCellsPasses{100};

  CellGrowMode cellGrowMode{CellGrowMode::Box};
};

//##################################################################################################
tp_image_utils::ByteMap cellSegmentInitialCells(const tp_image_utils::ByteMap& src, const CellSegmentParameters& params);

//##################################################################################################
tp_image_utils::ByteMap cellSegment(const tp_image_utils::ByteMap& src, const CellSegmentParameters& params);

//##################################################################################################
tp_image_utils::ByteMap cellSegment(const tp_image_utils::ByteMap& src, const tp_image_utils::ByteMap& labels, const CellSegmentParameters& params);

//##################################################################################################
tp_image_utils::ByteMap cellSegmentSimple(const tp_image_utils::ByteMap& src, const CellSegmentParameters& params);

}

#endif
