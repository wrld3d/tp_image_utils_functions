#ifndef tp_image_utils_functions_FindPixelGrid_h
#define tp_image_utils_functions_FindPixelGrid_h

#include "tp_image_utils_functions/Globals.h"

#include "tp_image_utils/ByteMap.h"
#include "tp_image_utils/Grid.h"

namespace tp_image_utils_functions
{

//##################################################################################################
struct FindPixelGrid
{
  static float mean(const std::vector<int>& values);

  static float mean(const std::vector<float>& values);

  static float squaredSD(const std::vector<int>& values, float& mean);

  static float squaredSD(const std::vector<float>& values, float& mean);

  static float standardDeviation(const std::vector<int>& values, float& mean);

  static std::vector<int> stripOutliers(const std::vector<int>& values, float mean, float squaredSD);

  static std::vector<float> stripOutliers(const std::vector<float>& values, float mean, float squaredSD);

  static std::vector<int> findReversals(const std::vector<uint8_t>& src);

  static std::vector<int> findReversalsH(const tp_image_utils::ByteMap& src);

  static std::vector<int> findReversalsV(const tp_image_utils::ByteMap& src);

  static float findMeanPixelSize(const std::vector<int>& values);

  static float findMeanPixelWidth(const tp_image_utils::ByteMap& src);

  static float findMeanPixelHeight(const tp_image_utils::ByteMap& src);

  //################################################################################################
  //! Finds reversals in brightness
  /*!
  The result pixels:
   - 0   = Dark to light
   - 128 = No reversal
   - 255 = Light to dark

  \param src - A gray scale vector containing the source data
  \return  - An vector the same size as the source image colored as above
  */
  static std::vector<uint8_t> reversals(const std::vector<uint8_t>& src);

  //################################################################################################
  //! Finds reversals in brightness
  /*!
  The result pixels:
   - 0   = Dark to light
   - 128 = No reversal
   - 255 = Light to dark

  \param src - A gray scale image containing the source data
  \return  - An image the same size as the source image colored as above
  */
  static tp_image_utils::ByteMap reversalsH(const tp_image_utils::ByteMap& src);

  //################################################################################################
  //! Finds reversals in brightness
  /*!
  The result pixels:
   - 0   = Dark to light
   - 128 = No reversal
   - 255 = Light to dark

  \param src - A gray scale image containing the source data
  \return  - An image the same size as the source image colored as above
  */
  static tp_image_utils::ByteMap reversalsV(const tp_image_utils::ByteMap& src);

  //################################################################################################
  static tp_image_utils::ByteMap findPixelGrid(const tp_image_utils::ByteMap& src);

  //################################################################################################
  static tp_image_utils::ColorMap findPixelGrid(const tp_image_utils::ByteMap& src, const tp_image_utils::ColorMap& src2);

  //################################################################################################
  struct FindRegularGridParams
  {
    int xCells;  //!< The number of cells to find on the x axis, or 0 to calculate this.
    int yCells;  //!< The number of cells to find on the y axis, or 0 to calculate this.

    tp_image_utils::LineCollection* hLines; //!< If set this will be populated with the list of horizontal lines.
    tp_image_utils::LineCollection* vLines; //!< If set this will be populated with the list of vertical lines.

    tp_image_utils::Line* correctedCorners; //!< Stretch the grid to best fit the corners

    float angleDeviation; //!< The maximum difference between the grid orientation and a line.

    FindRegularGridParams():
      xCells(14),
      yCells(14),
      hLines(nullptr),
      vLines(nullptr),
      correctedCorners(nullptr),
      angleDeviation(2.0f)
    {

    }
  };

  //################################################################################################
  //! Find a grid in the lines
  /*!
  This will search for a grid in the lines using the following steps:
  1. Rotate the lines to find the angle where the most lines are parallel or perpendicular.
  2. Once it has an orientation for the grid it will filter out lines that dont fit.
  3. Then it will try to find the best spacing by measuring the distances between lines and
     filtering out the outliers.
  4. Then it will find the best offset to align the grid with the remaining lines. This will be
     between 0 and the cell width.
  5. Finaly if it is searching for a finite grid it will adjust the offset to move the grid over the
     lines so that the grid matches the most lines.

  \param lines - The lines to search.
  \param gridType - The type of grid to produce.
  \param params - Extra optional params.
  \return The best fitting grid that it could find.
  */
  static tp_image_utils::Grid findRegularGrid(const tp_image_utils::LineCollection& lines,
                                              tp_image_utils::GridType gridType,
                                              const FindRegularGridParams& params = FindRegularGridParams());
};

}

#endif
