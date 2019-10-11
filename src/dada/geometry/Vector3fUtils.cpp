//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Vector3fUtils.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/geometry/Vector3fUtils.h"
#include <cmath>

namespace dada
{

float length(const Vector3f& v)
{
  return sqrt(lengthSq(v));
}

} // dada
