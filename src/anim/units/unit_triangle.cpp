/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "unit_triangle.h"

namespace spectral {
namespace units {


triangle::triangle( animation *Anim, const vec &V1, const vec &V2, const vec &V3 ) : unit(Anim), TrianglePrimitive(Anim) {
  vertices::simple * TriangleVertices = new vertices::simple[3];
  TriangleVertices[0] = vertices::simple(V1, {0, 0, -1}, {V1.X, V1.Y}, color(1, 1, 1, 1));
  TriangleVertices[1] = vertices::simple(V2, {0, 0, -1}, {V2.X, V2.Y}, color(1, 1, 1, 1));
  TriangleVertices[2] = vertices::simple(V3, {0, 0, -1}, {V3.X, V3.Y}, color(1, 1, 1, 1));
  int Indices[] = {0, 1, 2};
  auto Shader = shader::Manager.Get("default");
  auto Material = material::Manager.Add("default", Shader);
  TrianglePrimitive.Set(std::shared_ptr<geometry>(new geometry(3, TriangleVertices, 3, Indices)), Material);
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
