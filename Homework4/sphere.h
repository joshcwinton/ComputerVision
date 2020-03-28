// Class for representing calibration sphere
// Inherits from image class
// Written by Josh Winton for Computer Vision Homework 4

#ifndef COMPUTER_VISION_SPHERE_H_
#define COMPUTER_VISION_SPHERE_H_

#include "image.h"

using namespace std;

namespace ComputerVisionProjects
{
class Sphere : public Image
{
public:
  // Given a thresholded binary image with one sphere in it return the (row, column) coordinates of the centroid
  pair<int, int> GetCenter();

  // Given a thresholded binary image with one sphere in it, return the radius of the cirlce
  int GetRadius();
};

} // namespace ComputerVisionProjects

#endif // COMPUTER_VISION_SPHERE_H_