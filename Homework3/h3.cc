/* 
Author: Josh Winton
Project: Computer Vision Homework 3
File: h3.cc
Purpose: ??
*/

#define _USE_MATH_DEFINES

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv)
{

  if (argc != 4)
  {
    printf("Usage: %s [binary edge image] [gray-level hough image] [hough voting array]\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string output_hough_image(argv[2]);
  const string output_hough_array(argv[3]); // output will be stored in a .txt (?)

  Image an_image;
  Image hough_image;

  if (!ReadImage(input_file, &an_image))
  {
    cout << "Can't open file " << input_file << endl;
    return 0;
  }

  an_image.GenerateHoughImageAndFile(hough_image, output_hough_array);

  if (!WriteImage(output_hough_image, hough_image))
  {
    cout << "Can't write to file " << output_hough_image << endl;
    return 0;
  }
}
