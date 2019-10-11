//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         Program.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/gl/GL.h"
#include "dada/core/Log.h"
#include "dada/gl/Program.h"

#include "dada/gl/Shader.h"

namespace dada
{

Program::Program() :
  Object(),
  m_id(0),
  m_valid(false)
{
  m_id = glCreateProgram();
  GLenum err = glGetError();
  if (m_id == 0 || err != GL_NO_ERROR)
  {
    getLog() << "ERROR: Unable to create program" << endl;
  }
}

Program::~Program()
{
  glDeleteProgram(m_id);
}

bool Program::attach(Shader& sh)
{
  m_valid = false;
  glAttachShader(m_id, sh.getID());
  GLenum err = glGetError();
  return err == GL_NO_ERROR;
}

bool Program::link()
{
  glLinkProgram(m_id);

  GLint linked;
  glGetProgramiv(m_id, GL_LINK_STATUS, &linked);
  if (linked == 0)
  {
    GLint length = 0;
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
    if (length > 1)
    {
      getLog() << "ERROR: While linking program " << m_id << endl;
      char* buf = new char[length];
      glGetProgramInfoLog(m_id, length, NULL, buf);
      getLog() << buf << endl;
      delete buf;
    }
  }
  m_valid = (linked != 0);
  return m_valid;
}

Program::index_t Program::findAttributeLocation(const char* name) const
{
  return glGetAttribLocation(m_id, name);
}

Program::index_t Program::findUniformLocation(const char* name) const
{
  return glGetUniformLocation(m_id, name);
}

bool Program::use()
{
  bool res = false;
  glUseProgram(m_id);
  GLenum err = glGetError();
  if (err == GL_NO_ERROR)
  {
    res = true;
  }
  else
  {
    getLog() << "ERROR: Unable to use program" << endl;
  }
  return res;
}
/*
bool Program::setUniform(index_t location, int val)
{
  bool res = false;
  glUniform1i(location, val);
  GLenum err = glGetError();
  if (err == GL_NO_ERROR)
  {
    res = true;
  }
  else
  {
    getLog() << "ERROR: Unable to set uniform of program" << endl;
  }
  return res;
}

bool Program::setUniform(index_t location, float val)
{
  bool res = false;
  glUniform1f(location, val);
  GLenum err = glGetError();
  if (err == GL_NO_ERROR)
  {
    res = true;
  }
  else
  {
    getLog() << "ERROR: Unable to set uniform of program" << endl;
  }
  return res;
}

bool Program::setUniform(index_t location, const Vector3f& val)
{
  bool res = false;
  glUniform3fv(location, 1, val.c_arr());
  GLenum err = glGetError();
  if (err == GL_NO_ERROR)
  {
    res = true;
  }
  else
  {
    getLog() << "ERROR: Unable to set uniform of program" << endl;
  }
  return res;
}

bool Program::setUniform(index_t location, const Vector4f& val)
{
  bool res = false;
  glUniform4fv(location, 1, val.c_arr());
  GLenum err = glGetError();
  if (err == GL_NO_ERROR)
  {
    res = true;
  }
  else
  {
    getLog() << "ERROR: Unable to set uniform of program" << endl;
  }
  return res;
}

bool Program::setUniform(index_t location, const Matrix4f& val)
{
  bool res = false;
  glUniformMatrix4fv(location, 1, GL_FALSE, val.c_arr());
  GLenum err = glGetError();
  if (err == GL_NO_ERROR)
  {
    res = true;
  }
  else
  {
    getLog() << "ERROR: Unable to set uniform of program" << endl;
  }
  return res;
}
*/
} // dada
