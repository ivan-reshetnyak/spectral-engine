/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "emitter_firework.h"
#include "particle_spark.h"

namespace spectral {
namespace emitter {


fireworks::fireworks( animation *Anim, world *World, float LifeTime,
                      const vec &Position, float MinSpeed, float MaxSpeed,
                      int NumOfParticles, const color &Color ) :
    Anim(Anim), World(World), LifeTime(LifeTime), Position(Position),
    MinSpeed(MinSpeed), MaxSpeed(MaxSpeed), Color(Color),
    NumOfParticles(NumOfParticles) {
}


void fireworks::Release() {
  for (int i = 0; i < NumOfParticles; ++i)
    Emit();
}


std::shared_ptr<particle_t> fireworks::Initialize() {
  vec Speed(vec::random());
  while (!Speed == 0)
    Speed = vec::random();
  Speed = Speed.Normalized() * random(MinSpeed, MaxSpeed);

  return std::shared_ptr<particle::spark>(
    new particle::spark(Anim, World, particle::timed(Anim->Timer, LifeTime), Position, Speed, Color));
}


void fireworks::Initialize( std::shared_ptr<particle_t> ToReuse ) {
  std::shared_ptr<particle::spark> Ptr = std::dynamic_pointer_cast<particle::spark>(ToReuse);
  vec Speed(vec::random());
  while (!Speed == 0)
    Speed = vec::random();
  Speed = Speed.Normalized() * random(MinSpeed, MaxSpeed);
  *Ptr = std::move(particle::spark(Anim, World, particle::timed(Anim->Timer, LifeTime), Position, Speed, Color));
}


bool fireworks::IsDead() const {
  return AliveHead == nullptr;
}


fireworks * fireworks::Set( const vec &NewPos ) {
  Position = NewPos;
  return this;
}


fireworks * fireworks::Set( const color &NewCol ) {
  Color = NewCol;
  return this;
}


} // End of 'emitter' namespace
} // End of 'spectral' namespace
