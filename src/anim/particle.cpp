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


emitter_t::emitter_t() : AliveHead(nullptr), AliveTail(nullptr), Dead(nullptr) {
}


void emitter_t::Update( const timer &Timer ) {
  entry *Entry = AliveHead;
  while (Entry != nullptr) {
    Entry->Particle->Update(Timer);
    Entry = Entry->Next;
  }

  while (AliveHead != nullptr && AliveHead->Particle->IsDead()) {
    entry *ToDie = AliveHead;
    AliveHead = AliveHead->Next;
    ToDie->Next = Dead;
    Dead = ToDie;
  }

  if (AliveHead == nullptr)
    AliveTail = nullptr;
}


void emitter_t::Render() {
  entry *Entry = AliveHead;
  while (Entry != nullptr) {
    Entry->Particle->Render();
    Entry = Entry->Next;
  }
}


void particle_manager::Update( const timer &Timer ) {
  for (auto &Emitter : Emitters)
    Emitter->Update(Timer);
  Emitters.remove_if([]( std::shared_ptr<emitter_t> Emitter ) -> bool { return Emitter->IsDead(); });
}


void particle_manager::Render() {
  for (auto &Emitter: Emitters)
    Emitter->Render();
}


particle_manager & particle_manager::operator<<( std::shared_ptr<emitter_t> Emitter ) {
  Emitters.push_front(Emitter);
  return *this;
}

} // End of 'spectral' namespace
