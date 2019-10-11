//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Transform3f.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/geometry/Transform3f.h"
#include "dada/geometry/Matrix3fUtils.h"
#include "dada/geometry/Vector3fUtils.h"
#include <cmath>

namespace dada
{

Transform3f::Transform3f() :
  m_m(),
  m_v()
{
}

Transform3f::Transform3f(float val) :
  m_m(val),
  m_v(0.0f)
{
}

void Transform3f::setIdentity()
{
  m_m.set(1.0f);
  m_v.set(0.0f);
}

void Transform3f::setTranslate(const Vector3f& dv)
{
  m_m.set(1.0f);
  m_v = dv;
}

void Transform3f::setScale(const Vector3f& factor)
{
  m_m.set(factor.x(), factor.y(), factor.z());
  m_v.set(0.0f);
}

void Transform3f::setRotateX(float angle)
{
  genRotateX(m_m, angle);
  m_v.set(0.0f);
}

void Transform3f::setRotateY(float angle)
{
  genRotateY(m_m, angle);
  m_v.set(0.0f);
}

void Transform3f::setRotateZ(float angle)
{
  genRotateZ(m_m, angle);
  m_v.set(0.0f);
}

void Transform3f::setMirrorY()
{
  m_m[4] = -1.0f;
}

void Transform3f::translate(const Vector3f& dv)
{
  Vector3f res;
  dot(res, m_m, dv);
  m_v += res;
}

void Transform3f::scale(const Vector3f& factor)
{
  m_m[0] *= factor.x();
  m_m[1] *= factor.x();
  m_m[2] *= factor.x();
  m_m[3] *= factor.y();
  m_m[4] *= factor.y();
  m_m[5] *= factor.y();
  m_m[6] *= factor.z();
  m_m[7] *= factor.z();
  m_m[8] *= factor.z();
}

void Transform3f::rotateX(float angle)
{
  Matrix3f r, res;
  genRotateX(r, angle);
  dot(res, m_m, r);
  m_m = res;
}

void Transform3f::rotateY(float angle)
{
  Matrix3f r, res;
  genRotateY(r, angle);
  dot(res, m_m, r);
  m_m = res;
}

void Transform3f::rotateZ(float angle)
{
  Matrix3f r, res;
  genRotateZ(r, angle);
  dot(res, m_m, r);
  m_m = res;
}

void Transform3f::mirrorY()
{
  m_m[4] = -m_m[4];
}

void Transform3f::lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up)
{
  //Vector3f f(center);
  //f -= eye;
  Vector3f f(eye);
  f -= center;
  normalize(f);
  Vector3f s;
  cross(s, f, up);
  //Vector3f s_n(s);
  //s_n.normalize();
  //Vector3f u;
  //cross(u, s_n, f);

  Matrix3f m, res;
  m[0] = s[0];
  m[1] = up[0]; //u[0];
  m[2] = -f[0];
  m[3] = s[1];
  m[4] = up[1]; //u[1];
  m[5] = -f[1];
  m[6] = s[2];
  m[7] = up[2]; // u[2];
  m[8] = -f[2];
  dot(res, m_m, m);
  m_m = res;

  Vector3f dv(eye);
  negate(dv);
  translate(dv);
  //dot(m_v, m_m, dv);
}

void Transform3f::genMatrix(Matrix4f& res) const
{
  res[ 0] = m_m[0];
  res[ 1] = m_m[1];
  res[ 2] = m_m[2];
  res[ 3] = 0.0f;
  res[ 4] = m_m[3];
  res[ 5] = m_m[4];
  res[ 6] = m_m[5];
  res[ 7] = 0.0f;
  res[ 8] = m_m[6];
  res[ 9] = m_m[7];
  res[10] = m_m[8];
  res[11] = 0.0f;
  res[12] = m_v[0];
  res[13] = m_v[1];
  res[14] = m_v[2];
  res[15] = 1.0f;
}

