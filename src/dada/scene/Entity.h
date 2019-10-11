//---------------------------------------------------------
//
//  Project:      dada
//  Module:       scene
//  File:         Entity.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#ifndef DADA_SCENE_ENTITY_H
#define DADA_SCENE_ENTITY_H

#include "dada/scene/Drawable.h"

namespace dada
{

class Entity : public Drawable
{
public:
  virtual void draw();
};

} // dada

#endif // DADA_SCENE_ENTITY_H
