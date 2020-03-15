// Josh Winton
// Definitions of utilities for finding lines
// in an image from its Hough transform.
// Written for Computer Vision Homework 3

#include "houghUtils.h"
#include "image.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <iterator>
#include <cmath>

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
    cout << "Unable to open file: " << hough_array_file;
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

vector<vector<int>> GenerateLabelArray(vector<vector<int>> const &hough_array)
{
  int current_label = 1;
  int rows = hough_array.size();
  int columns = hough_array[0].size();
  vector<vector<int>> labels;
  queue<pair<int, int>> label_queue;

  // initialize label vector
  for (size_t i = 0; i < rows; i++)
  {
    vector<int> temp;
    temp.resize(columns, -1);
    labels.push_back(temp);
  }

  // set labels
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < columns; j++)
    {
      size_t current_val = hough_array[i][j];

      // if a bucket has votes and not already labeled
      if ((current_val > 0) && (labels[i][j] == -1))
      {
        // give it current label and add it as the first element in a queue
        labels[i][j] = current_label;
        pair<int, int> pixel(i, j);
        label_queue.push(pixel);
      }
      // background pixel or already labeled
      else
      {
        // go to next pixel
        continue;
      }

      // pop element from queue and look at its neighbors

      while (!label_queue.empty())
      {
        pair<int, int> queue_pixel(label_queue.front());
        label_queue.pop();

        int up;
        int down;
        int left;
        int right;

        // check for up
        if (queue_pixel.first > 0)
        {
          up = hough_array[queue_pixel.first - 1][queue_pixel.second];
          if ((up > 0) &&
              (labels[queue_pixel.first - 1][queue_pixel.second] == -1))
          {
            labels[queue_pixel.first - 1][queue_pixel.second] = current_label;
            pair<int, int> pixel(queue_pixel.first - 1, queue_pixel.second);
            label_queue.push(pixel);
          }
        }

        // check for down
        if (queue_pixel.first < rows - 1)
        {
          down = hough_array[queue_pixel.first + 1][queue_pixel.second];
          if ((down > 0) &&
              (labels[queue_pixel.first + 1][queue_pixel.second] == -1))
          {
            labels[queue_pixel.first + 1][queue_pixel.second] = current_label;
            pair<int, int> pixel(queue_pixel.first + 1, queue_pixel.second);
            label_queue.push(pixel);
          }
        }

        // check for left
        if (queue_pixel.second > 0)
        {
          left = hough_array[queue_pixel.first][queue_pixel.second - 1];
          if ((left > 0) &&
              (labels[queue_pixel.first][queue_pixel.second - 1] == -1))
          {
            labels[queue_pixel.first][queue_pixel.second - 1] = current_label;
            pair<int, int> pixel(queue_pixel.first, queue_pixel.second - 1);
            label_queue.push(pixel);
          }
        }

        // check for right
        if (queue_pixel.second < columns - 1)
        {
          right = hough_array[queue_pixel.first][queue_pixel.second + 1];
          if ((right > 0) &&
              (labels[queue_pixel.first][queue_pixel.second + 1] == -1))
          {
            labels[queue_pixel.first][queue_pixel.second + 1] = current_label;
            pair<int, int> pixel(queue_pixel.first, queue_pixel.second + 1);
            label_queue.push(pixel);
          }
        }
      }
      current_label++;
    }
  }
  return labels;
}

// Given a labeled array for a hough array
// Create a map from a label to a vector of its points
void BuildObjectMapFromLabeledArray(const vector<vector<int>> &hough_array, unordered_map<int, vector<pair<int, int>>> &objectMap)
{
  // Search for objects, first bucket with vote is first object
  for (size_t i = 0; i < hough_array.size(); i++)
  {
    for (size_t j = 0; j < hough_array[i].size(); j++)
    {
      int current_label = hough_array[i][j];
      pair<int, int> pixel(i, j);

      // If label in hash table, add this pixel to its row
      if (current_label > 0)
      {
        if (objectMap.find(current_label) == objectMap.end())
        {
          vector<pair<int, int>> temp;
          temp.push_back(pixel);
          objectMap[current_label] = temp;
        }
        else
        {
          objectMap[current_label].push_back(pixel);
        }
      }
    }
  }
}

vector<pair<int, int>> GetCentersFromHoughArrayAndLabels(vector<vector<int>> &hough_array, unordered_map<int, vector<pair<int, int>>> &objectMap)
{
  vector<pair<int, int>> centers;
  vector<int> labels;

  // initialize list of labels
  for (auto pair : objectMap)
  {
    labels.push_back(pair.first);
  }

  // for each label, get weighted sum of its pixels

  for (auto pair : objectMap)
  {
    int rho_sum = 0;
    int theta_sum = 0;
    int num_votes = 0;

    // for each pixel, add its position to rho and theta once for each vote
    for (auto pixel : pair.second)
    {
      int rho = pixel.first;
      int theta = pixel.second;
      int votes = hough_array[rho][theta];

      num_votes += votes;
      rho_sum += (votes * rho);
      theta_sum += (votes * theta);
    }

    int avg_rho = rho_sum / num_votes;
    int avg_theta = theta_sum / num_votes;

    std::pair<int, int> center(avg_rho, avg_theta);
    centers.push_back(center);
  }
  return centers;
}

// Takes image dimensions x and y
// Returns a vector of (x1, y1, x2, y2) lines
vector<vector<int>> ConvertPolarCentersToLines(vector<pair<int, int>> centers, int rows, int columns)
{
  vector<vector<int>> lines;
  // for each center (rho, theta) determine which image boundaries it intersects
  for (auto center : centers)
  {
    // scale rho and theta
    double rho = center.first / (double)2;
    double theta = center.second * M_PI / (double)360;

    vector<int> line;
    double a = cos(theta), b = sin(theta);
    double x0 = a * rho, y0 = b * rho;
    int x1 = x0 + 1000 * (-b);
    int y1 = y0 + 1000 * (a);
    int x2 = x0 - 1000 * (-b);
    int y2 = y0 - 1000 * (a);
    line.push_back(x1);
    line.push_back(y1);
    line.push_back(x2);
    line.push_back(y2);
    lines.push_back(line);
  }

  return lines;
}

void DrawLinesFromVector(vector<vector<int>> lines, Image &an_image)
{
  for (size_t i = 0; i < lines.size(); i++)
  {
    DrawLine(lines[i][0], lines[i][1], lines[i][2], lines[i][3], 125, &an_image);
  }
}

} // namespace ComputerVisionProjects
