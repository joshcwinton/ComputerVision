// Class for storing database information for labeled binary image
// Written by Joshua Winton for CSCI 49369 at Hunter College

#ifndef COMPUTER_VISION_DATABASE_H_
#define COMPUTER_VISION_DATABASE_H_

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "image.h"
#include "Object.h"

using namespace std;

typedef class ComputerVisionProjects::ObjectData object;

namespace ComputerVisionProjects
{
class Database
{
private:
  // Holds strings, each string corresponds to the characteristics of an object
  vector<string> DatabaseData;

  // Stores vectors of pixel pairs corresponding to a label
  unordered_map<int, vector<pair<int, int>>> objectMap;

  // Maps label to center of object
  unordered_map<int, pair<int, int>> centers;

  // Maps labels to [a, b, c]
  unordered_map<int, vector<int>> minimumMoments;

  // Maps labels to areas
  unordered_map<int, int> areas;

  // Maps labels to theta that gives orientation
  unordered_map<int, double> thetas;

  // copy of pointer to image
  const Image *an_image;

public:
  // ~Database();
  Database(const Image *labeled_image);

  // Looks for objects labeled by color in labeled_image and inserts all
  // pixels matching a label into a hash table indexed by label, objectMap
  void BuildObjectMapFromLabeledImage(const Image *labeled_image);

  // Prints final output, all data for each object
  // Attributes separated by spaces, objects separated by lines
  // void PrintDatabaseData();

  // Returns vector with all labels from image
  vector<int> GetAllLabels()
  {
    vector<int> labels;

    unordered_map<int, vector<pair<int, int>>>::iterator it = objectMap.begin();

    while (it != objectMap.end())
    {
      labels.push_back(it->first);
      it++;
    }
    return labels;
  };

  void PrintAllLabels()
  {
    vector<int> labels = GetAllLabels();
    cout << "Labels:" << endl;
    for (int label : labels)
      cout << label << endl;
  }

  // Takes a label and a map from labels to pixels
  // Computes average row value of all pixels in object
  int GetAverageRowOfObject(int label);

  // Takes a label and a map from labels to pixels
  // Computes average column value of all pixels in object
  int GetAverageColumnOfObject(int label);

  // Builds centers map using object map
  void GetAllCentersFromObjectMap();

  // Builds map from label to a vector containing (a, b, c)
  void GetMinimumMomentsOfInertia();

  // Builds map from label to orientation as represented by theta
  void GetThetas();

  // Output database info
  void PrintDatabase();

  // Write db info to text file
  void WriteDatabaseToFile(string database_file);

  // Update image with database info
  void DrawOnImage(Image *an_image);

  // Given an image and a set of labels, draw lines on image only for those labels
  void DrawSelectedLabelsOnImage(Image *an_image, vector<int> labels);

  double GetRoundnessByLabel(int label);

  size_t num_objects() const
  {
    return objectMap.bucket_count();
  };
};

// namespace ComputerVisionProjects
} // namespace ComputerVisionProjects

#endif // COMPUTER_VISION_DATABASE_H