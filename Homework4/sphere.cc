// Class for representing calibration sphere
// Inherits from image class
// Written by Josh Winton for Computer Vision Homework 4

#include "sphere.h"
#include <vector>
#include <iostream>
#include <cmath>

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

// Given a center and radius, return a vector representing normal as (x, y, z) with its length as pixel brightness
vector<int> Sphere::GetNormal(int x_center, int y_center, int radius)
{
  vector<int> unit_normal;
  int max_brightness = 0;
  int bright_x_center;
  int bright_y_center;

  // Find brightest pixel
  // Store that pixel and its brightness
  for (size_t i = 0; i < num_rows(); i++)
  {
    for (size_t j = 0; j < num_columns(); j++)
    {
      if (GetPixel(i, j) >= max_brightness)
      {
        max_brightness = GetPixel(i, j);
        bright_x_center = j;
        bright_y_center = i;
      }
    }
  }

  // Find that pixel w.r.t sphere center
  bright_x_center -= x_center;
  bright_y_center -= y_center;

  // cout << bright_x_center << " " << bright_y_center << endl;

  // Get the normal at that point
  double x_component = bright_x_center / (sqrt(pow(radius, 2) - pow(bright_x_center, 2) - pow(bright_y_center, 2)));
  double y_component = bright_y_center / (sqrt(pow(radius, 2) - pow(bright_x_center, 2) - pow(bright_y_center, 2)));

  // cout << x_component << " " << y_component << endl;

  // Scale it to the unit normal
  double scaled_x = x_component / sqrt(pow(x_component, 2) + pow(y_component, 2) + 1);
  double scaled_y = y_component / sqrt(pow(x_component, 2) + pow(y_component, 2) + 1);
  double scaled_z = 1 / sqrt(pow(x_component, 2) + pow(y_component, 2) + 1);

  // cout << scaled_x << " " << scaled_y << " " << scaled_z << endl;

  // Scale it by the pixel brightness

  scaled_x *= max_brightness;
  scaled_y *= max_brightness;
  scaled_z *= max_brightness;

  // cout << scaled_x << " " << scaled_y << " " << scaled_z << endl;

  unit_normal.push_back((int)scaled_x);
  unit_normal.push_back((int)scaled_y);
  unit_normal.push_back((int)scaled_z);

  return unit_normal;
}

} // namespace ComputerVisionProjects