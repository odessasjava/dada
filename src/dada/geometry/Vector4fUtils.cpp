//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Vector4fUtils.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/geometry/Vector4fUtils.h"
#include <cmath>

namespace dada
{

float length(const Vector4f& v)
{
  return sqrt(lengthSq(v));
}

} // dada
