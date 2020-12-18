/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "triangle.h"

namespace spectral {
namespace units {


triangle::triangle( animation *Anim, const vec &V1, const vec &V2, const vec &V3 ) : unit(Anim), Primitive(Anim) {
  vertex Vertices[] = {
    vertex(V1, {0, 0, -1}, {V1.X, V1.Y}, color(1, 1, 1, 1)),
    vertex(V2, {0, 0, -1}, {V2.X, V2.Y}, color(1, 1, 1, 1)),
    vertex(V3, {0, 0, -1}, {V3.X, V3.Y}, color(1, 1, 1, 1))
  };
  int Indices[] = {0, 1, 2};
  geometry Geom(3, Vertices, 3, Indices);
  auto Shader = shader::Manager.Get("pass");
  auto Material = material::Manager.Add("default", Shader);
  Primitive.Set(Geom, Material);
}


void triangle::Render() {
  Primitive.Draw();
}

} // End of 'units' namespace
} // End of 'spectral' namespace
