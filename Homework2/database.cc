// Class for storing database information for labeled binary image
// Written by Joshua Winton for CSCI 49369 at Hunter College

#include "database.h"
#include <iostream>

using namespace std;

size_t THRESHOLD_SIZE = 20;

namespace ComputerVisionProjects
{

Database::Database(const Image *labeled_image)
{
  BuildObjectMapFromLabeledImage(labeled_image);
}

void Database::BuildObjectMapFromLabeledImage(const Image *labeled_image)
{
  cout << "building database" << endl;
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
}
} // namespace ComputerVisionProjects
