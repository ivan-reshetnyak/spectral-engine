/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "particle.h"

namespace spectral {


void particle_t::Update( const timer &Timer ) {
}


void particle_t::Render() {
}


void particle_manager::Update( const timer &Timer ) {
  Emitters.remove_if([]( std::shared_ptr<emitter> Emitter ) -> bool { return Emitter->IsDead(); });
  for (auto &Emitter : Emitters)
    Emitter->Emit(Timer, Particles);

  for (auto &Particle : Particles)
    Particle->Update(Timer);
  Particles.remove_if([]( std::shared_ptr<particle_t> Particle ) -> bool { return Particle->IsDead(); });
}


void particle_manager::Render() {
  for (auto &Particle: Particles)
    Particle->Render();
}


particle_manager & particle_manager::operator<<( std::shared_ptr<emitter> Emitter ) {
  Emitters.push_front(Emitter);
  return *this;
}

} // End of 'spectral' namespace
