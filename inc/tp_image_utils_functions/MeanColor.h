#ifndef tp_image_utils_functions_MeanColor_h
#define tp_image_utils_functions_MeanColor_h

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace tp_image_utils
{
class ColorMap;
}

namespace tp_image_utils_functions
{
glm::vec4 meanColor(const tp_image_utils::ColorMap& image, const glm::ivec2& location, size_t radius);
}

#endif
