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


emitter_t::~emitter_t() {
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


void emitter_t::Emit() {
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


void emitter_t::Update( const timer &Timer ) {
  NumOfParticles = 0;
  entry *Entry = AliveHead;
  while (Entry != nullptr) {
    Entry->Particle->Update(Timer);
    ++NumOfParticles;
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
