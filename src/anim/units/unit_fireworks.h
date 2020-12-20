/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "../animation.h"
#include "../unit.h"
#include "../particles/particle_spark.h"

namespace spectral {
namespace units {


class fireworks : public unit {
public:
  fireworks( animation *Anim );
  void Update() override;
  void Render() override;

private:
  particle_manager ParticleManager;
  std::shared_ptr<particle::fireworks_emitter> Explosion;
  float LastExplosion, Period;
};


} // End of 'units' namespace
} // End of 'spectral' namespace
