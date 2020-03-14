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
#include <unordered_map>

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

  // Threshold hough array using hough_threshold
  ThresholdHoughSpace(hough_array, hough_threshold);

  // Create a labeled array
  vector<vector<int>> label_array = GenerateLabelArray(hough_array);

  // Create a map from each label to a vector of points that correspond to that label
  unordered_map<int, vector<pair<int, int>>> objectMap;
  BuildObjectMapFromLabeledArray(label_array, objectMap);

  // DEBUGGING: PRINT OPJECT MAP
  /*   for (auto pair : objectMap)
  {
    cout << pair.first << " ";
    for (auto const item : pair.second)
    {
      cout << "{" << item.first << ":" << item.second << "}";
    }
    cout << endl;
  } */

  // For each list of points, calculate its center and keep a list of centers
  vector<pair<int, int>> centers = GetCentersFromHoughArrayAndLabels(hough_array, objectMap);

  // Convert a (rho, theta) pair to a (x1, y1, x2, y2) list of points given image dimensions;
  vector<vector<int>> lines = ConvertPolarCentersToLines(centers, an_image.num_rows(), an_image.num_columns());

  // For each center draw a line on original image
  DrawLinesFromVector(lines, an_image);

  WriteHoughArrayToImage(hough_array);
  WriteHoughArrayToImage(label_array, "labels.pgm");

  if (!WriteImage(output_line_image, an_image))
  {
    cout << "Can't write to file " << output_line_image << endl;
    return 0;
  }
}
