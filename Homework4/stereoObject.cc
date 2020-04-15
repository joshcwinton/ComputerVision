#include "stereoObject.h"
#include "image.h"
#include <iostream>
#include <cmath>

using namespace std;

namespace ComputerVisionProjects
{

array<double, 3> leftMultiply(array<array<double, 3>, 3> leftMatrix, array<int, 3> rightMatrix)
{
  array<double, 3> result;
  result.fill(0);

  for (size_t i = 0; i < 3; i++)
  {
    result[0] += leftMatrix[0][i] * rightMatrix[i];
    result[1] += leftMatrix[1][i] * rightMatrix[i];
    result[2] += leftMatrix[2][i] * rightMatrix[i];
  }

  return result;
}

array<double, 3> makeUnitVector(array<double, 3> v)
{
  array<double, 3> result;
  double length = sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
  result[0] = v[0] / length;
  result[1] = v[1] / length;
  result[2] = v[2] / length;
  return result;
}

double vectorLength(array<double, 3> v)
{
  return sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
}

void drawNormal(int row, int col, array<double, 3> normal, Image *normal_image)
{
  // Draw small circle
  normal_image->SetPixel(row, col - 1, 255);
  normal_image->SetPixel(row - 1, col, 255);
  normal_image->SetPixel(row, col + 1, 255);
  normal_image->SetPixel(row + 1, col, 255);
  // scale up normal
  array<double, 3> long_normal = {10 * normal[0], 10 * normal[1], 10 * normal[2]};
  DrawLine(row, col, row + long_normal[1], col + long_normal[0], 255, normal_image);
  normal_image->SetPixel(row, col, 0);
}

StereoObject::StereoObject(Image *image_1, Image *image_2, Image *image_3, array<array<double, 3>, 3> S_inverse, int step_size, int threshold)
{
  threshold_ = threshold;
  step_size_ = step_size;

  image_1_ = image_1;
  image_2_ = image_2;
  image_3_ = image_3;

  S_inverse_ = S_inverse;

  calcNormals();
  calcAlbedos();
}

StereoObject::StereoObject(Image *image_1, Image *image_2, Image *image_3, array<array<double, 3>, 3> S_inverse, int threshold)
{
  threshold_ = threshold;
  step_size_ = 1;

  image_1_ = image_1;
  image_2_ = image_2;
  image_3_ = image_3;

  S_inverse_ = S_inverse;

  calcAlbedos();
}

void StereoObject::calcNormals()
{
  // initialize normals_
  normals_.resize(image_1_->num_rows());
  array<double, 3> zeroes = {0, 0, 0};
  for (size_t i = 0; i < normals_.size(); i++)
  {
    normals_[i].resize(image_1_->num_columns(), zeroes);
  }

  // for every step_size_th row and column calculate the normal of the object at that point and put it in normals_
  for (size_t row = 0; row < image_1_->num_rows(); row += step_size_)
  {
    for (size_t col = 0; col < image_1_->num_columns(); col += step_size_)
    {
      if (!isVisible(row, col))
      {
        continue;
      }

      // Build column vector of intensities
      int I_1 = image_1_->GetPixel(row, col);
      int I_2 = image_2_->GetPixel(row, col);
      int I_3 = image_3_->GetPixel(row, col);
      array<int, 3> I = {I_1, I_2, I_3};
      array<double, 3> N;

      // Apply S_inverse to I to get N
      N = leftMultiply(S_inverse_, I);
      N = makeUnitVector(N);

      // Put resized N in normals_
      normals_[row][col] = N;
    }
  }
}

void StereoObject::calcAlbedos()
{
  // initialize albedos_
  albedos_.resize(image_1_->num_rows());
  for (size_t i = 0; i < albedos_.size(); i++)
  {
    albedos_[i].resize(image_1_->num_columns(), 0);
  }

  // for every step_size_th row and column calculate the normal of the object at that point and put it in normals_
  for (size_t row = 0; row < image_1_->num_rows(); row++)
  {
    for (size_t col = 0; col < image_1_->num_columns(); col++)
    {
      if (!isVisible(row, col))
      {
        continue;
      }

      // Build column vector of intensities
      int I_1 = image_1_->GetPixel(row, col);
      int I_2 = image_2_->GetPixel(row, col);
      int I_3 = image_3_->GetPixel(row, col);
      array<int, 3> I = {I_1, I_2, I_3};
      array<double, 3> N;

      // Apply S_inverse to I to get N
      N = leftMultiply(S_inverse_, I);

      // Put resized N in normals_
      albedos_[row][col] = vectorLength(N);
    }
  }
}

bool StereoObject::isVisible(int row, int col)
{
  if (image_1_->GetPixel(row, col) < threshold_)
  {
    return false;
  }
  if (image_2_->GetPixel(row, col) < threshold_)
  {
    return false;
  }
  if (image_3_->GetPixel(row, col) < threshold_)
  {
    return false;
  }
  return true;
}

void StereoObject::drawNormals(Image *normals_image)
{
  // initialize image
  normals_image->AllocateSpaceAndSetSize(image_1_->num_rows(), image_1_->num_columns());
  normals_image->SetNumberGrayLevels(255);

  for (size_t row = 0; row < normals_image->num_rows(); row++)
  {
    for (size_t col = 0; col < normals_image->num_columns(); col++)
    {
      normals_image->SetPixel(row, col, image_1_->GetPixel(row, col));
    }
  }

  // loop over all pixels incrementing by step size
  // draw normals_[row][col]
  for (size_t row = 0; row < normals_image->num_rows(); row += step_size_)
  {
    for (size_t col = 0; col < normals_image->num_columns(); col += step_size_)
    {
      if (!isVisible(row, col))
      {
        continue;
      }
      drawNormal(row, col, normals_[row][col], normals_image);
    }
  }
}

void StereoObject::drawAlbedos(Image *albedos_image)
{
  // initialize image
  albedos_image->AllocateSpaceAndSetSize(image_1_->num_rows(), image_1_->num_columns());
  albedos_image->SetNumberGrayLevels(255);

  // find max albedo
  double max_albedo = 0;

  for (size_t row = 0; row < albedos_.size(); row++)
  {
    for (size_t col = 0; col < albedos_[row].size(); col++)
    {
      if (albedos_[row][col] > max_albedo)
      {
        max_albedo = albedos_[row][col];
      }
    }
  }

  // set albedo for visible pixels
  for (size_t row = 0; row < albedos_image->num_rows(); row++)
  {
    for (size_t col = 0; col < albedos_image->num_columns(); col++)
    {
      if (!isVisible(row, col))
      {
        continue;
      }
      // scale albedo to 0-255
      int t = (albedos_[row][col] / max_albedo) * 255;
      albedos_image->SetPixel(row, col, t);
    }
  }
}

} // namespace ComputerVisionProjects
