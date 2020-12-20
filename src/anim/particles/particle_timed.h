/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "def.h"
#include "../particle.h"

namespace spectral {
namespace particle {


class timed : public particle_t {
public:
  timed( const timer &Timer, float LifeTime );
  timed( const timed &&Other );
  timed & operator=( const timed &&Other );
  virtual bool IsDead() const override;
  virtual void Update( const timer &Timer ) override;

protected:
  float BirthTime, LifeTime, Age;
};


} // End of 'particles' namespace
} // End of 'spectral' namespace
