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

  // Initialize hough array + image
  int max_rho = sqrt(pow(an_image.num_rows(), 2) + pow(an_image.num_columns(), 2));
  double max_theta = M_PI;
  int d_rho = 2;
  int d_theta = M_PI / 180; // 1 degree

  // how many samples for rho and theta
  int rho_buckets = max_rho / d_rho;
  int theta_buckets = 180;

  // create accumulator array
  int hough_array[rho_buckets][theta_buckets];

  // Set A(k, h) to zero everywhere in A
  for (int i = 0; i < rho_buckets; i++)
  {
    for (int j = 0; j < theta_buckets; j++)
    {
      hough_array[i][j] = 0;
    }
  }

  // For all pixels (i, j) such that E(i, j) is 1
  for (int i = 0; i < an_image.num_rows(); i++)
  {
    for (int j = 0; j < an_image.num_columns(); j++)
    {
      if (an_image.GetPixel(i, j) >= 1)
      {
        // fill in
      }
    }
  }

  // Draw array as image
  hough_image.AllocateSpaceAndSetSize(rho_buckets, theta_buckets);

  int max_votes = 1;

  for (int i = 0; i < rho_buckets; i++)
  {
    for (int j = 0; j < theta_buckets; j++)
    {
      if (hough_array[i][j] > max_votes)
      {
        max_votes = hough_array[i][j];
      }
    }
  }

  for (int i = 0; i < rho_buckets; i++)
  {
    for (int j = 0; j < theta_buckets; j++)
    {
      int t = hough_array[i][j];
      hough_image.SetPixel(i, j, t);
    }
  }

  hough_image.SetNumberGrayLevels(255);

  if (!WriteImage(output_hough_image, hough_image))
  {
    cout << "Can't write to file " << output_hough_image << endl;
    return 0;
  }
}
