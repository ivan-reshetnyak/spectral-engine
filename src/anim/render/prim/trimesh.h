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


class trimesh : public primitive {
public:
  trimesh( animation *Anim );
  trimesh( animation *Anim, std::shared_ptr<geometry> Geometry, std::shared_ptr<material> Material );
  ~trimesh();

protected:
  virtual void Render() override;
};

} // End of 'prim' namespace
} // End of 'spectral' namespace
