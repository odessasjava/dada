//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Matrix3fUtils.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:  Utilities for nine-element square column aligned matrix
//
//---------------------------------------------------------

#ifndef DADA_GEOMETRY_MATRIX3FUTILS_H
#define DADA_GEOMETRY_MATRIX3FUTILS_H

namespace dada
{

class Matrix3f;
class Vector3f;


void dot(Matrix3f& res, const Matrix3f& a, const Matrix3f& b);
void dot(Vector3f& res, const Matrix3f& a, const Vector3f& b);

} // dada

#endif // DADA_GEOMETRY_MATRIX3FUTILS_H
