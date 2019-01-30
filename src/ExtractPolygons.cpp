#include "tp_image_utils_functions/ExtractPolygons.h"

#include "tp_image_utils/ColorMap.h"

#include "tp_utils/DebugUtils.h"

#include "glm/glm.hpp"

namespace tp_image_utils_functions
{

namespace
{

//##################################################################################################
std::string annotation(uint8_t i)
{
  return std::to_string(i);
}

//##################################################################################################
std::string annotation(TPPixel i)
{
  return std::to_string(i.i);
}

//##################################################################################################
template<typename T, typename I>
void simplePolygonExtractionImpl(const T& sourceImage, std::vector<tp_math_utils::Polygon>& results, bool annotate)
{
  int w = sourceImage.width();
  int h = sourceImage.height();

  if(w<1 || h<1 || sourceImage.size()<1)
    return;

  tp_image_utils::ByteMap mask(w, h);
  mask.fill(0);

  tp_image_utils::ColorMap scratch(w, h);
  scratch.fill(TPPixel(0));

  const I* s = sourceImage.constData();
  const uint8_t* m = mask.constData();
  for(int y=0; y<h; y++)
  {
    for(int x=0; x<w; x++, s++, m++)
    {
      if((*m)>0)
        continue;

      I v=(*s);

      std::vector<glm::vec2> toFill;
      toFill.push_back({x, y});
      do
      {
        glm::vec2 p = toFill.at(toFill.size()-1);
        toFill.pop_back();

        if(p.x<0 || p.y<0 || p.x>=w || p.y>=h)
          continue;

        if(mask.pixel(p.x, p.y) != 0)
          continue;

        if(sourceImage.pixel(p.x, p.y) != v)
          continue;

        mask.setPixel(p.x, p.y, 1);

        toFill.push_back({p.x-1, p.y  });
        toFill.push_back({p.x+1, p.y  });
        toFill.push_back({p.x  , p.y-1});
        toFill.push_back({p.x  , p.y+1});
      }
      while(!toFill.empty());

      //     1
      //   .-->.
      // 0 |   | 2
      //   '<--'
      //     3
      int currentSide=0;
      int cx = x;
      int cy = y;

      auto different = [&sourceImage, w, h, &cx, &cy, v](int dx, int dy)
      {
        dx += cx;
        dy += cy;
        if(dx<0 || dy<0 || dx>=w || dy>=h) return true;
        return sourceImage.pixel(dx, dy) != v;
      };

      std::vector<glm::vec2> loop;
      for(;;)
      {
        switch(currentSide)
        {
        case 0: //----------------------------------------------------------------------------------
        {
          loop.push_back({cx, cy});
          if(different(0, 1))
          {
            currentSide = 1;
            break;
          }
          if(different(-1, 1))
          {
            cy += 1;
            break;
          }
          currentSide = 3;
          cx -= 1;
          cy += 1;
          break;
        }

        case 1: //----------------------------------------------------------------------------------
        {
          loop.push_back({cx, cy+1});
          if(different(1, 0))
          {
            currentSide = 2;
            break;
          }
          if(different(1, 1))
          {
            cx += 1;
            break;
          }
          currentSide = 0;
          cx += 1;
          cy += 1;
          break;
        }

        case 2: //----------------------------------------------------------------------------------
        {
          loop.push_back({cx+1, cy+1});
          if(different(0, -1))
          {
            currentSide = 3;
            break;
          }
          if(different(1, -1))
          {
            cy -= 1;
            break;
          }
          currentSide = 1;
          cx += 1;
          cy -= 1;
          break;
        }

        case 3: //----------------------------------------------------------------------------------
        {
          loop.push_back({cx+1, cy});
          if(different(-1, 0))
          {
            currentSide = 0;
            break;
          }
          if(different(-1, -1))
          {
            cx -= 1;
            break;
          }
          currentSide = 2;
          cx -= 1;
          cy -= 1;
          break;
        }
        }

        if(cx==x && cy==y && currentSide==0)
          break;
      }

      tp_math_utils::Polygon poly;
      poly.outer = loop;

      if(annotate)
        poly.properties["value"] = annotation(v);

      results.push_back(poly);
    }
  }
}

}

//##################################################################################################
void ExtractPolygon::simplePolygonExtraction(const tp_image_utils::ByteMap& sourceImage,
                                             std::vector<tp_math_utils::Polygon>& results,
                                             bool annotate)
{
  simplePolygonExtractionImpl<tp_image_utils::ByteMap, uint8_t>(sourceImage, results, annotate);
}

//##################################################################################################
void ExtractPolygon::simplePolygonExtraction(const tp_image_utils::ColorMap& sourceImage,
                                             std::vector<tp_math_utils::Polygon>& results,
                                             bool annotate)
{
  simplePolygonExtractionImpl<tp_image_utils::ColorMap, TPPixel>(sourceImage, results, annotate);
}

}
