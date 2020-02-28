// Segments a binary into several connected images

#include "database.h"
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv)
{

  if (argc != 4)
  {
    printf("Usage: %s inputimage outputdatabase outputimage\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string database_file(argv[2]);
  const string output_file(argv[3]);

  Image an_image;
  if (!ReadImage(input_file, &an_image))
  {
    cout << "Can't open file " << input_file << endl;
    return 0;
  }

  Database object_database(&an_image);

  // object_database.PrintDatabase();

  object_database.WriteDatabaseToFile(database_file);

  object_database.DrawOnImage(&an_image);

  if (!WriteImage(output_file, an_image))
  {
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}
