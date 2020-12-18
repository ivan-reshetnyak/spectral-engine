/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "triangle.h"

namespace spectral {
namespace units {


triangle::triangle( animation *Anim, const vec &V1, const vec &V2, const vec &V3 ) : unit(Anim), TrianglePrimitive(Anim) {
  vertex TriangleVertices[] = {
    vertex(V1, {0, 0, -1}, {V1.X, V1.Y}, color(1, 1, 1, 1)),
    vertex(V2, {0, 0, -1}, {V2.X, V2.Y}, color(1, 1, 1, 1)),
    vertex(V3, {0, 0, -1}, {V3.X, V3.Y}, color(1, 1, 1, 1))
  };
  int Indices[] = {0, 1, 2};
  geometry Geom(3, TriangleVertices, 3, Indices);
  auto Shader = shader::Manager.Get("default");
  auto Material = material::Manager.Add("default", Shader);
  TrianglePrimitive.Set(Geom, Material);
}


void triangle::Render() {
  TrianglePrimitive.Draw();
}


void triangle::Update() {
  Anim->World = matrix::Translation((float)(sin(Anim->GetTimer().GetTime()) * 1),
                                    (float)(cos(Anim->GetTimer().GetTime()) * 1),
                                    (float)(cos(Anim->GetTimer().GetTime()) * sin(Anim->GetTimer().GetTime()) * 1)) *
    matrix::RotationY(Anim->GetTimer().GetTime() * 90);;
}


} // End of 'units' namespace
} // End of 'spectral' namespace
