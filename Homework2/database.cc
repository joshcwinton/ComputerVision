// Class for storing database information for labeled binary image
// Written by Joshua Winton for CSCI 49369 at Hunter College

#include "database.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define THRESHOLD_SIZE 20
#define PI 3.14159265

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
  // Search for objects, first foreground pixel is first object
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
  vector<int> labels = GetAllLabels();
  for (int label : labels)
  {
    int avg_row = GetAverageRowOfObject(label);
    int avg_col = GetAverageColumnOfObject(label);
    pair<int, int> center(avg_row, avg_col);
    centers[label] = center;
  }
}

void Database::GetMinimumMomentsOfInertia()
{
  vector<int> labels = GetAllLabels();

  for (int label : labels)
  {
    pair<int, int> center = centers[label];

    int count = 0;
    int a = 0;
    int b = 0;
    int c = 0;

    // loop over all pixels under that label and update abc
    for (pair<int, int> pixel : objectMap[label])
    {
      count++;
      a += (pixel.second - center.second) * (pixel.second - center.second);
      b += (pixel.first - center.first) * (pixel.second - center.second);
      c += (pixel.first - center.first) * (pixel.first - center.first);
    }

    b *= 2;

    if (minimumMoments.find(label) == minimumMoments.end())
    {
      vector<int> temp;
      temp.push_back(a);
      temp.push_back(b);
      temp.push_back(c);
      minimumMoments[label] = temp;
    }
    else
    {
      minimumMoments[label].push_back(a);
      minimumMoments[label].push_back(b);
      minimumMoments[label].push_back(c);
    }
  }
}

void Database::GetThetas()
{
  vector<int> labels = GetAllLabels();
  for (int label : labels)
  {
    double theta;

    vector<int> sums = minimumMoments[label];

    double a = sums[0];
    double b = sums[1];
    double c = sums[2];

    theta = 0.5 * atan2(b, (a - c));

    thetas[label] = -theta;
  }
}

// {label}{row center}{column center}{minimum moment of inertia}{orientation}
void Database::PrintDatabase()
{
  vector<int> labels = GetAllLabels();

  cout << "label\t"
       << "row\t"
       << "column\t"
       << "E\t"
       << "theta" << endl;

  for (int label : labels)
  {
    // object label
    cout << label << "\t";

    // row center
    cout << centers[label].first << "\t";

    // column center
    cout << centers[label].second << "\t";

    // minimum moment of inertia
    int a = minimumMoments[label][0];
    int b = minimumMoments[label][1];
    int c = minimumMoments[label][2];
    int t = thetas[label];
    int E = (a * pow(sin(t), 2)) - (b * sin(t) * cos(t)) + (c * pow(cos(t), 2));
    cout << E << "\t";
    // orientation
    cout << thetas[label];

    cout << endl;
  }
}

void Database::DrawOnImage(Image *an_image)
{
  vector<int> labels = GetAllLabels();

  int color = an_image->num_gray_levels();
  an_image->SetNumberGrayLevels(color + 1);

  for (int label : labels)
  {
    // get center of object
    pair<int, int> center = centers[label];
    // get slope
    double slope = tan(-thetas[label]);
    // get endpoint for slope
    pair<int, int> endpoint(center.first + (slope * 10), center.second + 10);
    // draw line
    if ((endpoint.first > an_image->num_rows()) || (endpoint.second > an_image->num_columns()))
    {
      abort();
    }
    else
    {
      DrawLine(center.first, center.second, endpoint.first, endpoint.second, color, an_image);
    }
  }
}

// Write db info to text file
void Database::WriteDatabaseToFile(string database_file)
{
  ofstream dbfile;
  dbfile.open(database_file);

  vector<int> labels = GetAllLabels();

  dbfile << "label\t"
         << "row\t"
         << "column\t"
         << "E\t"
         << "theta" << endl;

  for (int label : labels)
  {
    // object label
    dbfile << label << "\t";

    // row center
    dbfile << centers[label].first << "\t";

    // column center
    dbfile << centers[label].second << "\t";

    // minimum moment of inertia
    int a = minimumMoments[label][0];
    int b = minimumMoments[label][1];
    int c = minimumMoments[label][2];
    int t = thetas[label];
    int E = (a * pow(sin(t), 2)) - (b * sin(t) * cos(t)) + (c * pow(cos(t), 2));
    dbfile << E << "\t";
    // orientation
    dbfile << thetas[label];

    dbfile << endl;
  }

  dbfile.close();
}

double Database::GetRoundnessByLabel(int label)
{
  int a = minimumMoments[label][0];
  int b = minimumMoments[label][1];
  int c = minimumMoments[label][2];
  int min_theta = thetas[label];
  int max_theta = min_theta + (PI / 2);
  double E_min = (a * pow(sin(min_theta), 2)) - (b * sin(min_theta) * cos(min_theta)) + (c * pow(cos(min_theta), 2));
  double E_max = (a * pow(sin(max_theta), 2)) - (b * sin(max_theta) * cos(max_theta)) + (c * pow(cos(max_theta), 2));
  double roundness = E_min / E_max;
  return roundness;
}

} // namespace ComputerVisionProjects
