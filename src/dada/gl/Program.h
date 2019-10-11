//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         Program.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#ifndef DADA_GL_PROGRAM_H
#define DADA_GL_PROGRAM_H

#include "dada/core/Object.h"


//#include "dada\core\Matrix4f.h"
//#include "dada\core\Shader.h"
//#include "dada\core\Vector3f.h"
//#include "dada\core\Vector4f.h"

namespace dada
{

class Shader;

class Program : public Object
{
public:
  DADA_OBJECT(Program, Object)
  
  typedef unsigned int id_t;
  typedef unsigned int index_t;
  
  static const index_t INVALID_INDEX = static_cast<index_t>(-1);
  
public:
  Program();
  ~Program();
  bool isInited() const;
  id_t getID() const;
  bool isValid() const;
  bool attach(Shader& sh);
  bool link();
  index_t findAttributeLocation(const char* name) const;
  index_t findUniformLocation(const char* name) const;
  bool use();
  //bool setUniform(index_t location, int val);
  //bool setUniform(index_t location, float val);
  //bool setUniform(index_t location, const Vector3f& val);
  //bool setUniform(index_t location, const Vector4f& val);
  //bool setUniform(index_t location, const Matrix4f& val);
  
private:
  id_t m_id;
  bool m_valid;
};

inline bool Program::isInited() const
{
  return m_id != 0;
}

inline Program::id_t Program::getID() const
{
  return m_id;
}

inline bool Program::isValid() const
{
  return m_valid;
}

} // dada

#endif // DADA_GL_PROGRAM_H
