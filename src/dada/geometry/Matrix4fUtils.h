//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Matrix4fUtils.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:  Utilities for sixteen-element square column aligned matrix
//
//---------------------------------------------------------

#ifndef DADA_GEOMETRY_MATRIX4FUTILS_H
#define DADA_GEOMETRY_MATRIX4FUTILS_H

namespace dada
{

class Matrix4f;

void dot(Matrix4f& res, const Matrix4f& a, const Matrix4f& b);

} // dada

#endif // DADA_GEOMETRY_MATRIX4FUTILS_H
