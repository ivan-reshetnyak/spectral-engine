/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "../particle.h"
#include "unit_signal.h"

namespace spectral {
namespace units {


class bb_vertex : public vertex {
public:
  vec Position;
  float Size;

  bb_vertex() {
  }


  bb_vertex( const vec &Position, float Size ) : Position(Position), Size(Size) {
  }


  std::vector<location> GetLayout() override {
    std::vector<location> Layout;
    Layout.push_back(location({ 0, 3, GL_FLOAT, false, sizeof(bb_vertex), OFFSET(bb_vertex, Position) }));
    Layout.push_back(location({ 1, 1, GL_FLOAT, false, sizeof(bb_vertex), OFFSET(bb_vertex, Size) }));
    return Layout;
  }


  int GetSize() override {
    return sizeof(bb_vertex);
  }
};

class billboard : public particle::timed {
public:
  billboard( animation *Anim, float LifeTime, const vec &Start, const vec &Speed ) :
              timed(Anim->GetTimer(), LifeTime), Position(Start), Speed(Speed), Primitive(Anim), Anim(Anim) {
      bb_vertex * Vertices = new bb_vertex[1];
    Vertices[0] = bb_vertex(Start, 0.3f);
    auto Shader = shader::Manager.Get("default_particle");
    auto Material = material::Manager.Add("unit_signal_billboard", Shader);
    Primitive.Set(std::shared_ptr<geometry>(new geometry(1, Vertices, 1, { 0 })), Material);
  }


  void Update( const timer &Timer ) override {
    timed::Update(Timer);
    Position += Speed * (float)Timer.GetDeltaTime();
  }


  void Render() override {
    Anim->World = matrix::Translation(Position.X, Position.Y, Position.Z);
    Primitive.Draw();
    Anim->World = matrix();
  }

private:
  animation *Anim;
  vec Position, Speed;
  prim::points Primitive;
};

class bb_emitter : public emitter {
public:
  bb_emitter( animation *Anim, float Period, float LifeTime, const vec &Position, const vec &Speed ) :
      LastEmission((float)Anim->GetTimer().GetTime()), Anim(Anim),
      Period(Period), LifeTime(LifeTime),
      Position(Position), Speed(Speed) {
  }


  virtual bool IsDead() const {
    return false;
  }


  virtual void Emit( const timer &Timer, std::forward_list<std::shared_ptr<particle_t>> &Where ) {
    if (Timer.GetTime() - LastEmission < Period)
      return;
    LastEmission = (float)Timer.GetTime();
    Where.push_front(std::shared_ptr<particle_t>(new billboard(Anim, LifeTime, Position, Speed)));
  }

private:
  float Period, LastEmission, LifeTime;
  vec Position, Speed;
  animation *Anim;
};


signal::signal( animation *Anim, const vec &Pos, const vec &Speed ) : unit(Anim) {
  ParticleManager << std::shared_ptr<emitter>(new bb_emitter(Anim, 0.5, 3.0, vec(0, 0, 0), vec(0, 1, 0)));
}


void signal::Update() {
  ParticleManager.Update(Anim->GetTimer());
}


void signal::Render() {
  ParticleManager.Render();
}


} // End of 'particles' namespace
} // End of 'spectral' namespace
