//---------------------------------------------------------
//
//  Project:      dada
//  Module:       core
//  File:         MetaInfo.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#ifndef DADA_CORE_METAINFO_H
#define DADA_CORE_METAINFO_H

#include "dada/core/common.h"

namespace dada
{

class MetaInfo
{
public:
  MetaInfo(const char* name, const MetaInfo* parent);
  const char* getName() const;
  const MetaInfo* getParent() const;
  bool isInstance(const MetaInfo& mi) const;
  bool isKind(const MetaInfo& mi) const;
  
private:
  MetaInfo();
  MetaInfo(const MetaInfo& mi);
  MetaInfo& operator = (const MetaInfo& mi);
  
  const char* m_name;
  const MetaInfo* m_parent;
};

inline const char* MetaInfo::getName() const
{
  return m_name;
}

inline const MetaInfo* MetaInfo::getParent() const
{
  return m_parent;
}

} // dada

#endif // DADA_CORE_METAINFO_H
