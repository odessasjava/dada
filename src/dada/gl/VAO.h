//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         VAO.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#pragma once

#include "dada/core/Object.h"

namespace dada
{

class VAO : public Object
{
public:
  DADA_OBJECT(VAO, Object)
  
  typedef unsigned int id_t;
  
public:
  VAO();
  ~VAO();
  bool isInited() const;
  id_t getID() const;
  bool bind();
  
private:
  id_t m_id;
};

inline bool VAO::isInited() const
{
  return m_id != 0;
}

inline VAO::id_t VAO::getID() const
{
  return m_id;
}

} // dada
