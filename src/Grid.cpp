#include "tp_image_utils/Grid.h"

#include "json.hpp"

namespace tp_image_utils
{

//##################################################################################################
std::string gridTypeToString(GridType gridType)
{
  switch(gridType)
  {
  case GridTypeFinite:   return "GridTypeFinite";
  case GridTypeInfinite: return "GridTypeInfinite";
  }

  return "GridTypeInfinite";
}

//##################################################################################################
GridType gridTypeFromString(const std::string& gridType)
{
  if(gridType == "GridTypeFinite")
    return GridTypeFinite;

  return GridTypeInfinite;
}

//##################################################################################################
Grid::Grid():
  type(GridTypeInfinite),
  origin(0.0f, 0.0f),
  xAxis(1.0f, 0.0f),
  yAxis(0.0f, 1.0f),
  xCells(0),
  yCells(0)
{

}

//##################################################################################################
ColorMap Grid::drawGrid(const ColorMap& image, const GridStyle& style)const
{
  int cx = xCells;
  if(cx<1)
    cx=10;

  int cy = yCells;
  if(cy<1)
    cy=10;

  Point xEnd(xAxis.x*float(cx), xAxis.y*float(cx));
  Point yEnd(yAxis.x*float(cy), yAxis.y*float(cy));

  //Calculate the lines that form the grid
  LineCollection lines;

  for(int c=0; c<=cx; c++)
  {
    Line line;
    line.push_back(Point(origin.x + (float(c)*xAxis.x),          origin.y + (float(c)*xAxis.y)         ));
    line.push_back(Point(origin.x + yEnd.x + (float(c)*xAxis.x), origin.y + yEnd.y + (float(c)*xAxis.y)));
    lines.push_back(line);
  }

  for(int c=0; c<=cy; c++)
  {
    Line line;
    line.push_back(Point(origin.x + (float(c)*yAxis.x),          origin.y + (float(c)*yAxis.y)         ));
    line.push_back(Point(origin.x + xEnd.x + (float(c)*yAxis.x), origin.y + xEnd.y + (float(c)*yAxis.y)));
    lines.push_back(line);
  }

  //Draw a box at the origin
  {
    Line line;
    line.push_back(Point(origin.x-2, origin.y-2));
    line.push_back(Point(origin.x-2, origin.y+2));
    line.push_back(Point(origin.x+2, origin.y+2));
    line.push_back(Point(origin.x+2, origin.y-2));
    line.push_back(Point(origin.x-2, origin.y-2));
    lines.push_back(line);
  }


  PointStyle ps;
  ps.lineColor = style.lineColor;
  return Point::drawPoints(image, lines, ps);
}

//##################################################################################################
Grid deserializeGrid(const std::string& data)
{
  Grid result;

  if(!data.empty())
  {
    nlohmann::json j = nlohmann::json::parse(data, nullptr, false);

    result.type = gridTypeFromString(j["type"]);

    result.origin = deserializePoint(j["origin"]);

    result.xAxis = deserializePoint(j["xAxis"]);
    result.yAxis = deserializePoint(j["yAxis"]);

    result.xCells = j["xCells"];
    result.yCells = j["yCells"];
  }

  return result;
}

//##################################################################################################
std::string serializeGrid(const Grid& grid)
{
  nlohmann::json j;

  j["type"] = gridTypeToString(grid.type);

  j["origin"] = serializePoint(grid.origin);

  j["xAxis"] = serializePoint(grid.xAxis);
  j["yAxis"] = serializePoint(grid.yAxis);

  j["xCells"] = grid.xCells;
  j["yCells"] = grid.yCells;

  return j;
}

//##################################################################################################
std::vector<Grid> deserializeGrids(const std::vector<std::string>& data)
{
  std::vector<Grid> result;
  for(const std::string& grid : data)
    result.push_back(deserializeGrid(grid));
  return result;
}

//##################################################################################################
std::vector<std::string> serializeGrids(const std::vector<Grid>& grids)
{
  std::vector<std::string> result;
  for(const Grid& grid : grids)
    result.push_back(serializeGrid(grid));
  return result;
}

}
