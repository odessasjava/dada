//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Vector3f.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:  Three-element vector of floats
//
//---------------------------------------------------------

#ifndef DADA_GEOMETRY_VECTOR3F_H
#define DADA_GEOMETRY_VECTOR3F_H

namespace dada
{

class Vector3f
{
public:
  enum { NUM_ELEMENTS = 3 };
  typedef float Element;
  typedef unsigned int index_t;
  
  Vector3f();
  explicit Vector3f(float val);
  Vector3f(float val0, float val1, float val2);
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
  float r() const;
  float& r();
  float g() const;
  float& g();
  float b() const;
  float& b();
  
private:
  float m_buffer[NUM_ELEMENTS];
};


inline Vector3f::Vector3f()
{
}

inline Vector3f::Vector3f(float val)
{
  set(val);
}

inline Vector3f::Vector3f(float val0, float val1, float val2)
{
  m_buffer[0] = val0;
  m_buffer[1] = val1;
  m_buffer[2] = val2;
}

inline const float* Vector3f::buffer() const
{
  return m_buffer;
}

inline float* Vector3f::buffer()
{
  return m_buffer;
}

inline void Vector3f::set(float val)
{
  m_buffer[0] = val;
  m_buffer[1] = val;
  m_buffer[2] = val;
}

inline float Vector3f::operator [] (index_t idx) const
{
  return m_buffer[idx];
}

inline float& Vector3f::operator [] (index_t idx)
{
  return m_buffer[idx];
}

inline float Vector3f::x() const
{
  return m_buffer[0];
}

inline float& Vector3f::x()
{
  return m_buffer[0];
}

inline float Vector3f::y() const
{
  return m_buffer[1];
}

inline float& Vector3f::y()
{
  return m_buffer[1];
}

inline float Vector3f::z() const
{
  return m_buffer[2];
}

inline float& Vector3f::z()
{
  return m_buffer[2];
}

inline float Vector3f::r() const
{
  return m_buffer[0];
}

inline float& Vector3f::r()
{
  return m_buffer[0];
}

inline float Vector3f::g() const
{
  return m_buffer[1];
}

inline float& Vector3f::g()
{
  return m_buffer[1];
}

inline float Vector3f::b() const
{
  return m_buffer[2];
}

inline float& Vector3f::b()
{
  return m_buffer[2];
}

} // dada

#endif // DADA_GEOMETRY_VECTOR3F_H
