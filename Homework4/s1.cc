/* 
Author:  Josh Winton
Project: Computer Vision Homework 4
File:    s1.cc
Purpose: Locates sphere in an image and computes its center and radius 
*/
#include "image.h"
#include <cstdio>
#include <iostream>
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
  const string input_threshold(argv[2]);
  const string output_parameters_file(argv[3]);

  Image an_image;
  if (!ReadImage(input_image_file, &an_image))
  {
    cout << "Can't open file " << input_image_file << endl;
    return 0;
  }

  // write parameters to file
}
