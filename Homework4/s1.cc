/* 
Author:  Josh Winton
Project: Computer Vision Homework 4
File:    s1.cc
Purpose: Locates sphere in an image and computes its center and radius 
*/
#include "image.h"
#include "sphere.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv)
{

  if (argc != 4)
  {
    printf("Usage: %s [input original image] [input threshold value] [output parameters file]\n", argv[0]);
    return 0;
  }
  const string input_image_file(argv[1]);
  const int input_threshold(stoi(argv[2]));
  const string output_parameters_file(argv[3]);

  printf("Input image file is \"%s\".\n", input_image_file.c_str());
  printf("Input threshold is %i.\n", input_threshold);
  printf("Output parameters file is \"%s\".\n", output_parameters_file.c_str());

  Sphere an_image;
  if (!ReadImage(input_image_file, &an_image))
  {
    cout << "Can't open file " << input_image_file << endl;
    return 0;
  }

  ThresholdImage(input_threshold, &an_image);

  // (row, column)
  pair<int, int> sphere_center = an_image.GetCenter();
  int radius = an_image.GetRadius();

  printf("Sphere center is (%i, %i).\n", sphere_center.first, sphere_center.second);
  printf("Radius is %i.\n", radius);

  ofstream output_file(output_parameters_file);
  if (output_file.is_open())
  {
    output_file << sphere_center.second << " " << sphere_center.first << " " << radius << endl;
    output_file.close();
  }
  else
    cout << "Unable to open output file";

  return 0;
}
