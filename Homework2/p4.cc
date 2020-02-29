// Segments a binary into several connected images

#include "database.h"
#include "image.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int getLabel(string line)
{
  string label = "";
  for (int i = 0; i < line.length(); i++)
  {
    if (line[i] == ' ')
    {
      break;
    }
    else
    {
      label += line[i];
    }
  }
  return stoi(label);
}

double getRoundness(string line)
{
  string roundness = "";
  stack<char> t;

  for (int i = line.length() - 1; i >= 0; i--)
  {
    if ((line[i] == ' ') || (line[i] == '\t'))
    {
      break;
    }
    else
    {
      t.push(line[i]);
    }
  }

  while (!t.empty())
  {
    roundness += t.top();
    t.pop();
  }

  return stod(roundness);
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
  unordered_map<int, double> old_roundness;
  string line;

  ifstream dbstream(input_database);
  if (dbstream.is_open())
  {
    // skip first line of text because it's header
    getline(dbstream, line);

    while (getline(dbstream, line))
    {
      int label = getLabel(line);
      double roundness = getRoundness(line);
      old_roundness[label] = roundness;
    }

    dbstream.close();
  }
  else
  {
    cout << "Unable to open file";
  }

  // for each label in the new database
  vector<int> new_db_labels = new_image_database.GetAllLabels();
  vector<int> matches;

  for (int label : new_db_labels)
  {
    // search the old database for a label with similar roundness
    for (pair<int, double> element : old_roundness)
    {

      if (abs(element.second - new_image_database.GetRoundnessByLabel(label)) < 0.001)
      {
        // keep list of new labels that resulted in a match
        matches.push_back(label);
      }
    }
  }

  // for each of those matching labels, draw on image
  new_image_database.DrawSelectedLabelsOnImage(&an_image, matches);

  if (!WriteImage(output_file, an_image))
  {
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}
