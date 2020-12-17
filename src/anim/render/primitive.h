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


struct tex_coord {
  float U, V;

  tex_coord() = default;
  tex_coord( const float &U, const float &V );
};


struct vertex {
  vec Pos;
  vec Norm;
  color Col;
  tex_coord UV;
  tex_coord Height;
  INT ID;
  // TODO: What were those for? tex_coord P0, P1, H0, H1;

  vertex();
  vertex( const vec &Pos );
};


class primitive {
public:
  primitive( animation *Anim );
  ~primitive();
  virtual void Render();
  // NOTE: Do I need it? virtual void UpdateShaderContext();
  virtual void SetBuffers( vertex *V, INT *I, INT NoofV, INT NoofI );
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
}; /* End of 'prim' class */

} // End of 'spectral' namespace
