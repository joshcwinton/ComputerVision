// Utilities for finding lines in an image from its Hough space
// Written for Computer Vision Homework 3

#ifndef COMPUTER_VISION_HOUGH_UTILS_H_
#define COMPUTER_VISION_HOUGH_UTILS_H_

#include "image.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

namespace ComputerVisionProjects
{

// Takes a hough transform array file generated in h3
// Writes the array to result_array
void ReadHoughArrayFromTextFile(string hough_array_file, vector<vector<int>> *result_array);

// Only for testing, writes hough array to an output image
void WriteHoughArrayToImage(vector<vector<int>> hough_array, string output_file = "debugging.pgm");

// Takes a hough space and a threshold, only indices with more votes than the threshold kept
void ThresholdHoughSpace(vector<vector<int>> &hough_array, int threshold);

// Takes a hough space and a map from labels to objects and returns a vector of (rho, theta) pairs
vector<pair<int, int>> GetCentersFromHoughArrayAndLabels(vector<vector<int>> &hough_array, unordered_map<int, vector<pair<int, int>>> &objectMap);

// Takes image dimensions x and y
// Returns a vector of (x1, y1, x2, y2) lines
vector<vector<int>> ConvertPolarCentersToLines(vector<pair<int, int>> centers, int rows, int columns);

// Used to parse lines from hough array text file to a vector of integers
vector<int> StringToVectorOfInts(string line);

// Given a hough array, segment it and return a 2d array of labeled buckets
vector<vector<int>> GenerateLabelArray(vector<vector<int>> const &hough_array);

// Given a labeled array for a hough array
// Create a map from a label to a vector of its points
void BuildObjectMapFromLabeledArray(const vector<vector<int>> &hough_array, unordered_map<int, vector<pair<int, int>>> &objectMap);

void DrawLinesFromVector(vector<vector<int>> lines, Image &an_image);

} // namespace ComputerVisionProjects

#endif // COMPUTER_VISION_HOUGH_UTILS_H_