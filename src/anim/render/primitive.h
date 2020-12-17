/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <windows.h>

#include <gl/glew.h>

#include "def.h"
#include "anim/animation.h"

namespace spectral {


class primitive {
public:
  primitive( animation *Anim );
  ~primitive();
  virtual void Render();
  // NOTE: Do I need it? virtual void UpdateShaderContext();
  // virtual void SetBuffers( vertex *V, INT *I, INT NoofV, INT NoofI );
  virtual void DeleteBuffers();

protected:
  UINT
    VABuf, VBuf, IBuf,
    NoofV, NoofI;
  animation *Anim;
  // TODO: Add material *Material;

private:
  primitive( const primitive &P ) = delete;
  primitive & operator=( const primitive &P ) = delete;
};


} // End of 'spectral' namespace
