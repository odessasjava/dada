//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         VAO.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/gl/VAO.h"
#include "dada/gl/GL.h"
#include "dada/core/Log.h"

namespace dada
{

VAO::VAO() :
  Object(),
  m_id(0)
{
  glGenVertexArrays(1, &m_id);
  GLenum err = glGetError();
  if (m_id == 0 || err != GL_NO_ERROR)
  {
    getLog() << "ERROR: Unable to create VAO" << endl;
  }
}

VAO::~VAO()
{
  glDeleteVertexArrays(1, &m_id);
  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
  {
    getLog() << "ERROR: Unable to delete VAO" << endl;
  }
}

bool VAO::bind()
{
  bool res = false;
  glBindVertexArray(m_id);
  GLenum err = glGetError();
  if (err == GL_NO_ERROR)
  {
    res = true;
  }
  else
  {
    getLog() << "ERROR: Unable to bind VAO" << endl;
  }
  return res;
}

} // dada
