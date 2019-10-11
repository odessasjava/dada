//---------------------------------------------------------
//
//  Project:      dada
//  Module:       scene
//  File:         Drawable.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#ifndef DADA_SCENE_DRAWABLE_H
#define DADA_SCENE_DRAWABLE_H

namespace dada
{

class Drawable
{
public:
  virtual void draw() = 0;
};

} // dada

#endif // DADA_SCENE_DRAWABLE_H
