/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <forward_list>
#include <memory>

#include "timer.h"

namespace spectral {


class particle_t {
public:
  virtual bool IsDead() const = 0;
  virtual void Update( const timer &Timer );
  virtual void Render();
};


class emitter {
public:
  virtual bool IsDead() const = 0;
  virtual void Emit( const timer &Timer, std::forward_list<std::shared_ptr<particle_t>> &Where ) = 0;
};


class particle_manager {
public:
  void Update( const timer &Timer );
  void Render();
  particle_manager & operator<<( std::shared_ptr<emitter> Emitter );

private:
  std::forward_list<std::shared_ptr<emitter>> Emitters;
  std::forward_list<std::shared_ptr<particle_t>> Particles;
};


} // End of 'spectral' namespace
