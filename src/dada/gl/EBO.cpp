//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         EBO.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/gl/EBO.h"
#include "dada/gl/GL.h"
#include "dada/core/Log.h"

namespace dada
{

EBO::EBO() :
  Object(),
  m_id(0)
{
  glGenBuffers(1, &m_id);
  GLenum err = glGetError();
  if (m_id == 0 || err != GL_NO_ERROR)
  {
    getLog() << "ERROR: Unable to create EBO" << endl;
  }
}

EBO::~EBO()
{
  glDeleteBuffers(1, &m_id);
  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
  {
    getLog() << "ERROR: Unable to delete EBO" << endl;
  }
}

bool EBO::bind()
{
  bool res = false;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
  GLenum err = glGetError();
  if (err == GL_NO_ERROR)
  {
    res = true;
  }
  else
  {
    getLog() << "ERROR: Unable to bind EBO" << endl;
  }
  return res;
}

bool EBO::load(unsigned int size, const void* data)
{
  bool res = bind();
  if (res)
  {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    GLenum err = glGetError();
    if (err == GL_NO_ERROR)
    {
      res = true;
    }
    else
    {
      getLog() << "ERROR: Unable to load EBO" << endl;
    }
  }
  return res;
}

} // dada
