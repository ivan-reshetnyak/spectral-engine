/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "def.h"
#include "../animation.h"
#include "../render/prim/trimesh.h"
#include "../unit.h"

namespace spectral {
namespace units {


class triangle : public unit {
public:
  triangle( animation *Anim, const vec &V1, const vec &V2, const vec &V3 );
  void Render() override;

private:
  prim::trimesh Primitive;
};


} // End of 'units' namespace
} // End of 'spectral' namespace
