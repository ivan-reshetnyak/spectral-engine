/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "def.h"
#include "../render/prim/points.h"
#include "particle_timed.h"

namespace spectral {
namespace particle {


class fireworks : public timed {
public:
  fireworks( animation *Anim, world *World,
             const timed &&Timed,
             const vec &StartPos, const vec &StartVel,
             const color &Color = color(1, 1, 1, 1));
  fireworks & operator=( const fireworks &&Other );
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


class fireworks_emitter : public emitter {
public:
  fireworks_emitter( animation *Anim, world *World, float LifeTime,
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


} // End of 'particles' namespace
} // End of 'spectral' namespace
