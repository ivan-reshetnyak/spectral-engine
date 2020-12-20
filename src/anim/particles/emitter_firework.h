/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "def.h"
#include "../animation.h"
#include "../particle.h"

namespace spectral {
namespace emitter {


class fireworks : public emitter_t {
public:
  fireworks( animation *Anim, world *World, float LifeTime,
             const vec &Position, float MinSpeed, float MaxSpeed,
             int NumOfParticles,
             const color &Color = color(1, 1, 1) );
  void Release();
  virtual bool IsDead() const override;
  virtual std::shared_ptr<particle_t> Initialize() override;
  virtual void Initialize( std::shared_ptr<particle_t> ToReuse ) override;

protected:
  animation *Anim;
  world *World;
  float LifeTime, MinSpeed, MaxSpeed;
  int NumOfParticles;
  vec Position;
  color Color;
};


} // End of 'emitter' namespace
} // End of 'spectral' namespace
