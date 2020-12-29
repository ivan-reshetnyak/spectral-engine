/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "../../def.h"
#include "../render/prim/points.h"
#include "particle_timed.h"

namespace spectral {
namespace particle {


class spark : public timed {
public:
  spark( animation *Anim, world *World,
             const timed &&Timed,
             const vec &StartPos, const vec &StartVel,
             const color &Color = color(1, 1, 1, 1));
  spark & operator=( const spark &&Other );
  virtual void Update( const timer &Timer ) override;
  virtual void Render() override;

protected:
  animation *Anim;
  color Color;
  float Rotation;
  vec StartPos, StartVel;
  static std::shared_ptr<material> Material;
  static prim::points Primitive;
  static world *World;
};


} // End of 'particle' namespace
} // End of 'spectral' namespace
