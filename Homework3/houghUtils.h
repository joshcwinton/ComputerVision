// Utilities for finding lines in an image from its Hough space
// Written for Computer Vision Homework 3

#ifndef COMPUTER_VISION_HOUGH_UTILS_H_
#define COMPUTER_VISION_HOUGH_UTILS_H_

#include <string>
#include <vector>

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

// Takes a hough space and returns a vector of (rho, theta) pairs
vector<pair<int, int>> LocateCenters(vector<vector<int>> hough_array);

// Takes image dimensions x and y
// Returns a vector of pairs of points (which are also pairs)
vector<pair<pair<int, int>, pair<int, int>>> ConvertPolarCentersToLines(int x, int y, vector<pair<int, int>>);

// Used to parse lines from hough array text file to a vector of integers
vector<int> StringToVectorOfInts(string line);

} // namespace ComputerVisionProjects

#endif // COMPUTER_VISION_HOUGH_UTILS_H_