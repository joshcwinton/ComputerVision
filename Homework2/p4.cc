// Segments a binary into several connected images

#include "database.h"
#include "image.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

// used to compare objects using area
#define MAX_AREA_DIFFERENCE 200

using namespace std;
using namespace ComputerVisionProjects;

// Split string into vector where:
// 0 is label
// 1 is row
// 2 is column
// 3 is min E
// 4 is theta
// 5 is roundness
// 6 is area
vector<string> parseLine(string line)
{
  vector<string> return_vector;
  string temp_string;
  for (int i = 0; i < line.length(); i++)
  {
    if (line[i] == '\t')
    {
      return_vector.push_back(temp_string);
      temp_string = "";
    }
    else if (i == line.length() - 1)
    {
      temp_string += line[i];
      return_vector.push_back(temp_string);
      temp_string = "";
    }
    else
    {
      temp_string += line[i];
    }
  }
  return return_vector;
}

int main(int argc, char **argv)
{

  if (argc != 4)
  {
    printf("Usage: %s labeledimage inputdatabase outputimage \n", argv[0]);
    return 0;
  }
  const string labeled_image(argv[1]);
  const string input_database(argv[2]);
  const string output_file(argv[3]);

  Image an_image;
  if (!ReadImage(labeled_image, &an_image))
  {
    cout << "Can't open file " << labeled_image << endl;
    return 0;
  }

  // Create new database for new labeled image
  Database new_image_database(&an_image);

  // generate map from label to roundness for old database
  unordered_map<int, double> old_roundnesses;
  // generate map from label to area for old database
  unordered_map<int, int> old_areas;

  string line;

  ifstream dbstream(input_database);
  if (dbstream.is_open())
  {
    // skip first line of text because it's header
    getline(dbstream, line);

    while (getline(dbstream, line))
    {
      vector<string> objectInfo;
      objectInfo = parseLine(line);
      int label = stoi(objectInfo[0]);
      double roundness = stod(objectInfo[5]);
      int area = stoi(objectInfo[6]);
      old_roundnesses[label] = roundness;
      old_areas[label] = area;
    }

    dbstream.close();
  }
  else
  {
    cout << "Unable to open file";
  }

  // genrate map from label to area for old database

  // for each label in the new database
  vector<int> new_db_labels = new_image_database.GetAllLabels();
  vector<int> matches;

  for (int label : new_db_labels)
  {
    // search the old database for a label with similar area
    // after finding matching area, compare inertia
    // if both match, add to db
    int new_area = new_image_database.GetAreaByLabel(label);

    for (pair<int, double> element : old_areas)
    {
      int old_area = element.second;

      if (abs(old_area - new_area) < MAX_AREA_DIFFERENCE)
      {
        // keep list of new labels that resulted in a match
        matches.push_back(label);
      }
    }
  }

  cout << matches.size() << " matches found\n";

  // for each of those matching labels, draw on image
  new_image_database.DrawSelectedLabelsOnImage(&an_image, matches);

  if (!WriteImage(output_file, an_image))
  {
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}
