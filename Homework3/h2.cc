/* 
Author: Josh Winton
Project: Computer Vision Homework 3
File: h2.cc
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
    printf("Usage: %s file1 threshold file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const int threshold(stoi(argv[2]));
  const string output_file(argv[3]);

  Image an_image;
  if (!ReadImage(input_file, &an_image))
  {
    cout << "Can't open file " << input_file << endl;
    return 0;
  }

  // Set all pixels with value above "threshold" to max value
  // Set all pixels with value below "threshold" to min value
  ConvertGrayScaleToBinary(&an_image, threshold);

  if (!WriteImage(output_file, an_image))
  {
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}
