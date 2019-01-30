#ifndef tp_image_utils_functions_Bitwise_h
#define tp_image_utils_functions_Bitwise_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
enum LogicOp
{
  LogicOpFalse                  = 0,
  LogicOpNOR                    = 1,
  LogicOpConverseNonimplication = 2,
  LogicOpNegationP              = 3,
  LogicOpMaterialNonimplication = 4,
  LogicOpNegationQ              = 5,
  LogicOpXOR                    = 6,
  LogicOpNAND                   = 7,
  LogicOpAND                    = 8,
  LogicOpXNOR                   = 9,
  LogicOpQ                      = 10,
  LogicOpMaterialImplication    = 11,
  LogicOpP                      = 12,
  LogicOpConverseImplication    = 13,
  LogicOpOR                     = 14,
  LogicOpTrue                   = 15
};

//##################################################################################################
const char* logicOpToString(LogicOp operation);

//##################################################################################################
LogicOp logicOpFromString(const std::string& operation);

//##################################################################################################
std::vector<std::string> logicalOps();

//##################################################################################################
tp_image_utils::ByteMap bitwise(const tp_image_utils::ByteMap& p,
                                const tp_image_utils::ByteMap& q,
                                LogicOp operation);


}

#endif
