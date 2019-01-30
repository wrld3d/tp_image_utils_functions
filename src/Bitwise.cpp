#include "tp_image_utils_functions/Bitwise.h"

namespace tp_image_utils_functions
{

//##################################################################################################
const char* logicOpToString(LogicOp operation)
{
  static const char* names[16] =
  {
    "False",
    "NOR",
    "Converse nonimplication",
    "Negation P",
    "Material nonimplication",
    "Negation Q",
    "XOR",
    "NAND",
    "AND",
    "XNOR",
    "Q",
    "Material implication",
    "P",
    "Converse implication",
    "OR",
    "True"
  };

  return names[tpBound(0, int(operation), 15)];
}

//##################################################################################################
LogicOp logicOpFromString(const std::string& operation)
{
  if(operation == "False"                  ) return LogicOp( 0);
  if(operation == "NOR"                    ) return LogicOp( 1);
  if(operation == "Converse nonimplication") return LogicOp( 2);
  if(operation == "Negation P"             ) return LogicOp( 3);
  if(operation == "Material nonimplication") return LogicOp( 4);
  if(operation == "Negation Q"             ) return LogicOp( 5);
  if(operation == "XOR"                    ) return LogicOp( 6);
  if(operation == "NAND"                   ) return LogicOp( 7);
  if(operation == "AND"                    ) return LogicOp( 8);
  if(operation == "XNOR"                   ) return LogicOp( 9);
  if(operation == "Q"                      ) return LogicOp(10);
  if(operation == "Material implication"   ) return LogicOp(11);
  if(operation == "P"                      ) return LogicOp(12);
  if(operation == "Converse implication"   ) return LogicOp(13);
  if(operation == "OR"                     ) return LogicOp(14);
  if(operation == "True"                   ) return LogicOp(15);
  return LogicOpFalse;
}

//##################################################################################################
std::vector<std::string> logicalOps()
{
  std::vector<std::string> logicalOps;

  for(int i=0; i<16; i++)
    logicalOps.push_back(logicOpToString(LogicOp(i)));

  return logicalOps;
}

//##################################################################################################
tp_image_utils::ByteMap bitwise(const tp_image_utils::ByteMap& p,
                                const tp_image_utils::ByteMap& q,
                                LogicOp operation)
{
  static const uint8_t truthTable[16][4]=
  {
    {  0,   0,   0,   0},  // LogicOpFalse
    {255,   0,   0,   0},  // LogicOpNOR
    {  0, 255,   0,   0},  // LogicOpConverseNonimplication
    {255, 255,   0,   0},  // LogicOpNegationP
    {  0,   0, 255,   0},  // LogicOpMaterialNonimplication
    {255,   0, 255,   0},  // LogicOpNegationQ
    {  0, 255, 255,   0},  // LogicOpXOR
    {255, 255, 255,   0},  // LogicOpNAND
    {  0,   0,   0, 255},  // LogicOpAND
    {255,   0,   0, 255},  // LogicOpXNOR
    {  0, 255,   0, 255},  // LogicOpQ
    {255, 255,   0, 255},  // LogicOpMaterialImplication
    {  0,   0, 255, 255},  // LogicOpP
    {255,   0, 255, 255},  // LogicOpConverseImplication
    {  0, 255, 255, 255},  // LogicOpOR
    {255, 255, 255, 255}   // LogicOpTrue
  };

  if(p.size() != q.size())
    return tp_image_utils::ByteMap();

  const uint8_t* tt = &(truthTable[tpBound(0, int(operation), 15)][0]);

  tp_image_utils::ByteMap d(p.width(), p.height());

  const uint8_t* pp = p.constData();
  const uint8_t* qq = q.constData();
  uint8_t* dd = d.data();
  uint8_t* ddMax = dd+d.size();

  for(; dd<ddMax; dd++, pp++, qq++)
    (*dd) = *(tt+((((*pp)>0)?2:0) + (((*qq)>0)?1:0)));

  return d;
}


}
