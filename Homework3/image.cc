// Class for representing a 2D gray-scale image,
// with support for reading/writing pgm images.
// To be used in Computer Vision class.

#include "image.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <utility>
#include <cmath>

using namespace std;

namespace ComputerVisionProjects
{

Image::Image(const Image &an_image)
{
  AllocateSpaceAndSetSize(an_image.num_rows(), an_image.num_columns());
  SetNumberGrayLevels(an_image.num_gray_levels());

  for (size_t i = 0; i < num_rows(); ++i)
    for (size_t j = 0; j < num_columns(); ++j)
    {
      SetPixel(i, j, an_image.GetPixel(i, j));
    }
}

Image::~Image() { DeallocateSpace(); }

void Image::AllocateSpaceAndSetSize(size_t num_rows, size_t num_columns)
{
  if (pixels_ != nullptr)
    DeallocateSpace();
  pixels_ = new int *[num_rows];
  for (size_t i = 0; i < num_rows; ++i)
    pixels_[i] = new int[num_columns];

  num_rows_ = num_rows;
  num_columns_ = num_columns;
}

void Image::DeallocateSpace()
{
  for (size_t i = 0; i < num_rows_; i++)
    delete pixels_[i];
  delete pixels_;
  pixels_ = nullptr;
  num_rows_ = 0;
  num_columns_ = 0;
}

bool ReadImage(const string &filename, Image *an_image)
{
  if (an_image == nullptr)
    abort();
  FILE *input = fopen(filename.c_str(), "rb");
  if (input == 0)
  {
    cout << "ReadImage: Cannot open file" << endl;
    return false;
  }

  // Check for the right "magic number".
  char line[1024];
  if (fread(line, 1, 3, input) != 3 || strncmp(line, "P5\n", 3))
  {
    fclose(input);
    cout << "ReadImage: Expected .pgm file" << endl;
    return false;
  }

  // Skip comments.
  do
    fgets(line, sizeof line, input);
  while (*line == '#');

  // Read the width and height.
  int num_columns, num_rows;
  sscanf(line, "%d %d\n", &num_columns, &num_rows);
  an_image->AllocateSpaceAndSetSize(num_rows, num_columns);

  // Read # of gray levels.
  fgets(line, sizeof line, input);
  int levels;
  sscanf(line, "%d\n", &levels);
  an_image->SetNumberGrayLevels(levels);

  // read pixel row by row.
  for (int i = 0; i < num_rows; ++i)
  {
    for (int j = 0; j < num_columns; ++j)
    {
      const int byte = fgetc(input);
      if (byte == EOF)
      {
        fclose(input);
        cout << "ReadImage: short file" << endl;
        return false;
      }
      an_image->SetPixel(i, j, byte);
    }
  }

  fclose(input);
  return true;
}

bool WriteImage(const string &filename, const Image &an_image)
{
  FILE *output = fopen(filename.c_str(), "w");
  if (output == 0)
  {
    cout << "WriteImage: cannot open file" << endl;
    return false;
  }
  const int num_rows = an_image.num_rows();
  const int num_columns = an_image.num_columns();
  const int colors = an_image.num_gray_levels();

  // Write the header.
  fprintf(output, "P5\n"); // Magic number.
  fprintf(output, "#\n");  // Empty comment.
  fprintf(output, "%d %d\n%03d\n", num_columns, num_rows, colors);

  for (int i = 0; i < num_rows; ++i)
  {
    for (int j = 0; j < num_columns; ++j)
    {
      const int byte = an_image.GetPixel(i, j);
      if (fputc(byte, output) == EOF)
      {
        fclose(output);
        cout << "WriteImage: could not write" << endl;
        return false;
      }
    }
  }

  fclose(output);
  return true;
}

// Implements the Bresenham's incremental midpoint algorithm;
// (adapted from J.D.Foley, A. van Dam, S.K.Feiner, J.F.Hughes
// "Computer Graphics. Principles and practice",
// 2nd ed., 1990, section 3.2.2);
void DrawLine(int x0, int y0, int x1, int y1, int color, Image *an_image)
{
  if (an_image == nullptr)
    abort();

#ifdef SWAP
#undef SWAP
#endif
#define SWAP(a, b) \
  {                \
    a ^= b;        \
    b ^= a;        \
    a ^= b;        \
  }

  const int DIR_X = 0;
  const int DIR_Y = 1;

  // Increments: East, North-East, South, South-East, North.
  int incrE, incrNE, incrS, incrSE, incrN;
  int d;      /* the D */
  int x, y;   /* running coordinates */
  int mpCase; /* midpoint algorithm's case */
  int done;   /* set to 1 when done */

  int xmin = x0;
  int xmax = x1;
  int ymin = y0;
  int ymax = y1;

  int dx = xmax - xmin;
  int dy = ymax - ymin;
  int dir;

  if (dx * dx > dy * dy)
  { // Horizontal scan.
    dir = DIR_X;
    if (xmax < xmin)
    {
      SWAP(xmin, xmax);
      SWAP(ymin, ymax);
    }
    dx = xmax - xmin;
    dy = ymax - ymin;

    if (dy >= 0)
    {
      mpCase = 1;
      d = 2 * dy - dx;
    }
    else
    {
      mpCase = 2;
      d = 2 * dy + dx;
    }

    incrNE = 2 * (dy - dx);
    incrE = 2 * dy;
    incrSE = 2 * (dy + dx);
  }
  else
  { // vertical scan.
    dir = DIR_Y;
    if (ymax < ymin)
    {
      SWAP(xmin, xmax);
      SWAP(ymin, ymax);
    }
    dx = xmax - xmin;
    dy = ymax - ymin;

    if (dx >= 0)
    {
      mpCase = 1;
      d = 2 * dx - dy;
    }
    else
    {
      mpCase = 2;
      d = 2 * dx + dy;
    }

    incrNE = 2 * (dx - dy);
    incrE = 2 * dx;
    incrSE = 2 * (dx + dy);
  }

  /// Start the scan.
  x = xmin;
  y = ymin;
  done = 0;

  while (!done)
  {
    an_image->SetPixel(x, y, color);

    // Move to the next point.
    switch (dir)
    {
    case DIR_X:
      if (x < xmax)
      {
        switch (mpCase)
        {
        case 1:
          if (d <= 0)
          {
            d += incrE;
            x++;
          }
          else
          {
            d += incrNE;
            x++;
            y++;
          }
          break;

        case 2:
          if (d <= 0)
          {
            d += incrSE;
            x++;
            y--;
          }
          else
          {
            d += incrE;
            x++;
          }
          break;
        }
      }
      else
      {
        done = 1;
      }
      break;

    case DIR_Y:
      if (y < ymax)
      {
        switch (mpCase)
        {
        case 1:
          if (d <= 0)
          {
            d += incrE;
            y++;
          }
          else
          {
            d += incrNE;
            y++;
            x++;
          }
          break;

        case 2:
          if (d <= 0)
          {
            d += incrSE;
            y++;
            x--;
          }
          else
          {
            d += incrE;
            y++;
          }
          break;
        } // mpCase
      }   // y < ymin
      else
      {
        done = 1;
      }
      break;
    }
  }
}

void ConvertGrayScaleToBinary(Image *an_image, int threshold)
{
  for (int i = 0; i < an_image->num_rows(); i++)
  {
    for (int j = 0; j < an_image->num_columns(); j++)
    {
      if (an_image->GetPixel(i, j) < threshold)
      {
        an_image->SetPixel(i, j, 0);
      }
      else
      {
        an_image->SetPixel(i, j, 255);
      }
    }
  }
  an_image->SetNumberGrayLevels(1);
}

// For each pixel in the image, check neighbors and based on their values, set
// new pixel value
void LabelImage(Image *an_image)
{
  int current_label = 1;
  int labels[an_image->num_rows()][an_image->num_columns()];
  queue<pair<int, int>> label_queue;

  // initialize labels
  for (int i = 0; i < an_image->num_rows(); i++)
  {
    for (int j = 0; j < an_image->num_columns(); j++)
    {
      labels[i][j] = -1;
    }
  }

  // set labels
  for (int i = 0; i < an_image->num_rows(); i++)
  {
    for (int j = 0; j < an_image->num_columns(); j++)
    {
      size_t current_val = an_image->GetPixel(i, j);

      // if foreground pixel and not already labelled
      if ((current_val > 0) && (labels[i][j] == -1))
      {
        // give it current label and add it as the first element in a queue
        labels[i][j] = current_label;
        pair<int, int> pixel(i, j);
        label_queue.push(pixel);
      }
      // background pixel or already labeled
      else
      {
        // go to next pixel
        continue;
      }

      // 3
      // pop element from queue and look at its neighbors

      while (!label_queue.empty())
      {
        pair<int, int> queue_pixel(label_queue.front());
        label_queue.pop();

        int up;
        int down;
        int left;
        int right;

        // check for up
        if (queue_pixel.first > 0)
        {
          up = an_image->GetPixel(queue_pixel.first - 1, queue_pixel.second);
          if ((up > 0) &&
              (labels[queue_pixel.first - 1][queue_pixel.second] == -1))
          {
            labels[queue_pixel.first - 1][queue_pixel.second] = current_label;
            pair<int, int> pixel(queue_pixel.first - 1, queue_pixel.second);
            label_queue.push(pixel);
          }
        }

        // check for down
        if (queue_pixel.first < an_image->num_rows() - 1)
        {
          down = an_image->GetPixel(queue_pixel.first + 1, queue_pixel.second);
          if ((down > 0) &&
              (labels[queue_pixel.first + 1][queue_pixel.second] == -1))
          {
            labels[queue_pixel.first + 1][queue_pixel.second] = current_label;
            pair<int, int> pixel(queue_pixel.first + 1, queue_pixel.second);
            label_queue.push(pixel);
          }
        }

        // check for left
        if (queue_pixel.second > 0)
        {
          left = an_image->GetPixel(queue_pixel.first, queue_pixel.second - 1);
          if ((left > 0) &&
              (labels[queue_pixel.first][queue_pixel.second - 1] == -1))
          {
            labels[queue_pixel.first][queue_pixel.second - 1] = current_label;
            pair<int, int> pixel(queue_pixel.first, queue_pixel.second - 1);
            label_queue.push(pixel);
          }
        }

        // check for right
        if (queue_pixel.second < an_image->num_columns() - 1)
        {
          right = an_image->GetPixel(queue_pixel.first, queue_pixel.second + 1);
          if ((right > 0) &&
              (labels[queue_pixel.first][queue_pixel.second + 1] == -1))
          {
            labels[queue_pixel.first][queue_pixel.second + 1] = current_label;
            pair<int, int> pixel(queue_pixel.first, queue_pixel.second + 1);
            label_queue.push(pixel);
          }
        }
      }
      current_label++;
    }
  }

  an_image->SetNumberGrayLevels(current_label);

  for (int i = 0; i < an_image->num_rows(); i++)
  {
    for (int j = 0; j < an_image->num_columns(); j++)
    {
      if (labels[i][j] == -1)
      {
        labels[i][j] = 0;
      }
      an_image->SetPixel(i, j, labels[i][j]);
    }
  }
}

void Image::ApplySquaredGradientSobelOperator()
{
  // box filter convolved with first deriv filters
  int delta1[3][3] = {
      {1, 0, -1},
      {2, 0, -2},
      {1, 0, -1}};

  int delta2[3][3] = {
      {1, 2, 1},
      {0, 0, 0},
      {-1, -2, -1}};

  // temporary storage of pixel values
  int output[num_rows()][num_columns()];

  // used to scale brightness
  int max_output = 0;

  // Apply convolution
  for (int i = 1; i < num_rows() - 1; i++)
  {
    for (int j = 1; j < num_columns() - 1; j++)
    {
      int r = GetPixel(i - 1, j - 1);
      int s = GetPixel(i - 1, j);
      int t = GetPixel(i - 1, j + 1);
      int u = GetPixel(i, j - 1);
      int v = GetPixel(i, j);
      int w = GetPixel(i, j + 1);
      int x = GetPixel(i + 1, j - 1);
      int y = GetPixel(i + 1, j);
      int z = GetPixel(i + 1, j + 1);

      int frame[3][3] = {{r, s, t},
                         {u, v, w},
                         {x, y, z}};

      int i1 = Convolve3(frame, delta1);
      int i2 = Convolve3(frame, delta2);

      int result = sqrt((i1 * i1) + (i2 * i2));

      output[i][j] = result;

      if (result > max_output)
      {
        max_output = result;
      }
    }
  }

  for (int i = 0; i < num_rows(); i++)
  {
    for (int j = 0; j < num_columns(); j++)
    {
      SetPixel(i, j, output[i][j]);
    }
  }
}

void Image::GenerateHoughImageAndFile(Image &hough_image, const string output_file)
{
  // Initialize hough array + image
  int max_rho = sqrt(pow(num_rows(), 2) + pow(num_columns(), 2));
  double max_theta = M_PI;
  int d_rho = 2;
  double d_theta = M_PI / 360; // 1 degree in radians

  // how many samples for rho and theta
  int rho_buckets = max_rho / d_rho;
  int theta_buckets = 360;

  cout << rho_buckets << " " << theta_buckets << endl;

  // create accumulator array A(1..R,1..T)
  // R is number of samples for rho
  // T is number of samples for theta
  int hough_array[rho_buckets][theta_buckets];

  // Set A(k, h) to zero everywhere in A
  for (int i = 0; i < rho_buckets; i++)
  {
    for (int j = 0; j < theta_buckets; j++)
    {
      hough_array[i][j] = 0;
    }
  }

  // For all pixels (i, j) such that E(i, j) is 1
  for (int i = 0; i < num_rows(); i++)
  {
    for (int j = 0; j < num_columns(); j++)
    {
      if (GetPixel(i, j) >= 1)
      {
        // for h = 1..T
        for (int h = 0; h < theta_buckets; h++)
        {
          // compute rho = ...formula in slides
          double theta_dh = h * d_theta;
          double rho = (i * cos(theta_dh)) + (j * sin(theta_dh));
          // find index k, index k that corresponds to rho
          int k = rho / d_rho;
          // vote
          hough_array[k][h] += 1;
        }
      }
    }
  }

  // Draw array as image
  hough_image.AllocateSpaceAndSetSize(rho_buckets, theta_buckets);

  // find max votes for scaling
  int max_votes = 1;

  for (int i = 0; i < rho_buckets; i++)
  {
    for (int j = 0; j < theta_buckets; j++)
    {
      if (hough_array[i][j] > max_votes)
      {
        max_votes = hough_array[i][j];
      }
    }
  }

  // write output array to image
  for (int i = 0; i < rho_buckets; i++)
  {
    for (int j = 0; j < theta_buckets; j++)
    {
      double h = hough_array[i][j];
      double v = max_votes;
      // scale votes to range from brightness 0 to 255
      double b = h / v * 255;
      hough_image.SetPixel(i, j, b);
    }
  }

  hough_image.SetNumberGrayLevels(255);

  // BEGIN FILE WRITE
  ofstream hough_file(output_file);
  if (hough_file.is_open())
  {
    // write array to file
    hough_file << rho_buckets << " " << theta_buckets << endl;

    for (int i = 0; i < rho_buckets; i++)
    {
      for (int j = 0; j < theta_buckets; j++)
      {
        hough_file << hough_array[i][j] << " ";
      }
      hough_file << endl;
    }
    hough_file.close();
  }
  else
  {
    cout << "Unable to open voting array file" << endl;
  }
}

const int Convolve3(int A[3][3], int B[3][3])
{
  int sum = 0;

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      sum += (A[i][j] * B[i][j]);
    }
  }

  return sum;
}

} // namespace ComputerVisionProjects
