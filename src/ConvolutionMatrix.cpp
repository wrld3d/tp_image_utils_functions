#include "tp_image_utils_functions/ConvolutionMatrix.h"

#include "tp_image_utils/ColorMap.h"

namespace tp_image_utils_functions
{

//##################################################################################################
ConvolutionMatrix::ConvolutionMatrix()
{
  makeIdentity();
}

//##################################################################################################
ConvolutionMatrix::ConvolutionMatrix(const std::string& text)
{
  loadString(text);
}

//##################################################################################################
ConvolutionMatrix::ConvolutionMatrix(const std::vector<int>& matrixData, int width, int height)
{
  setMatrixData(matrixData, width, height);
}

//##################################################################################################
int ConvolutionMatrix::width()const
{
  return m_width;
}

//##################################################################################################
int ConvolutionMatrix::height()const
{
  return m_height;
}

//##################################################################################################
std::vector<int> ConvolutionMatrix::matrixData()const
{
  return m_matrixData;
}

//##################################################################################################
void ConvolutionMatrix::setMatrixData(const std::vector<int>& matrixData, int width, int height)
{
  if(width<3 || (width&1)!=1   ||
     height<3 || (height&1)!=1 ||
     (width*height) != int(matrixData.size()))
    makeIdentity();
  else
  {
    m_width = width;
    m_height = height;
    m_matrixData = matrixData;
  }
}

//##################################################################################################
std::string ConvolutionMatrix::toString()const
{
  std::string output;

  const int* d = m_matrixData.data();

  for(int y=0; y<m_height; y++)
  {
    if(y>0)
      output.push_back('|');

    for(int x=0; x<m_width; x++)
    {
      if(x>0)
        output.push_back(',');

      output.append(std::to_string(*d));
      d++;
    }
  }

  return output;
}

//##################################################################################################
void ConvolutionMatrix::loadString(const std::string& text)
{
  m_matrixData.clear();
  m_height = -1;

  std::vector<std::string> rows;
  tpSplit(rows, text, '|', tp_utils::SplitBehavior::SkipEmptyParts);

  m_width = rows.size();

  if(m_width<3 || (m_width&1)!=1)
  {
    makeIdentity();
    return;
  }

  for(const std::string& row : tpConst(rows))
  {
    std::vector<std::string> parts;
    tpSplit(parts, row, ',', tp_utils::SplitBehavior::SkipEmptyParts);

    if(m_height<1)
    {
      m_height = parts.size();

      if(m_height<3 || (m_height&1)!=1)
      {
        makeIdentity();
        return;
      }
    }
    else if(m_height != int(parts.size()))
    {
      makeIdentity();
      return;
    }

    try
    {
      for(const std::string& part : tpConst(parts))
        m_matrixData.push_back(std::stoi(part));
    }
    catch(...)
    {

    }
  }
}

//##################################################################################################
tp_image_utils::ColorMap ConvolutionMatrix::convolve(const tp_image_utils::ColorMap& src)const
{
  return convolutionMatrix(src, m_matrixData, m_width, m_height);
}

//##################################################################################################
void ConvolutionMatrix::makeIdentity()
{
  m_width =  3;
  m_height = 3;

  m_matrixData =
  {
    0, 0, 0,
    0, 9, 0,
    0, 0, 0
  };
}

namespace
{
//##################################################################################################
struct PixelDetails_lt
{
  int red;
  int green;
  int blue;

  PixelDetails_lt():
    red(0),
    green(0),
    blue(0)
  {

  }
};
}

//##################################################################################################
tp_image_utils::ColorMap convolutionMatrix(const tp_image_utils::ColorMap& src, const std::vector<int>& matrixData, int width, int height)
{
  if(width<=1 || height<=1)
    return tp_image_utils::ColorMap();

  int size = width*height;

  if(size>int(matrixData.size()))
    return tp_image_utils::ColorMap();

  int dw = src.width()  - width;//((width+1)/2);
  int dh = src.height() - height;//((height+1)/2);

  if(dw<1 || dh<1)
    return tp_image_utils::ColorMap();

  std::vector<PixelDetails_lt> buffer;
  buffer.resize(dw*dh);

  PixelDetails_lt* bufferData = buffer.data();

  for(int my=0; my<height; my++)
  {
    for(int mx=0; mx<width;  mx++)
    {
      int weight = matrixData.at((my*width)+mx);
      for(int dy=0; dy<dh; dy++)
      {
        auto* s = src.constData() + ((dy+my)*src.width()) + mx;
        PixelDetails_lt* d = bufferData + (dy*dw);
        PixelDetails_lt* dMax = d + dw;
        while(d<dMax)
        {
          d->red   += int(s->r) * weight;
          d->green += int(s->g) * weight;
          d->blue  += int(s->b) * weight;

          d++;
          s++;
        }
      }
    }
  }

  tp_image_utils::ColorMap dst(dw, dh);
  {
    PixelDetails_lt* s = bufferData;

    for(int y=0; y<dh; y++)
    {
      TPPixel* d = dst.data() + (y*dw);
      TPPixel* dMax = d+dw;

      while(d<dMax)
      {
        d->r = tpBound(0, (s->red   / size), 255);
        d->g = tpBound(0, (s->green / size), 255);
        d->b = tpBound(0, (s->blue  / size), 255);
        d->a = 255;
        d++;
        s++;
      }
    }
  }

  return dst;
}
}
