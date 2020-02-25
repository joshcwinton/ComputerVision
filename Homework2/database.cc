// Class for storing database information for labeled binary image
// Written by Joshua Winton for CSCI 49369 at Hunter College

#include "database.h"
#include <iostream>
#include <cmath>

using namespace std;

size_t THRESHOLD_SIZE = 20;

namespace ComputerVisionProjects
{

Database::Database(const Image *labeled_image)
{
  an_image = labeled_image;

  BuildObjectMapFromLabeledImage(labeled_image);

  GetAllCentersFromObjectMap();

  GetMinimumMomentsOfInertia();

  GetThetas();
  // GetAreas();
}

void Database::BuildObjectMapFromLabeledImage(const Image *labeled_image)
{
  cout << "Building database..." << endl;
  // Search for objects, first foreground pixel is first object
  cout << "columns: " << labeled_image->num_columns() << " rows: " << labeled_image->num_rows() << endl;

  for (size_t i = 0; i < labeled_image->num_rows(); i++)
  {
    for (size_t j = 0; j < labeled_image->num_columns(); j++)
    {
      int current_label = labeled_image->GetPixel(i, j);
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

  // Now each hash table entry corresponds to an object

  // Remove objects with less than THRESHOLD_SIZE pixels
  for (auto it = objectMap.begin(); it != objectMap.end();)
  {
    if (it->second.size() < THRESHOLD_SIZE)
    {
      objectMap.erase(it++);
    }
    else
    {
      ++it;
    }
  }

  cout << endl;
}

int Database::GetAverageRowOfObject(int label)
{
  vector<pair<int, int>> objectPixels = objectMap[label];
  int num_pixels = objectPixels.size();
  int row_sum = 0;

  for (int i = 0; i < num_pixels; i++)
  {
    row_sum += objectPixels[i].first;
  }

  return row_sum / num_pixels;
}

int Database::GetAverageColumnOfObject(int label)
{
  vector<pair<int, int>> objectPixels = objectMap[label];
  int num_pixels = objectPixels.size();
  int col_sum = 0;

  for (int i = 0; i < num_pixels; i++)
  {
    col_sum += objectPixels[i].second;
  }

  return col_sum / num_pixels;
}

void Database::GetAllCentersFromObjectMap()
{
  cout << "Getting centers..." << endl;
  vector<int> labels = GetAllLabels();
  for (int label : labels)
  {
    int avg_row = GetAverageRowOfObject(label);
    int avg_col = GetAverageColumnOfObject(label);
    pair<int, int> center(avg_row, avg_col);
    centers[label] = center;
    cout << "Label: " << label << " Center: " << avg_row << ", " << avg_col << endl;
  }
  cout << endl;
}

void Database::GetMinimumMomentsOfInertia()
{
  cout << "Getting minimum moments of inertia..." << endl;

  vector<int> labels = GetAllLabels();

  for (int label : labels)
  {
    cout << "label: " << label << endl;

    pair<int, int> center = centers[label];

    int a = 0;
    int b = 0;
    int c = 0;

    // loop over all pixels under that label and update abc
    for (pair<int, int> pixel : objectMap[label])
    {

      a += (pixel.first - center.first) * (pixel.first - center.first);
      b += (pixel.first - center.first) * (pixel.second - center.second);
      c += (pixel.second - center.second) * (pixel.second - center.second);
    }

    b *= 2;

    if (minimumMoments[label].size() == 0)
    {
      cout << a << " " << b << " " << c << endl;
      minimumMoments[label].push_back(a);
      minimumMoments[label].push_back(b);
      minimumMoments[label].push_back(c);
    }
    else
    {
      abort();
    }
  }

  cout << endl;
}

void Database::GetThetas()
{
  cout << "Calculating orientations..." << endl;

  vector<int> labels = GetAllLabels();
  for (int label : labels)
  {
    double theta;

    vector<int> sums = minimumMoments[label];

    int a = sums[0];
    int b = sums[1];
    int c = sums[2];

    theta = 0.5 * atan(b / (a - c));

    thetas[label] = -theta;
  }

  cout << endl;
}

} // namespace ComputerVisionProjects
