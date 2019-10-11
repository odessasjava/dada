//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Vector3fUtils.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:  Utilities for three-element vector of floats
//
//---------------------------------------------------------

#ifndef DADA_GEOMETRY_VECTOR3FUTILS_H
#define DADA_GEOMETRY_VECTOR3FUTILS_H

#include "dada/geometry/Vector3f.h"

namespace dada
{

float length(const Vector3f& v);
float lengthSq(const Vector3f& v);
void normalize(Vector3f& v);
void negate(Vector3f& v);
void operator += (Vector3f& a, const Vector3f& b);
void operator -= (Vector3f& a, const Vector3f& b);
void operator *= (Vector3f& a, float b);
void operator /= (Vector3f& a, float b);
float dot(const Vector3f& a, const Vector3f& b);
void cross(Vector3f& res, const Vector3f& a, const Vector3f& b);


inline float lengthSq(const Vector3f& v)
{
  return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

inline void normalize(Vector3f& v)
{
  const float len = length(v);
  if (len != 0.0f)
  {
    v /= len;
  }
}

inline void negate(Vector3f& v)
{
  v[0] = -v[0];
  v[1] = -v[1];
  v[2] = -v[2];
}

inline void operator += (Vector3f& a, const Vector3f& b)
{
  a[0] += b[0];
  a[1] += b[1];
  a[2] += b[2];
}

inline void operator -= (Vector3f& a, const Vector3f& b)
{
  a[0] -= b[0];
  a[1] -= b[1];
  a[2] -= b[2];
}

inline void operator *= (Vector3f& a, float b)
{
  a[0] *= b;
  a[1] *= b;
  a[2] *= b;
}

inline void operator /= (Vector3f& a, float b)
{
  a[0] /= b;
  a[1] /= b;
  a[2] /= b;
}

inline float dot(const Vector3f& a, const Vector3f& b)
{
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline void cross(Vector3f& res, const Vector3f& a, const Vector3f& b)
{
  res[0] = a[1] * b[2] - a[2] * b[1];
  res[1] = a[2] * b[0] - a[0] * b[2];
  res[2] = a[0] * b[1] - a[1] * b[0];
}

} // dada

#endif // DADA_GEOMETRY_VECTOR3FUTILS_H
