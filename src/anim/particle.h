/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

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


class emitter {
public:
  emitter();


  virtual ~emitter() {
    while (AliveHead != nullptr) {
      entry *ToDelete = AliveHead;
      AliveHead = AliveHead->Next;
      delete ToDelete;
    }

    while (Dead != nullptr) {
      entry *ToDelete = Dead;
      Dead = Dead->Next;
      delete ToDelete;
    }
  }


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

  void Emit() {
    entry *ToAdd;
    if (Dead != nullptr) {
      ToAdd = Dead;
      Dead = Dead->Next;
      Initialize(ToAdd->Particle);
      ToAdd->Next = nullptr;
    } else
      ToAdd = new entry{ Initialize(), nullptr };

    if (AliveTail == nullptr) {
      AliveHead = AliveTail = ToAdd;
    } else {
      AliveTail->Next = ToAdd;
      AliveTail = ToAdd;
    }
  }
};


class particle_manager {
public:
  void Update( const timer &Timer );
  void Render();
  particle_manager & operator<<( std::shared_ptr<emitter> Emitter );

private:
  std::forward_list<std::shared_ptr<emitter>> Emitters;
};


} // End of 'spectral' namespace
