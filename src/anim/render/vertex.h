/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <vector>

#include "def.h"

namespace spectral {


struct tex_coord {
  float U, V;

  tex_coord() = default;
  tex_coord( const float &U, const float &V );
};


class vertex {
public:
  struct location {
    int
      Index,
      Size,
      Type;
    bool IsNormalised;
    int Stride;
    const void *Pointer;
  };

  virtual std::vector<location> GetLayout() = 0;
  virtual int GetSize() = 0;
};


namespace vertices {


class simple : public vertex {
public:
  vec
    Position,
    Normal;
  color Color;
  tex_coord Tex;

  simple();
  simple( const vec &Position, const vec &Normal,
          const tex_coord &Tex, const color &Color );
  simple( const simple &Other );
  virtual std::vector<location> GetLayout() override;
  virtual int GetSize() override;
};


} // End of 'vertices' namespace
} // End of 'spectral' namespace
