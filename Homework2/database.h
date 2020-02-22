// Class for storing database information for labeled binary image
// Written by Joshua Winton for CSCI 49369 at Hunter College

#ifndef COMPUTER_VISION_DATABASE_H_
#define COMPUTER_VISION_DATABASE_H_

#include <string>
#include <vector>
#include <unordered_map>
#include "image.h"
#include "Object.h"

using namespace std;

typedef class ComputerVisionProjects::ObjectData object;

namespace ComputerVisionProjects
{
class Database
{
public:
  // ~Database();
  Database(const Image *labeled_image);

  // Holds strings, each string corresponds to the characteristics of an object
  vector<string> DatabaseData;

  // Stores vectors of pixel pairs corresponding to a label
  unordered_map<int, vector<pair<int, int>>> objectMap;

  // Looks for objects labeled by color in labeled_image and inserts all
  // pixels matching a label into a hash table indexed by label, objectMap
  void BuildObjectMapFromLabeledImage(const Image *labeled_image);

  // Prints final output, all data for each object
  // Attributes separated by spaces, objects separated by lines
  // void PrintDatabaseData();

  size_t num_objects() const
  {
    return objectMap.bucket_count();
  };
};

// Takes a label and a map from labels to pixels
// Computes
int GetAverageRowOfObject(const int label, const unordered_map<int, vector<pair<int, int>>> objectMap);

} // namespace ComputerVisionProjects

#endif // COMPUTER_VISION_DATABASE_H