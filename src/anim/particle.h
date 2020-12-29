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
  virtual ~particle_t() {
  }

  virtual bool IsDead() const = 0;
  virtual void Update( const timer &Timer );
  virtual void Render();
};


class emitter_t {
public:
  int NumOfParticles;

  emitter_t();
  virtual ~emitter_t();
  virtual bool IsDead() const = 0;
  virtual void Update( const timer &Timer );
  virtual void Render();
  virtual std::shared_ptr<particle_t> Initialize() = 0;
  virtual void Initialize( std::shared_ptr<particle_t> ToReuse ) = 0;

protected:
  struct entry {
    std::shared_ptr<particle_t> Particle;
    entry *Next;
  };
  entry *AliveHead, *AliveTail, *Dead;

  void Emit();
};


class particle_manager {
public:
  void Update( const timer &Timer );
  void Render();
  particle_manager & operator<<( std::shared_ptr<emitter_t> Emitter );

private:
  std::forward_list<std::shared_ptr<emitter_t>> Emitters;
};


} // End of 'spectral' namespace
