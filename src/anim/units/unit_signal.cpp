/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "../particle.h"
#include "../render/resource/tex/tex_png.h"
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
             timed(Anim->Timer, LifeTime), Position(Start), Speed(Speed), Anim(Anim) {
    if (!material::Manager.Exists("unit_signal_billboard")) {
      auto Shader = shader::Manager.Get("default_particle");
      std::shared_ptr<texture> Texture(new tex::png("Texture", 0, "../assets/textures/smoke.png"));
      Material = material::Manager.Add("unit_signal_billboard", Shader);
      Material->
        Add(Texture)->
        SetUniform("Time", &Anim->Timer.Time)->
        SetUniform("World", &Anim->World)->SetUniform("VP", &Anim->Camera.VP)->
        SetUniform("CameraRight", &Anim->Camera.Right)->
        SetUniform("CameraUp", &Anim->Camera.Up);

      bb_vertex * Vertices = new bb_vertex[1];
      Vertices[0] = bb_vertex(Start, 0.3f);
      Primitive.Set(Anim);
      Primitive.Set(std::shared_ptr<geometry>(new geometry(1, Vertices, 1, { 0 })), Material);
    }
    Rotation = (float)rand() / RAND_MAX * (float)Pi;
  }


  billboard & operator=( const billboard &&Other ) {
    timed::operator=(std::move(Other));
    Anim = Other.Anim;
    Position = Other.Position;
    Speed = Other.Speed;
    Rotation = Other.Rotation;
    return *this;
  }


  void Update( const timer &Timer ) override {
    timed::Update(Timer);
    Position += Speed * Timer.DeltaTime;
    Rotation += (float)!Speed * Timer.DeltaTime;
  }


  void Render() override {
    glDepthMask(false);
    Material->SetUniform("Age", Age);
    Material->SetUniform("LifeTime", LifeTime);
    Anim->World = matrix::Translation(Position.X, Position.Y, Position.Z) * matrix::RotationZ(Rotation);
    Primitive.Draw();
    Anim->World = matrix();
    glDepthMask(true);
  }

private:
  static std::shared_ptr<material> Material;
  static prim::points Primitive;
  animation *Anim;
  vec Position, Speed;
  float Rotation;
};


std::shared_ptr<material> billboard::Material;
prim::points billboard::Primitive;


class bb_emitter : public emitter {
public:
  bb_emitter( animation *Anim, float Period, float LifeTime, const vec &Position, const vec &Speed ) :
      LastEmission(Anim->Timer.Time), Anim(Anim),
      Period(Period), LifeTime(LifeTime),
      Position(Position), Speed(Speed) {
  }


  virtual bool IsDead() const {
    return false;
  }


  virtual std::shared_ptr<particle_t> Initialize() override {
    vec SpeedShifted = Speed + vec(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX) * 0.1f;
    return std::shared_ptr<billboard>(new billboard(Anim, LifeTime, Position, SpeedShifted));
  }


  virtual void Initialize( std::shared_ptr<particle_t> ToReuse ) override {
    std::shared_ptr<billboard> Ptr = std::dynamic_pointer_cast<billboard>(ToReuse);
    vec SpeedShifted = Speed + vec(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX) * 0.1f;
    *Ptr = std::move(billboard(Anim, LifeTime, Position, SpeedShifted));
  }


  virtual void Update( const timer &Timer ) override {
    emitter::Update(Timer);

    float Passed = Timer.Time - LastEmission;

    int ToEmit = (int)(Passed / Period);
    if (ToEmit <= 0)
      return;
    for (int i = 0; i < ToEmit; i++)
      Emit();
    LastEmission = Timer.Time;
  }

private:
  float Period, LastEmission, LifeTime;
  vec Position, Speed;
  animation *Anim;
};


signal::signal( animation *Anim, const vec &Pos, const vec &Speed ) : unit(Anim) {
  ParticleManager << std::shared_ptr<emitter>(new bb_emitter(Anim, 0.005f, 2.5f, Pos, Speed));
}


void signal::Update() {
  ParticleManager.Update(Anim->Timer);
}


void signal::Render() {
  ParticleManager.Render();
}


} // End of 'particles' namespace
} // End of 'spectral' namespace
