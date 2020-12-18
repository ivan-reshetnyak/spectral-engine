/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "particle.h"

namespace spectral {


particle::particle( const timer &Timer, float LifeTime ) :
    LifeTime(LifeTime), BirthTime((float)Timer.GetTime()) {
  Update(Timer);
}


void particle::Update( const timer &Timer ) {
}


void particle::Render() {
}


void particle_manager::Update( const timer &Timer ) {
  for (auto &Particle: Particles)
    Particle->Update(Timer);
  Particles.remove_if([]( std::shared_ptr<particle> Particle ) -> bool { return Particle->IsDead(); });
}


void particle_manager::Render() {
  for (auto &Particle: Particles)
    Particle->Render();
}


} // End of 'spectral' namespace
