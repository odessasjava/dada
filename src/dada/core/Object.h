//---------------------------------------------------------
//
//  Project:      dada
//  Module:       core
//  File:         Object.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#ifndef DADA_CORE_OBJECT_H
#define DADA_CORE_OBJECT_H

#include "dada/core/MetaInfo.h"

#define DADA_OBJECT(object, super)                                   \
  const dada::MetaInfo& getMetaInfo() const                          \
  {                                                                  \
    return object::getMetaInformation();                             \
  }                                                                  \
  static const dada::MetaInfo& getMetaInformation()                  \
  {                                                                  \
    static dada::MetaInfo mi(#object, &super::getMetaInformation()); \
    return mi;                                                       \
  }
  
namespace dada
{

class Object
{
public:
  const char* getClassName() const;
  bool isInstance(const Object& obj) const;
  bool isKind(const Object& obj) const;
  virtual const MetaInfo& getMetaInfo() const;
  static const MetaInfo& getMetaInformation();
  template<class T> const T* cast() const;
  template<class T> T* cast();
  
protected:
  Object();
  virtual ~Object();
  
private:
  Object(const Object& obj); // disabled
  Object& operator = (const Object& obj); // disabled
};

inline const char* Object::getClassName() const
{
  return getMetaInfo().getName();
}

inline bool Object::isInstance(const Object& obj) const
{
  return getMetaInfo().isInstance(obj.getMetaInfo());
}

inline bool Object::isKind(const Object& obj) const
{
  return getMetaInfo().isKind(obj.getMetaInfo());
}

inline const MetaInfo& Object::getMetaInfo() const
{
  return getMetaInformation();
}

inline const MetaInfo& Object::getMetaInformation()
{
  static MetaInfo mi("Object", NULL);
  return mi;
}

template<class T>
inline const T* Object::cast() const
{
  return getMetaInfo().isKind(T::getMetaInformation()) ? static_cast<const T*>(this) : NULL;
}

template<class T>
inline T* Object::cast()
{
  return getMetaInfo().isKind(T::getMetaInformation()) ? static_cast<T*>(this) : NULL;
}

inline Object::Object()
{
}

inline Object::~Object()
{
}

} // dada

#endif // DADA_CORE_OBJECT_H
