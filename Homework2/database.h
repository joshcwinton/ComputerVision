// Class for storing database information for labeled binary image
// Written by Joshua Winton for CSCI 49369 at Hunter College

#ifndef COMPUTER_VISION_DATABASE_H_
#define COMPUTER_VISION_DATABASE_H_

#include "image.h"

namespace ComputerVisionProjects {
class Database {
public:
  ~Database();
  Database(const Image &labeled_image);

  vector<ObjectData> DatabaseData;

  void BuildDatabaseFromLabeledImage(const Image &labeled_image);
  void PrintDatabaseData();

  size_t num_objects() const { return num_objects_; }

private:
  size_t num_objects_;
}
} // namespace ComputerVisionProjects
