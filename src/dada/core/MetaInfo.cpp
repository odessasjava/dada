//---------------------------------------------------------
//
//  Project:      dada
//  Module:       core
//  File:         MetaInfo.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/core/MetaInfo.h"

namespace dada
{

MetaInfo::MetaInfo(const char* name, const MetaInfo* parent) :
  m_name(name),
  m_parent(parent)
{
}

bool MetaInfo::isInstance(const MetaInfo& mi) const
{
  return this == &mi;
}

bool MetaInfo::isKind(const MetaInfo& mi) const
{
  const MetaInfo* iter = this;
  do
  {
    if (iter->isInstance(mi))
    {
      return true;
    }
    iter = iter->m_parent;
  } while (iter != NULL);
  return false;
}

} // dada
