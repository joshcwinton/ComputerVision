// Class for representing a 3D Object
// Written by Josh Winton for Computer Vision Homework 4

#ifndef COMPUTER_VISION_STEREOOBJECT_H_
#define COMPUTER_VISION_STEREOOBJECT_H_

#include "image.h"
#include <vector>
#include <array>

using namespace std;

namespace ComputerVisionProjects
{

class StereoObject
{
public:
  StereoObject(Image *image_1, Image *image_2, Image *image_3, array<array<double, 3>, 3> S_inverse, int step_size, int threshold);

  // constructor without step for s4
  StereoObject(Image *image_1, Image *image_2, Image *image_3, array<array<double, 3>, 3> S_inverse, int threshold);

  vector<vector<array<double, 3>>> getNormals();
  vector<vector<int>> getAlbedos();
  void drawNormals(Image *normals_image);
  void drawAlbedos(Image *albedos_image);

private:
  int threshold_;
  int step_size_;

  Image *image_1_;
  Image *image_2_;
  Image *image_3_;

  vector<vector<array<double, 3>>> normals_;
  vector<vector<double>> albedos_;

  array<array<double, 3>, 3> S_inverse_;

  void calcNormals();
  void calcAlbedos();
  bool isVisible(int row, int col);
};

} // namespace ComputerVisionProjects

#endif // COMPUTER_VISION_STEREOOBJECT_H_