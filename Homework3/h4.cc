/* 
Author: Josh Winton
Project: Computer Vision Homework 3
File: h3.cc
Purpose: ??
*/

#define _USE_MATH_DEFINES

#include "image.h"
#include "houghUtils.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv)
{

  if (argc != 5)
  {
    printf("Usage: %s [input-original-gray-level-image] [input-hough-voting-array] [input-hough-threshold-value] [output-gray-level-line-image]\n", argv[0]);
    return 0;
  }
  const string input_original_image(argv[1]);
  const string input_hough_array(argv[2]);
  const int hough_threshold(stoi(argv[3]));
  const string output_line_image(argv[4]);

  Image an_image;

  if (!ReadImage(input_original_image, &an_image))
  {
    cout << "Can't open file " << input_original_image << endl;
    return 0;
  }

  cout << "input_original_image:\t" << input_original_image << endl;
  cout << "input_hough_array:\t" << input_hough_array << endl;
  cout << "hough_threshold:\t" << hough_threshold << endl;
  cout << "output_line_image:\t" << output_line_image << endl;

  // Read Hough space into array from file
  vector<vector<int>> hough_array;
  ReadHoughArrayFromTextFile(input_hough_array, &hough_array);

  ThresholdHoughSpace(hough_array, hough_threshold);

  WriteHoughArrayToImage(hough_array);

  if (!WriteImage(output_line_image, an_image))
  {
    cout << "Can't write to file " << output_line_image << endl;
    return 0;
  }
}
