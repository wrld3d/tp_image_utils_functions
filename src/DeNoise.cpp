#include "tp_image_utils_functions/DeNoise.h"

#include "tp_utils/DebugUtils.h"

#include <memory.h>

namespace tp_image_utils_functions
{

//##################################################################################################
ByteRegions::ByteRegions(const tp_image_utils::ByteMap& src, bool addCorners)
{
  w = src.width();
  h = src.height();

  if(w<1 || h<1)
    return;

  int ci=0;
  regions.resize(w*h);
  map.resize(w*h);
  int* done      = new int[w*h];
  std::pair<int, int>* partial = new std::pair<int, int>[w*h*8];
  int partialCount=0;

  memset(done, 0, w*h*sizeof(int));

  {
    const uint8_t* s = src.constData();
    const uint8_t* sMax = s + (w*h);
    int* d = map.data();
    for(; s<sMax; s++, d++)
      (*d) = (-int(*s))-1;
  }

  for(int y=0; y<h; y++)
  {
    for(int x=0; x<w; x++)
    {
      int offset = (y*w)+x;

      //Don't bother if we already have a count for this
      if(map[offset]>=0)
        continue;

      int i = ci;
      ci++;
      int color = map[offset];

      map[offset] = i;

      ByteRegion& region = regions[i];
      region.value=int(-1-color);
      region.count=0;

      partialCount=0;
      partial[partialCount]=std::pair<int, int>(x-1, y  ); partialCount++;
      partial[partialCount]=std::pair<int, int>(x+1, y  ); partialCount++;
      partial[partialCount]=std::pair<int, int>(x  , y-1); partialCount++;
      partial[partialCount]=std::pair<int, int>(x  , y+1); partialCount++;

      if(addCorners)
      {
        partial[partialCount]=std::pair<int, int>(x+1, y+1); partialCount++;
        partial[partialCount]=std::pair<int, int>(x+1, y-1); partialCount++;
        partial[partialCount]=std::pair<int, int>(x-1, y-1); partialCount++;
        partial[partialCount]=std::pair<int, int>(x-1, y+1); partialCount++;
      }

      while(partialCount>0)
      {
        partialCount--;
        int px = partial[partialCount].first;
        int py = partial[partialCount].second;

        if(px<0 || py<0 || px>=w || py>=h)
          continue;

        int po = (py*w)+px;

        if(done[po]==i)
          continue;

        done[po]=i;

        if(map[po]!=color)
          continue;

        region.count++;
        map[po]=i;
        partial[partialCount]=std::pair<int, int>(px-1, py  ); partialCount++;
        partial[partialCount]=std::pair<int, int>(px+1, py  ); partialCount++;
        partial[partialCount]=std::pair<int, int>(px  , py-1); partialCount++;
        partial[partialCount]=std::pair<int, int>(px  , py+1); partialCount++;

        if(addCorners)
        {
          partial[partialCount]=std::pair<int, int>(px+1, py+1); partialCount++;
          partial[partialCount]=std::pair<int, int>(px+1, py-1); partialCount++;
          partial[partialCount]=std::pair<int, int>(px-1, py-1); partialCount++;
          partial[partialCount]=std::pair<int, int>(px-1, py+1); partialCount++;
        }
      }
    }
  }

  regions.resize(ci);

  delete[] done;
  delete[] partial;
}

//##################################################################################################
void ByteRegions::calculateBoundingBoxes()
{
  {
    ByteRegion* r = regions.data();
    ByteRegion* rMax = r + regions.size();
    for(; r<rMax; r++)
    {
      r->minX = w;
      r->minY = h;
      r->maxX = 0;
      r->maxY = 0;
    }
  }

  for(int y=0; y<h; y++)
  {
    for(int x=0; x<w; x++)
    {
      int index = map[(y*w)+x];
      ByteRegion& region = regions[index];

      if(region.minX>x)
        region.minX=x;

      if(region.minY>y)
        region.minY=y;

      if(region.maxX<x)
        region.maxX=x;

      if(region.maxY<y)
        region.maxY=y;
    }
  }
}

//##################################################################################################
tp_image_utils::ByteMap deNoise(const tp_image_utils::ByteMap& src,
                                int minSize,
                                bool addCorners,
                                uint8_t solid,
                                uint8_t space)
{
  if(minSize<2)
    return src;

  int w = src.width();
  int h = src.height();

  if(w<1 || h<1)
    return src;

  tp_image_utils::ByteMap dst(w, h);
  ByteRegions regions(src, addCorners);

  uint8_t* d = dst.data();
  for(int y=0; y<h; y++)
  {
    for(int x=0; x<w; x++)
    {
      int index = regions.map[(y*w)+x];
      const ByteRegion& region = regions.regions[index];
      (*d) = (region.value==space || region.count<minSize)?space:solid;

      d++;
    }
  }

  return dst;
}

//##################################################################################################
tp_image_utils::ByteMap deNoiseBlobs(const tp_image_utils::ByteMap& src,
                     float minAspectRatio,
                     float maxAspectRatio,
                     float minDensity,
                     float maxDensity,
                     int minSize,
                     int maxSize,
                     bool addCorners,
                     uint8_t solid,
                     uint8_t space)
{
  int w = src.width();
  int h = src.height();

  if(w<1 || h<1)
    return src;

  tp_image_utils::ByteMap dst(w, h);
  ByteRegions regions(src, addCorners);
  regions.calculateBoundingBoxes();

  std::vector<int> erase;
  erase.resize(regions.regions.size());
  {
    ByteRegion* r = regions.regions.data();
    ByteRegion* rMax = r + regions.regions.size();
    int* e = erase.data();
    for(; r<rMax; r++, e++)
    {
      if(r->value==space)
      {
        (*e) = 1;
        continue;
      }

      (*e) = 0;

      int rw = (r->maxX - r->minX)+1;
      int rh = (r->maxY - r->minY)+1;

      float ar = (rw>rh)?(float(rh)/float(rw)):(float(rw)/float(rh));

      float density = float(r->count) / float(rw*rh);

      if(ar<minAspectRatio || ar>maxAspectRatio)
        continue;

      if(density<minDensity || density>maxDensity)
        continue;

      if(rw<minSize || rw>maxSize)
        continue;

      if(rh<minSize || rh>maxSize)
        continue;

      (*e) = 1;
    }
  }


  uint8_t* d = dst.data();
  for(int y=0; y<h; y++)
  {
    for(int x=0; x<w; x++)
    {
      int index = regions.map[(y*w)+x];
      (*d) = (erase[index])?space:solid;

      d++;
    }
  }

  return dst;
}

//##################################################################################################
tp_image_utils::ByteMap deNoiseStripes(const tp_image_utils::ByteMap& src,
                                       int minSize,
                                       uint8_t solid,
                                       uint8_t space)
{
  if(minSize<2)
    return src;

  int w = src.width();
  int h = src.height();

  if(w<1 || h<1)
    return src;

  tp_image_utils::ByteMap dst(w, h);

  //Search columns
  for(int x=0; x<w; x++)
  {
    int count=0;
    bool spaceFound=false;
    for(int y=0; y<h; y++)
    {
      if(src.pixel(x, y)==solid)
        count++;
      else
      {
        dst.setPixel(x, y, space);

        if(count>0)
        {
          uint8_t val = (spaceFound && count<minSize)?space:solid;
          for(int p=y-count; p<y; p++)
            dst.setPixel(x, p, val);

          count=0;
        }

        spaceFound=true;
      }
    }

    if(count>0)
    {
      uint8_t val = solid;
      for(int p=h-count; p<h; p++)
        dst.setPixel(x, p, val);
    }
  }

  //Search rows
  for(int y=0; y<h; y++)
  {
    int count=0;
    bool spaceFound=false;
    for(int x=0; x<w; x++)
    {
      if(dst.pixel(x, y)==solid)
        count++;
      else
      {
        dst.setPixel(x, y, space);

        if(count>0)
        {
          uint8_t val = (spaceFound && count<minSize)?space:solid;
          for(int p=x-count; p<x; p++)
            dst.setPixel(p, y, val);

          count=0;
        }

        spaceFound=true;
      }
    }

    if(count>0)
    {
      uint8_t val = solid;
      for(int p=w-count; p<w; p++)
        dst.setPixel(p, y, val);
    }
  }

  return dst;
}

//##################################################################################################
tp_image_utils::ByteMap deNoiseKnoblets(const tp_image_utils::ByteMap& src,
                                        int knobletWidth,
                                        uint8_t solid,
                                        uint8_t space)
{
  if(knobletWidth<1)
    return src;

  int w = src.width();
  int h = src.height();

  if(w<(knobletWidth+2) || h<(knobletWidth+2))
    return src;

  tp_image_utils::ByteMap dst = src;

  int yMax = h-(knobletWidth+1);
  for(int y=1; y<yMax; y++)
  {
    uint8_t* d = dst.data()+(y*w)+1;
    uint8_t* dMax = d + (w-(knobletWidth+1));
    for(; d<dMax; d++)
    {
      auto calcOnLine = [=](int xincx, int xincy, int yincy, int yincx)
      {
        auto val = [=](int x, int y)
        {
          int px = (x*xincx) + (y*yincx);
          int py = (x*xincy) + (y*yincy);

          return *(d + ((py*w) + px));
        };

        //Left side of the kernel
        if(val(-1, -1)!=space)return;
        if(val(-1,  0)!=space)return;
        if(val(-1,  1)!=solid)return;

        //Center of the kernel
        for(int i=0; i<=knobletWidth; i++)
        {
          if(val(i, -1)!=space)return;
          if(val(i,  1)!=solid)return;
          if(val(i,  0)==space)
          {
            (*d) = space;
            return;
          }
        }
      };

      auto calcOnLeftCorner = [=](int xincx, int xincy, int yincy, int yincx)
      {
        auto val = [=](int x, int y)
        {
          int px = (x*xincx) + (y*yincx);
          int py = (x*xincy) + (y*yincy);

          return *(d + ((py*w) + px));
        };

        //Left side of the kernel
        if(val(-1, -1)!=space)return;
        if(val(-1,  0)!=space)return;
        if(val(-1,  1)!=space)return;

        //Center of the kernel
        for(int i=0; i<=knobletWidth; i++)
        {
          if(val(i, -1)!=space)return;
          if(val(i,  1)!=solid)return;
          if(val(i,  0)==space)
          {
            (*d) = space;
            return;
          }
        }
      };

      auto calcOnRightCorner = [=](int xincx, int xincy, int yincy, int yincx)
      {
        auto val = [=](int x, int y)
        {
          int px = (x*xincx) + (y*yincx);
          int py = (x*xincy) + (y*yincy);

          return *(d + ((py*w) + px));
        };

        //Left side of the kernel
        if(val(-1, -1)!=space)return;
        if(val(-1,  0)!=space)return;
        if(val(-1,  1)!=solid)return;

        //Center of the kernel
        for(int i=0; i<=knobletWidth; i++)
        {
          if(val(i, -1)!=space)return;
          if(val(i,  0)==space)
          {
            if(val(i,  1)==space)
              (*d) = space;
            return;
          }
          if(val(-1,  1)!=solid)return;
        }
      };

      if((*d)==space)continue; else calcOnLine(1, 0,  1,  0);
      if((*d)==space)continue; else calcOnLine(1, 0, -1,  0);
      if((*d)==space)continue; else calcOnLine(0, 1,  0,  1);
      if((*d)==space)continue; else calcOnLine(0, 1,  0, -1);

      if((*d)==space)continue; else calcOnLeftCorner(1, 0,  1,  0);
      if((*d)==space)continue; else calcOnLeftCorner(1, 0, -1,  0);
      if((*d)==space)continue; else calcOnLeftCorner(0, 1,  0,  1);
      if((*d)==space)continue; else calcOnLeftCorner(0, 1,  0, -1);

      if((*d)==space)continue; else calcOnRightCorner(1, 0,  1,  0);
      if((*d)==space)continue; else calcOnRightCorner(1, 0, -1,  0);
      if((*d)==space)continue; else calcOnRightCorner(0, 1,  0,  1);
      if((*d)==space)continue; else calcOnRightCorner(0, 1,  0, -1);
    }
  }

  return dst;
}

}
