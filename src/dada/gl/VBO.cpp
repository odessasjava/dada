//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         VBO.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/gl/VBO.h"
#include "dada/gl/GL.h"
#include "dada/core/Log.h"

namespace dada
{

VBO::VBO() :
  Object(),
  m_id(0)
{
  glGenBuffers(1, &m_id);
  GLenum err = glGetError();
  if (m_id == 0 || err != GL_NO_ERROR)
  {
    getLog() << "ERROR: Unable to create VBO" << endl;
  }
}

VBO::~VBO()
{
  glDeleteBuffers(1, &m_id);
  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
  {
    getLog() << "ERROR: Unable to delete VBO" << endl;
  }
}

bool VBO::bind()
{
  bool res = false;
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  GLenum err = glGetError();
  if (err == GL_NO_ERROR)
  {
    res = true;
  }
  else
  {
    getLog() << "ERROR: Unable to bind VBO" << endl;
  }
  return res;
}

bool VBO::load(unsigned int size, const void* data)
{
  bool res = bind();
  if (res)
  {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    GLenum err = glGetError();
    if (err == GL_NO_ERROR)
    {
      res = true;
    }
    else
    {
      getLog() << "ERROR: Unable to load VBO" << endl;
    }
  }
  return res;
}

} // dada
