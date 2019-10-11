//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         Shader.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#ifndef DADA_GL_SHADER_H
#define DADA_GL_SHADER_H

#include "dada/core/Object.h"

namespace dada
{

class Shader : public Object
{
public:
  DADA_OBJECT(Shader, Object)
  
  typedef int type_t;
  typedef unsigned int id_t;
  
public:
  Shader(type_t type);
  ~Shader();
  bool isInited() const;
  id_t getID() const;
  bool load(const char* source);
  
private:
  id_t m_id;
};

inline bool Shader::isInited() const
{
  return m_id != 0;
}

inline Shader::id_t Shader::getID() const
{
  return m_id;
}

} // dada

#endif // DADA_GL_SHADER_H
