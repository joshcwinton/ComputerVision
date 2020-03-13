// Definitions of utilities for finding lines
// in an image from its Hough transform.
// Written for Computer Vision Homework 3

#include "houghUtils.h"
#include "image.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

namespace ComputerVisionProjects
{

// Takes a hough transform array file generated in h3
// Writes the array to result_array
void ReadHoughArrayFromTextFile(string hough_array_file, vector<vector<int>> *result_array)
{
  string line;
  ifstream textfile(hough_array_file);
  if (textfile.is_open())
  {
    getline(textfile, line);

    cout << "array dimensions: " << line << endl;

    while (getline(textfile, line))
    {
      vector<int> t;
      t = StringToVectorOfInts(line);
      result_array->push_back(t);
    }

    textfile.close();
  }
  else
  {
    cout << "Unable to open file";
    abort();
  }
}

vector<int> StringToVectorOfInts(string line)
{
  stringstream ss(line);
  istream_iterator<string> begin(ss);
  istream_iterator<string> end;
  vector<string> vstrings(begin, end);
  vector<int> result;
  for (int i = 0; i < vstrings.size(); i++)
  {
    result.push_back(stoi(vstrings[i]));
  }
  return result;
}

// Only for testing, writes hough array to an output image
void WriteHoughArrayToImage(vector<vector<int>> hough_array, string output_file)
{
  // Create image to be written to file
  int rows = hough_array.size();
  int columns = hough_array[0].size();

  Image an_image;

  an_image.AllocateSpaceAndSetSize(rows, columns);

  // Loop through rows and columns of hough_array and get max_votes
  int max_votes = 0;

  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < columns; j++)
    {
      if (hough_array[i][j] > max_votes)
      {
        max_votes = hough_array[i][j];
      }
    }
  }

  // Set each pixel based on value of hough array scaled to range from 0 to 255 using max votes
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < columns; j++)
    {

      double brightness = hough_array[i][j] / (double)max_votes * 255;
      an_image.SetPixel(i, j, brightness);
    }
  }

  // write image to output_file
  an_image.SetNumberGrayLevels(255);
  WriteImage(output_file, an_image);

  printf("Debug image written to: %s \n", output_file.c_str());
}

// Takes a hough space and a threshold, only indices with more votes than the threshold kept
void ThresholdHoughSpace(vector<vector<int>> &hough_array, int threshold)
{
  int rows = hough_array.size();
  int columns = hough_array[0].size();

  // loop through hough space
  // if entry < threshold, set it to 0
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < columns; j++)
    {
      if (hough_array[i][j] < threshold)
      {
        hough_array[i][j] = 0;
      }
    }
  }
}

} // namespace ComputerVisionProjects