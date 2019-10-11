//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Matrix3fUtils.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/geometry/Matrix3fUtils.h"
#include "dada/geometry/Matrix3f.h"
#include "dada/geometry/Vector3f.h"

namespace dada
{

void dot(Matrix3f& res, const Matrix3f& a, const Matrix3f& b)
{
  res[0] = a[0] * b[0] + a[3] * b[1] + a[6] * b[2];
  res[1] = a[1] * b[0] + a[4] * b[1] + a[7] * b[2];
  res[2] = a[2] * b[0] + a[5] * b[1] + a[8] * b[2];
  res[3] = a[0] * b[3] + a[3] * b[4] + a[6] * b[5];
  res[4] = a[1] * b[3] + a[4] * b[4] + a[7] * b[5];
  res[5] = a[2] * b[3] + a[5] * b[4] + a[8] * b[5];
  res[6] = a[0] * b[6] + a[3] * b[7] + a[6] * b[8];
  res[7] = a[1] * b[6] + a[4] * b[7] + a[7] * b[8];
  res[8] = a[2] * b[6] + a[5] * b[7] + a[8] * b[8];
}

void dot(Vector3f& res, const Matrix3f& a, const Vector3f& b)
{
  res[0] = a[0] * b[0] + a[3] * b[1] + a[6] * b[2];
  res[1] = a[1] * b[0] + a[4] * b[1] + a[7] * b[2];
  res[2] = a[2] * b[0] + a[5] * b[1] + a[8] * b[2];
}

} // dada
