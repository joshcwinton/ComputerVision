/* 
Author:  Josh Winton
Project: Computer Vision Homework 4
File:    s1.cc
Purpose: Locates sphere in an image and computes its center and radius 
*/
#include "image.h"
#include "sphere.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// #include <algorithm>
// #include <iterator>
#include <vector>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv)
{

  if (argc != 6)
  {
    printf("Usage: %s [input parameters file] [image 1] [image 2] [image 3] [output directions file]\n", argv[0]);
    return 0;
  }
  const string input_parameters_file(argv[1]);
  const string image_1_file(argv[2]);
  const string image_2_file(argv[3]);
  const string image_3_file(argv[4]);
  const string output_directions_file(argv[5]);

  printf("input_parameters_file: \"%s\".\n", input_parameters_file.c_str());
  printf("image_1_file: \"%s\".\n", image_1_file.c_str());
  printf("image_2_file: \"%s\".\n", image_2_file.c_str());
  printf("image_3_file: \"%s\".\n", image_3_file.c_str());
  printf("output_directions_file: \"%s\".\n", output_directions_file.c_str());

  // Read parameters
  int sphere_x_center;
  int sphere_y_center;
  int radius;
  string line;

  ifstream input_parameters(input_parameters_file);
  if (input_parameters.is_open())
  {
    getline(input_parameters, line);
    istringstream iss(line);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    sphere_x_center = stoi(tokens[0]);
    sphere_y_center = stoi(tokens[1]);
    radius = stoi(tokens[2]);
  }
  else
  {
    cout << "Can't open parameters file";
    return 0;
  }

  // Read images into sphere objects
  Sphere sphere1;
  Sphere sphere2;
  Sphere sphere3;

  if (!ReadImage(image_1_file, &sphere1))
  {
    cout << "Can't open file " << image_1_file << endl;
    return 0;
  }

  if (!ReadImage(image_2_file, &sphere2))
  {
    cout << "Can't open file " << image_2_file << endl;
    return 0;
  }

  if (!ReadImage(image_3_file, &sphere3))
  {
    cout << "Can't open file " << image_3_file << endl;
    return 0;
  }

  // calculate output
  vector<double> normal1 = sphere1.GetNormal(sphere_x_center, sphere_y_center, radius);
  vector<double> normal2 = sphere2.GetNormal(sphere_x_center, sphere_y_center, radius);
  vector<double> normal3 = sphere3.GetNormal(sphere_x_center, sphere_y_center, radius);

  return 0;
}
