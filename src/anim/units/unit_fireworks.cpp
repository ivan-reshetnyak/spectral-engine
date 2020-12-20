/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "unit_fireworks.h"

namespace spectral {
namespace units {


fireworks::fireworks( animation *Anim ) : unit(Anim) {
  Explosion = std::shared_ptr<particle::fireworks_emitter>(
    new particle::fireworks_emitter(Anim, &Anim->World, 2.5f, vec(0, 50, 0),
                                    10.f, 15.f, 250, color(1.f, 1.f, 1.f)));
  ParticleManager << Explosion;
  LastExplosion = Anim->Timer.Time;
  Period = 0.5;
}


void fireworks::Update() {
  ParticleManager.Update(Anim->Timer);
  if (Explosion->IsDead() && Anim->Timer.Time - LastExplosion > Period) {
    ParticleManager << Explosion;
    Explosion->Release();
    LastExplosion = Anim->Timer.Time;
  }
}


void fireworks::Render() {
  ParticleManager.Render();
}


} // End of 'units' namespace
} // End of 'spectral' namespace
