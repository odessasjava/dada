//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         Shader.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/gl/Shader.h"
#include "dada/gl/GL.h"
#include "dada/core/Log.h"

namespace dada
{

Shader::Shader(type_t type) :
  Object(),
  m_id(0)
{
  m_id = glCreateShader(type);
  GLenum err = glGetError();
  if (m_id == 0 || err != GL_NO_ERROR)
  {
    getLog() << "ERROR: Requested unsupported type of shader " << type << endl;
  }
}

Shader::~Shader()
{
  glDeleteShader(m_id);
}

bool Shader::load(const char* source)
{
  glShaderSource(m_id, 1, &source, NULL);
  glCompileShader(m_id);
  
  GLint compiled = 0;
  glGetShaderiv(m_id, GL_COMPILE_STATUS, &compiled);
  if (compiled == 0)
  {
    GLint length = 0;
    glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &length);
    if (length > 1)
    {
      getLog() << "ERROR: While compiling shader " << m_id << endl;
      char* buf = new char[length];
      glGetShaderInfoLog(m_id, length, NULL, buf);
      getLog() << buf << endl;
      delete buf;
    }
  }
  return compiled != 0;
}

} // dada
