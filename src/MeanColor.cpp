#include "tp_image_utils_functions/MeanColor.h"
#include "tp_utils/Globals.h"
#include "tp_image_utils/ColorMap.h"
#include <glm/vec3.hpp>

namespace tp_image_utils_functions
{

glm::vec4 meanColor(const tp_image_utils::ColorMap& image, const glm::ivec2& location, size_t radius)
{
  const auto width = image.width();
  const auto height = image.height();

  const auto minX = size_t(tpBound(size_t(0), size_t(location.x) - radius, width));
  const auto maxX = size_t(tpBound(size_t(0), size_t(location.x) + radius, width));
  const auto minY = size_t(tpBound(size_t(0), size_t(location.y) - radius, height));
  const auto maxY = size_t(tpBound(size_t(0), size_t(location.y) + radius, height));

  glm::dvec3 color{0.0, 0.0, 0.0};
  double count=0.0;
  const auto imageData = image.constDataVector();

  for(size_t y = minY; y < maxY; y++)
  {
    auto offset = y * size_t(width);
    for(size_t x = minX; x < maxX; x++)
    {
      TPPixel p = imageData.at(offset + x);
      color.r += p.r;
      color.g += p.g;
      color.b += p.b;
      count += 1.0;
    }
  }

  if(count > 0.8)
  {
    color = color / (count * 255.0);
  }

  return glm::dvec4(color, 1.0f);
}

}
