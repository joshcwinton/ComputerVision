/* 
Author:  Josh Winton
Project: Computer Vision Homework 4
File:    s3.cc
Purpose: Calculates surface normals and albedo using 3 images under different lighting conditions
*/
#include "image.h"
#include "sphere.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// #include <algorithm>
// #include <iterator>
#include <vector>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv)
{

  if (argc != 8)
  {
    printf("Usage: %s [input directions] [image 1] [image 2] [image 3] [step] [threshold] [output]\n", argv[0]);
    return 0;
  }
  const string input_directions_filename(argv[1]);
  const string image_1_filename(argv[2]);
  const string image_2_filename(argv[3]);
  const string image_3_filename(argv[4]);
  const int step(stoi(argv[5]));
  const int threshold(stoi(argv[6]));
  const string output_filename(argv[7]);

  printf("input_directions_filename: \"%s\"\n", input_directions_filename.c_str());
  printf("image_1_filename: \"%s\"\n", image_1_filename.c_str());
  printf("image_2_filename: \"%s\"\n", image_2_filename.c_str());
  printf("image_3_filename: \"%s\"\n", image_3_filename.c_str());
  printf("step: %i\n", step);
  printf("threshold: %i\n", threshold);
  printf("output_filename: \"%s\"\n", output_filename.c_str());

  // Read input directions from file

  // Read image files into Image objects

  // Generate 3D object

  // Write 3D object with normals to image

  return 0;
}
