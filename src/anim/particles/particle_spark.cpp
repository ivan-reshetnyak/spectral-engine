/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "../render/vertex.h"
#include "../render/resource/material.h"
#include "../render/resource/tex/tex_png.h"
#include "particle_spark.h"

namespace spectral {
namespace particle {


class spark_vertex : public vertex {
public:
  spark_vertex() = default;


  std::vector<location> GetLayout() override {
    return std::vector<location>();
  }


  int GetSize() override {
    return sizeof(spark_vertex);
  }
};


std::shared_ptr<material> spark::Material;
prim::points spark::Primitive;
world * spark::World = nullptr;


spark::spark( animation *Anim, world *World,
                      const timed &&Timed,
                      const vec &StartPos, const vec &StartVel,
                      const color &Color ) :
    timed(std::move(Timed)), Color(Color), Anim(Anim),
    StartPos(StartPos), StartVel(StartVel) {
  if (!material::Manager.Exists("particle_spark")) {
    this->World = World;
    Material = material::Manager.Add("particle_spark", shader::Manager.Get("spark"));
    Material->
      Add(std::shared_ptr<texture>(new tex::png("Texture", 0, "../assets/textures/spark.png")))->
      SetUniform("Time", &Anim->Timer.Time)->
      SetUniform("g", World->Gravity)->
      SetUniform("Wind", World->Wind)->
      SetUniform("World", &World->Transformation)->
      SetUniform("VP", &Anim->Camera.VP)->
      SetUniform("CameraRight", &Anim->Camera.Right)->
      SetUniform("CameraUp", &Anim->Camera.Up);

    spark_vertex * Vertices = new spark_vertex[1]{ spark_vertex() };
    Primitive.Set(Anim);
    Primitive.Set(std::shared_ptr<geometry>(new geometry(1, Vertices, 1, { 0 })), Material);
  }
}


spark & spark::operator=( const spark &&Other ) {
  timed::operator=(std::move(Other));
  Anim = Other.Anim;
  Color = Other.Color;
  Rotation = Other.Rotation;
  StartPos = Other.StartPos;
  StartVel = Other.StartVel;
  return *this;
}


void spark::Update( const timer &Timer ) {
  timed::Update(Timer);
  Rotation = Timer.Time * (float)Pi * 0.1f;
}


void spark::Render() {
  glDepthMask(false);
  Material->SetUniform("Size", 1.0f);
  Material->SetUniform("Color", Color);
  Material->SetUniform("p0", StartPos);
  Material->SetUniform("v0", StartVel);
  Material->SetUniform("t", Age);
  Material->SetUniform("LifeTime", LifeTime);
  Material->SetUniform("Rotation", Rotation);
  Primitive.Draw();
  glDepthMask(true);
}


fireworks_emitter::fireworks_emitter( animation *Anim, world *World, float LifeTime,
                                      const vec &Position, float MinSpeed, float MaxSpeed,
                                      int NumOfParticles, const color &Color ) :
    Anim(Anim), World(World), LifeTime(LifeTime), Position(Position),
    MinSpeed(MinSpeed), MaxSpeed(MaxSpeed), Color(Color),
    NumOfParticles(NumOfParticles) {
  Release();
}


void fireworks_emitter::Release() {
  for (int i = 0; i < NumOfParticles; ++i)
    Emit();
}


std::shared_ptr<particle_t> fireworks_emitter::Initialize() {
  vec Speed(vec::random());
  while (!Speed == 0)
    Speed = vec::random();
  Speed = Speed.Normalized() * random(MinSpeed, MaxSpeed);

  return std::shared_ptr<spark>(new spark(Anim, World, timed(Anim->Timer, LifeTime), Position, Speed, Color));
}


void fireworks_emitter::Initialize( std::shared_ptr<particle_t> ToReuse ) {
  std::shared_ptr<spark> Ptr = std::dynamic_pointer_cast<spark>(ToReuse);
  vec Speed(vec::random());
  while (!Speed == 0)
    Speed = vec::random();
  Speed = Speed.Normalized() * random(MinSpeed, MaxSpeed);
  *Ptr = std::move(spark(Anim, World, timed(Anim->Timer, LifeTime), Position, Speed, Color));
}


bool fireworks_emitter::IsDead() const {
  return AliveHead == nullptr;
}

} // End of 'particles' namespace
} // End of 'spectral' namespace
