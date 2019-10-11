//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Vector4f.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:  Four-element vector of floats
//
//---------------------------------------------------------

#ifndef DADA_GEOMETRY_VECTOR4F_H
#define DADA_GEOMETRY_VECTOR4F_H

namespace dada
{

class Vector4f
{
public:
  enum { NUM_ELEMENTS = 4 };
  typedef float Element;
  typedef unsigned int index_t;
  
  Vector4f();
  explicit Vector4f(float val);
  Vector4f(float val0, float val1, float val2, float val3);
  const float* buffer() const;
  float* buffer();
  void set(float val);
  float operator [] (index_t idx) const;
  float& operator [] (index_t idx);
  float x() const;
  float& x();
  float y() const;
  float& y();
  float z() const;
  float& z();
  float w() const;
  float& w();
  float r() const;
  float& r();
  float g() const;
  float& g();
  float b() const;
  float& b();
  float a() const;
  float& a();
  
private:
  float m_buffer[NUM_ELEMENTS];
};


inline Vector4f::Vector4f()
{
}

inline Vector4f::Vector4f(float val)
{
  m_buffer[0] = val;
  m_buffer[1] = val;
  m_buffer[2] = val;
  m_buffer[3] = val;
}

inline Vector4f::Vector4f(float val0, float val1, float val2, float val3)
{
  m_buffer[0] = val0;
  m_buffer[1] = val1;
  m_buffer[2] = val2;
  m_buffer[3] = val3;
}

inline const float* Vector4f::buffer() const
{
  return m_buffer;
}

inline float* Vector4f::buffer()
{
  return m_buffer;
}

inline void Vector4f::set(float val)
{
  m_buffer[0] = val;
  m_buffer[1] = val;
  m_buffer[2] = val;
  m_buffer[3] = val;
}

inline float Vector4f::operator [] (index_t idx) const
{
  return m_buffer[idx];
}

inline float& Vector4f::operator [] (index_t idx)
{
  return m_buffer[idx];
}

inline float Vector4f::x() const
{
  return m_buffer[0];
}

inline float& Vector4f::x()
{
  return m_buffer[0];
}

inline float Vector4f::y() const
{
  return m_buffer[1];
}

inline float& Vector4f::y()
{
  return m_buffer[1];
}

inline float Vector4f::z() const
{
  return m_buffer[2];
}

inline float& Vector4f::z()
{
  return m_buffer[2];
}

inline float Vector4f::w() const
{
  return m_buffer[3];
}

inline float& Vector4f::w()
{
  return m_buffer[3];
}

inline float Vector4f::r() const
{
  return m_buffer[0];
}

inline float& Vector4f::r()
{
  return m_buffer[0];
}

inline float Vector4f::g() const
{
  return m_buffer[1];
}

inline float& Vector4f::g()
{
  return m_buffer[1];
}

inline float Vector4f::b() const
{
  return m_buffer[2];
}

inline float& Vector4f::b()
{
  return m_buffer[2];
}

inline float Vector4f::a() const
{
  return m_buffer[3];
}

inline float& Vector4f::a()
{
  return m_buffer[3];
}

} // dada

#endif // DADA_GEOMETRY_VECTOR4F_H
