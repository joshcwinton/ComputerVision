// Class for representing calibration sphere
// Inherits from image class
// Written by Josh Winton for Computer Vision Homework 4

#include "sphere.h"

using namespace std;

namespace ComputerVisionProjects
{

pair<int, int> Sphere::GetCenter()
{
  int row_sum = 0;
  int column_sum = 0;
  int area = 0;
  pair<int, int> center;

  for (size_t i = 0; i < num_rows(); i++)
  {
    for (size_t j = 0; j < num_columns(); j++)
    {
      if (GetPixel(i, j) != 0)
      {
        area++;
        row_sum += i;
        column_sum += j;
      }
    }
  }

  center.first = row_sum / area;
  center.second = column_sum / area;

  return center;
}

int Sphere::GetRadius()
{
  int min_row = num_rows();
  int min_column = num_columns();
  int max_row = 0;
  int max_column = 0;

  int vertical_diameter;
  int horizontal_diameter;
  int avg_diameter;
  int avg_radius;

  for (size_t i = 0; i < num_rows(); i++)
  {
    for (size_t j = 0; j < num_columns(); j++)
    {
      if (GetPixel(i, j) == 0)
      {
        continue;
      }
      if (i > max_row)
        max_row = i;

      if (i < min_row)
        min_row = i;

      if (j > max_column)
        max_column = j;

      if (j < min_column)
        min_column = j;
    }
  }

  vertical_diameter = max_row - min_row;
  horizontal_diameter = max_column - min_column;
  avg_diameter = (vertical_diameter + horizontal_diameter) / 2;
  avg_radius = avg_diameter / 2;

  return avg_radius;
}
} // namespace ComputerVisionProjects