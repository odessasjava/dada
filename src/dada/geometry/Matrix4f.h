//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Matrix4f.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:  Sixteen-element square column aligned matrix
//
//---------------------------------------------------------

#ifndef DADA_GEOMETRY_MATRIX4F_H
#define DADA_GEOMETRY_MATRIX4F_H

namespace dada
{

class Matrix4f
{
public:
  enum { NUM_ROWS = 4 };
  enum { NUM_COLS = 4 };
  enum { NUM_ELEMENTS = 16 };
  typedef float element_t;
  typedef unsigned int index_t;
  
  Matrix4f();
  explicit Matrix4f(float val);
  Matrix4f(float val00, float val11, float val22, float val33);
  const float* buffer() const;
  float* buffer();
  void set(float val);
  void set(float val00, float val11, float val22, float val33);
  float operator [] (index_t index) const;
  float& operator [] (index_t index);
  float at(index_t row, index_t col) const;
  float& at(index_t row, index_t col);
  
private:
  float m_buffer[16];
};


inline Matrix4f::Matrix4f()
{
}

inline Matrix4f::Matrix4f(float val)
{
  set(val);
}

inline Matrix4f::Matrix4f(float val00, float val11, float val22, float val33)
{
  set(val00, val11, val22, val33);
}

inline const float* Matrix4f::buffer() const
{
  return m_buffer;
}

inline float* Matrix4f::buffer()
{
  return m_buffer;
}

inline void Matrix4f::set(float val)
{
  m_buffer[ 0] = val;
  m_buffer[ 1] = 0.0f;
  m_buffer[ 2] = 0.0f;
  m_buffer[ 3] = 0.0f;
  m_buffer[ 4] = 0.0f;
  m_buffer[ 5] = val;
  m_buffer[ 6] = 0.0f;
  m_buffer[ 7] = 0.0f;
  m_buffer[ 8] = 0.0f;
  m_buffer[ 9] = 0.0f;
  m_buffer[10] = val;
  m_buffer[11] = 0.0f;
  m_buffer[12] = 0.0f;
  m_buffer[13] = 0.0f;
  m_buffer[14] = 0.0f;
  m_buffer[15] = val;
}

inline void Matrix4f::set(float val00, float val11, float val22, float val33)
{
  m_buffer[ 0] = val00;
  m_buffer[ 1] = 0.0f;
  m_buffer[ 2] = 0.0f;
  m_buffer[ 3] = 0.0f;
  m_buffer[ 4] = 0.0f;
  m_buffer[ 5] = val11;
  m_buffer[ 6] = 0.0f;
  m_buffer[ 7] = 0.0f;
  m_buffer[ 8] = 0.0f;
  m_buffer[ 9] = 0.0f;
  m_buffer[10] = val22;
  m_buffer[11] = 0.0f;
  m_buffer[12] = 0.0f;
  m_buffer[13] = 0.0f;
  m_buffer[14] = 0.0f;
  m_buffer[15] = val33;
}

inline float Matrix4f::operator [] (index_t index) const
{
  return m_buffer[index];
}

inline float& Matrix4f::operator [] (index_t index)
{
  return m_buffer[index];
}

inline float Matrix4f::at(index_t row, index_t col) const
{
  return m_buffer[row + NUM_ROWS * col];
}

inline float& Matrix4f::at(index_t row, index_t col)
{
  return m_buffer[row + NUM_ROWS * col];
}

} // dada

#endif // DADA_GEOMETRY_MATRIX4F_H
