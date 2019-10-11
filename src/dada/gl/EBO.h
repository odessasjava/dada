//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         EBO.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#pragma once

#include "dada/core/Object.h"

namespace dada
{

class EBO : public Object
{
public:
  DADA_OBJECT(EBO, Object)
  
  typedef unsigned int id_t;
  
public:
  EBO();
  ~EBO();
  bool isInited() const;
  id_t getID() const;
  bool bind();
  bool load(unsigned int size, const void* data);
  
private:
  id_t m_id;
};

inline bool EBO::isInited() const
{
  return m_id != 0;
}

inline EBO::id_t EBO::getID() const
{
  return m_id;
}

} // dada
