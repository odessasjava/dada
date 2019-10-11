//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Transform3f.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:  Class for transformations in 3D
//
//---------------------------------------------------------

#ifndef DADA_GEOMETRY_TRANSFORM3F_H
#define DADA_GEOMETRY_TRANSFORM3F_H

#include "dada/geometry/Matrix3f.h"
#include "dada/geometry/Matrix4f.h"
#include "dada/geometry/Vector3f.h"

namespace dada
{

class Transform3f
{
public:
  typedef float element_t;
  
  Transform3f();
  explicit Transform3f(float val);
  const Matrix3f& m() const;
  Matrix3f& m();
  const Vector3f& v() const;
  Vector3f& v();
  void setIdentity();
  void setTranslate(const Vector3f& dv);
  void setScale(const Vector3f& factor);
  void setRotateX(float angle);
  void setRotateY(float angle);
  void setRotateZ(float angle);
  void setMirrorY();
  //   void setLookAt(Matrix3f& res, const Vector3f& eye, const Vector3f& center, const Vector3f& up);
  void translate(const Vector3f& dv);
  void scale(const Vector3f& factor);
  void rotateX(float angle);
  void rotateY(float angle);
  void rotateZ(float angle);
  void mirrorY();
  void lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);
  void genMatrix(Matrix4f& res) const;

  static void genRotateX(Matrix3f& res, float angle);
  static void genRotateY(Matrix3f& res, float angle);
  static void genRotateZ(Matrix3f& res, float angle);
  //  static void genLookAt(Matrix3f& res, const Vector3f& eye, const Vector3f& center, const Vector3f& up);

  static void genOrtho(Matrix4f& res, float l, float r, float b, float t, float n, float f);
  static void genFrustum(Matrix4f& res, float l, float r, float b, float t, float n, float f);
  static void genPerspective(Matrix4f& res, float fovy, float aspect, float n, float f);

  friend void dot(Transform3f& res, const Transform3f& a, const Transform3f& b);

private:
  Matrix3f m_m;
  Vector3f m_v;
};

void dot(Transform3f& res, const Transform3f& a, const Transform3f& b);

inline const Matrix3f& Transform3f::m() const
{
  return m_m;
}

inline Matrix3f& Transform3f::m()
{
  return m_m;
}

inline const Vector3f& Transform3f::v() const
{
  return m_v;
}

inline Vector3f& Transform3f::v()
{
  return m_v;
}

} // dada

#endif // DADA_GEOMETRY_TRANSFORM3F_H
