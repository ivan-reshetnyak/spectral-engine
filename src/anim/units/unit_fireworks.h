/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "../animation.h"
#include "../unit.h"
#include "../ui/ui_button.h"
#include "../particles/emitter_firework.h"

namespace spectral {
namespace units {


class fireworks : public unit {
public:
  fireworks( animation *Anim );
  void Update() override;
  void Render() override;

private:
  particle_manager ParticleManager;
  std::shared_ptr<emitter::fireworks> Explosion;
  float LastExplosion, Period;
  std::shared_ptr<ui::button> LaunchButton;

  void Launch();
};


} // End of 'units' namespace
} // End of 'spectral' namespace
