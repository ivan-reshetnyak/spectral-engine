/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "def.h"

namespace spectral {


struct tex_coord {
  float U, V;

  tex_coord() = default;
  tex_coord( const float &U, const float &V );
};


struct vertex {
  vec
    Position,
    Normal;
  tex_coord Tex;
  color Color;

  vertex();
  vertex( const vertex &Other );
  vertex( const vec &Position,
          const vec &Normal = { 0, 1, 0 },
          const tex_coord &Tex = { 0, 0 },
          const color &Color = color(1, 1, 1, 1) );
};


} // End of 'spectral' namespace
