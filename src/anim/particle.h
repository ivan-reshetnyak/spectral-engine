/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <forward_list>
#include <memory>

#include "timer.h"

namespace spectral {


class particle {
public:
  virtual bool IsDead() const = 0;
  virtual void Update( const timer &Timer );
  virtual void Render();
};


class emitter {
public:
  virtual bool IsDead() const = 0;
  virtual void Emit( const timer &Timer, std::forward_list<std::shared_ptr<particle>> &Where ) = 0;
};


class particle_manager {
public:
  void Update( const timer &Timer );
  void Render();
private:
  std::forward_list<std::shared_ptr<emitter>> Emitters;
  std::forward_list<std::shared_ptr<particle>> Particles;
};


} // End of 'spectral' namespace
