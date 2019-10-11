//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Vector4fUtils.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:  Utilities for four-element vector of floats
//
//---------------------------------------------------------

#ifndef DADA_GEOMETRY_VECTOR4FUTILS_H
#define DADA_GEOMETRY_VECTOR4FUTILS_H

#include "dada/geometry/Vector4f.h"

namespace dada
{

float length(const Vector4f& v);
float lengthSq(const Vector4f& v);
void normalize(Vector4f& v);
void negate(Vector4f& v);
void operator += (Vector4f& a, const Vector4f& b);
void operator -= (Vector4f& a, const Vector4f& b);
void operator *= (Vector4f& a, float b);
void operator /= (Vector4f& a, float b);
float dot(const Vector4f& a, const Vector4f& b);


inline float lengthSq(const Vector4f& v)
{
  return v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3];
}

inline void normalize(Vector4f& v)
{
  const float len = length(v);
  if (len != 0.0f)
  {
    v /= len;
  }
}

inline void negate(Vector4f& v)
{
  v[0] = -v[0];
  v[1] = -v[1];
  v[2] = -v[2];
  v[3] = -v[3];
}

inline void operator += (Vector4f& a, const Vector4f& b)
{
  a[0] += b[0];
  a[1] += b[1];
  a[2] += b[2];
  a[3] += b[3];
}

inline void operator -= (Vector4f& a, const Vector4f& b)
{
  a[0] -= b[0];
  a[1] -= b[1];
  a[2] -= b[2];
  a[3] -= b[3];
}

inline void operator *= (Vector4f& a, float b)
{
  a[0] *= b;
  a[1] *= b;
  a[2] *= b;
  a[3] *= b;
}

inline void operator /= (Vector4f& a, float b)
{
  a[0] /= b;
  a[1] /= b;
  a[2] /= b;
  a[3] /= b;
}

inline float dot(const Vector4f& a, const Vector4f& b)
{
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

} // dada

#endif // DADA_GEOMETRY_VECTOR4FUTILS_H
