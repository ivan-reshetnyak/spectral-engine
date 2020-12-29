/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "../../def.h"
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
  fireworks * Set( const vec &NewPos );
  fireworks * Set( const color &NewCol );

protected:
  animation *Anim;
  world *World;
  float LifeTime, MinSpeed, MaxSpeed;
  vec Position;
  color Color;

  int BurstSize;
};


} // End of 'emitter' namespace
} // End of 'spectral' namespace