void Transform3f::genRotateX(Matrix3f& res, float angle)
{
  const float cosine = cos(angle);
  const float sine = sin(angle);
  res[0] = 1.0f;
  res[1] = 0.0f;
  res[2] = 0.0f;
  res[3] = 0.0f;
  res[4] = cosine;
  res[5] = sine;
  res[6] = 0.0f;
  res[7] = -sine;
  res[8] = cosine;
}

void Transform3f::genRotateY(Matrix3f& res, float angle)
{
  const float cosine = cos(angle);
  const float sine = sin(angle);
  res[0] = cosine;
  res[1] = 0.0f;
  res[2] = -sine;
  res[3] = 0.0f;
  res[4] = 1.0f;
  res[5] = 0.0f;
  res[6] = sine;
  res[7] = 0.0f;
  res[8] = cosine;
}

void Transform3f::genRotateZ(Matrix3f& res, float angle)
{
  const float cosine = cos(angle);
  const float sine = sin(angle);
  res[0] = cosine;
  res[1] = sine;
  res[2] = 0.0f;
  res[3] = -sine;
  res[4] = cosine;
  res[5] = 0.0f;
  res[6] = 0.0f;
  res[7] = 0.0f;
  res[8] = 1.0f;
}

void Transform3f::genOrtho(Matrix4f& res, float l, float r, float b, float t, float n, float f)
{
  const float kx = 1.0f / (r - l);
  const float ky = 1.0f / (t - b);
  const float kz = 1.0f / (f - n);
  res[ 0] = kx + kx;
  res[ 1] = 0.0f;
  res[ 2] = 0.0f;
  res[ 3] = 0.0f;
  res[ 4] = 0.0f;
  res[ 5] = ky + ky;
  res[ 6] = 0.0f;
  res[ 7] = 0.0f;
  res[ 8] = 0.0f;
  res[ 9] = 0.0f;
  res[10] = kz + kz;
  res[11] = 0.0f;
  res[12] = -(r + l) * kx;
  res[13] = -(t + b) * ky;
  res[14] = -(f + n) * kz;
  res[15] = 1.0f;
}

void Transform3f::genFrustum(Matrix4f& res, float l, float r, float b, float t, float n, float f)
{
  const float n2 = n + n;
  const float kx = 1.0f / (r - l);
  const float ky = 1.0f / (t - b);
  const float kz = 1.0f / (f - n);
  res[ 0] = n2 * kx;
  res[ 1] = 0.0f;
  res[ 2] = 0.0f;
  res[ 3] = 0.0f;
  res[ 4] = 0.0f;
  res[ 5] = n2 * ky;
  res[ 6] = 0.0f;
  res[ 7] = 0.0f;
  res[ 8] = -(r + l) * kx;
  res[ 9] = -(t + b) * ky;
  res[10] = (f + n) * kz;
  res[11] = 1.0f;
  res[12] = 0.0f;
  res[13] = 0.0f;
  res[14] = -n2 * f * kz;
  res[15] = 0.0f;
}

void Transform3f::genPerspective(Matrix4f& res, float fovy, float aspect, float n, float f)
{
  const float k = 1.0f / tan(0.5f * fovy);
  const float kz = 1.0f / (f - n);
  res[ 0] = k / aspect;
  res[ 1] = 0.0f;
  res[ 2] = 0.0f;
  res[ 3] = 0.0f;
  res[ 4] = 0.0f;
  res[ 5] = k;
  res[ 6] = 0.0f;
  res[ 7] = 0.0f;
  res[ 8] = 0.0f;
  res[ 9] = 0.0f;
  res[10] = (f + n) * kz;
  res[11] = 1.0f;
  res[12] = 0.0f;
  res[13] = 0.0f;
  res[14] = -2.0f * n * f * kz;
  res[15] = 0.0f;
}

void dot(Transform3f& res, const Transform3f& a, const Transform3f& b)
{
  dot(res.m_m, a.m_m, b.m_m);
  
  Vector3f v;
  dot(v, a.m_m, b.m_v);
  v += a.m_v;
  res.m_v = v;
}

} // dada
