/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "def.h"
#include "anim/animation.h"
#include "../primitive.h"

namespace spectral {
namespace prim {


class trimesh : public primitive
{
public:
  trimesh( animation *Anim );
  ~trimesh();
  void CreateQuad( const vec &P0, const vec &P1, const vec &P2, const vec &P3 );
};

} // End of 'prim' namespace
} // End of 'spectral' namespace
