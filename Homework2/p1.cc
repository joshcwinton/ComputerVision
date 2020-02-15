// Converts a gray-level image to a binary one using a threshold value
// Reads a given pgm image, converts it to binary, saves another pgm image.

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

void ConvertGrayScaleToBinary(Image *an_image, int threshold)
{
  cout << an_image->GetPixel(0, 0) << endl;
  for (int i = 0; i < an_image->num_rows(); i++)
  {
    for (int j = 0; j < an_image->num_columns(); j++)
    {
      if (an_image->GetPixel(i, j) <= threshold)
      {
        an_image->SetPixel(i, j, 0);
      }
      else
      {
        an_image->SetPixel(i, j, an_image->num_gray_levels());
      }
    }
  }
}

int main(int argc, char **argv)
{

  if (argc != 4)
  {
    printf("Usage: %s file1 threshold file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const int threshold(stoi(argv[2]));
  const string output_file(argv[3]);

  Image an_image;
  if (!ReadImage(input_file, &an_image))
  {
    cout << "Can't open file " << input_file << endl;
    return 0;
  }

  // // Draw a line from (0, 0) to (100, 240) having gray-value
  // // 200.
  // DrawLine(0, 0, 100, 240, 200,
  //          &an_image);

  ConvertGrayScaleToBinary(&an_image, threshold);

  if (!WriteImage(output_file, an_image))
  {
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}
