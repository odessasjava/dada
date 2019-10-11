//---------------------------------------------------------
//
//  Project:      dada
//  Module:       geometry
//  File:         Matrix3f.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:  Nine-element square column aligned matrix
//
//---------------------------------------------------------

#ifndef DADA_GEOMETRY_MATRIX3F_H
#define DADA_GEOMETRY_MATRIX3F_H

namespace dada
{

class Matrix3f
{
public:
  enum { NUM_ROWS = 3 };
  enum { NUM_COLS = 3 };
  enum { NUM_ELEMENTS = 9 };
  typedef float element_t;
  typedef unsigned int index_t;
  
  Matrix3f();
  explicit Matrix3f(float val);
  Matrix3f(float val00, float val11, float val22);
  const float* buffer() const;
  float* buffer();
  void set(float val);
  void set(float val00, float val11, float val22);
  float operator [] (index_t index) const;
  float& operator [] (index_t index);
  float at(index_t row, index_t col) const;
  float& at(index_t row, index_t col);
  
private:
  float m_buffer[9];
};


inline Matrix3f::Matrix3f()
{
}

inline Matrix3f::Matrix3f(float val)
{
  set(val);
}

inline Matrix3f::Matrix3f(float val00, float val11, float val22)
{
  set(val00, val11, val22);
}

inline const float* Matrix3f::buffer() const
{
  return m_buffer;
}

inline float* Matrix3f::buffer()
{
  return m_buffer;
}

inline void Matrix3f::set(float val)
{
  m_buffer[0] = val;
  m_buffer[1] = 0.0f;
  m_buffer[2] = 0.0f;
  m_buffer[3] = 0.0f;
  m_buffer[4] = val;
  m_buffer[5] = 0.0f;
  m_buffer[6] = 0.0f;
  m_buffer[7] = 0.0f;
  m_buffer[8] = val;
}

inline void Matrix3f::set(float val00, float val11, float val22)
{
  m_buffer[0] = val00;
  m_buffer[1] = 0.0f;
  m_buffer[2] = 0.0f;
  m_buffer[3] = 0.0f;
  m_buffer[4] = val11;
  m_buffer[5] = 0.0f;
  m_buffer[6] = 0.0f;
  m_buffer[7] = 0.0f;
  m_buffer[8] = val22;
}

inline float Matrix3f::operator [] (index_t index) const
{
  return m_buffer[index];
}

inline float& Matrix3f::operator [] (index_t index)
{
  return m_buffer[index];
}

inline float Matrix3f::at(index_t row, index_t col) const
{
  return m_buffer[row + NUM_ROWS * col];
}

inline float& Matrix3f::at(index_t row, index_t col)
{
  return m_buffer[row + NUM_ROWS * col];
}

} // dada

#endif // DADA_GEOMETRY_MATRIX3F_H
