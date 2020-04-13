
/*
Author:  Josh Winton
Project: Computer Vision Homework 4
File:    s3.cc
Purpose: Calculates surface normals and albedo using 3 images under different lighting conditions
*/

#include "image.h"
#include "sphere.h"
#include "matrixUtils.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// #include <algorithm>
// #include <iterator>
#include <vector>
#include <array>

using namespace std;
using namespace ComputerVisionProjects;

array<int, 3> makeArrayFromString(string vector_string)
{
  array<int, 3> vector_array;
  istringstream ss(vector_string);

  for (size_t i = 0; i < 3; i++)
  {
    string word;
    ss >> word;
    if (word == "")
    {
      break;
    }
    vector_array[i] = stoi(word);
  }

  return vector_array;
}

int main(int argc, char **argv)
{

  if (argc != 8)
  {
    printf("Usage: %s [input directions] [image 1] [image 2] [image 3] [step] [threshold] [output]\n", argv[0]);
    return 0;
  }
  const string input_directions_filename(argv[1]);
  const string image_1_filename(argv[2]);
  const string image_2_filename(argv[3]);
  const string image_3_filename(argv[4]);
  const int step(stoi(argv[5]));
  const int threshold(stoi(argv[6]));
  const string output_filename(argv[7]);

  printf("input_directions_filename: \"%s\"\n", input_directions_filename.c_str());
  printf("image_1_filename: \"%s\"\n", image_1_filename.c_str());
  printf("image_2_filename: \"%s\"\n", image_2_filename.c_str());
  printf("image_3_filename: \"%s\"\n", image_3_filename.c_str());
  printf("step: %i\n", step);
  printf("threshold: %i\n", threshold);
  printf("output_filename: \"%s\"\n", output_filename.c_str());

  // Read light source directions from file
  array<int, 3> s1;          // lighting direction 1
  array<int, 3> s2;          // lighting direction 2
  array<int, 3> s3;          // lighting direction 2
  array<array<int, 3>, 3> S; // [s1, s2, s3]

  string line;
  ifstream input_directions_file(input_directions_filename);
  if (input_directions_file.is_open())
  {
    getline(input_directions_file, line);
    s1 = makeArrayFromString(line);

    getline(input_directions_file, line);
    s2 = makeArrayFromString(line);

    getline(input_directions_file, line);
    s3 = makeArrayFromString(line);

    input_directions_file.close();
  }
  else
  {
    printf("Unable to open file \"%s\"", input_directions_filename.c_str());
  }

  // Create matrix S
  S[0] = s1;
  S[1] = s2;
  S[2] = s3;

  array<array<double, 3>, 3> S_inverse;

  // Find S inverse
  if (!inverse(S, S_inverse))
  {
    cout << "singular" << endl;
    return 1;
  }

  // Read image files into Image objects
  Image image1;
  Image image2;
  Image image3;

  ReadImage(image_1_filename, &image1);
  ReadImage(image_2_filename, &image2);
  ReadImage(image_3_filename, &image3);

  // Generate 3D object

  // Write 3D object with normals to image

  return 0;
}
