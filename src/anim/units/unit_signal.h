/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "def.h"
#include "../animation.h"
#include "../particles/particle_timed.h"
#include "../render/prim/points.h"
#include "../unit.h"

namespace spectral {
namespace units {


class signal : public unit {
public:
  signal( animation *Anim, const vec &Pos, const vec &Speed );
  void Update() override;
  void Render() override;

private:
  particle_manager ParticleManager;
};


} // End of 'units' namespace
} // End of 'spectral' namespace
