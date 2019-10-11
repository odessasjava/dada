//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         VBO.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#pragma once

#include "dada/core/Object.h"

namespace dada
{

class VBO : public Object
{
public:
  DADA_OBJECT(VBO, Object)
  
  typedef unsigned int id_t;
  
public:
  VBO();
  ~VBO();
  bool isInited() const;
  id_t getID() const;
  bool bind();
  bool load(unsigned int size, const void* data);
  
private:
  id_t m_id;
};

inline bool VBO::isInited() const
{
  return m_id != 0;
}

inline VBO::id_t VBO::getID() const
{
  return m_id;
}

} // dada
