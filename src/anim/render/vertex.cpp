/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "vertex.h"

namespace spectral {


tex_coord::tex_coord( const float &U, const float &V ) : U(U), V(V) {
}


namespace vertices {


simple::simple() {
}


simple::simple( const vec &Position,
                const vec &Normal,
                const tex_coord &Tex,
                const color &Color ) :
    Position(Position), Normal(Normal),
    Tex(Tex), Color(Color) {
}


simple::simple( const simple &Other ) {
  Position = Other.Position;
  Normal   = Other.Normal;
  Tex      = Other.Tex;
  Color    = Other.Color;
}


std::vector<simple::location> simple::GetLayout() {
  std::vector<simple::location> Layout;
  Layout.push_back(location({ 0, 3, GL_FLOAT, false, sizeof(simple), OFFSET(simple, Position) }));
  Layout.push_back(location({ 1, 3, GL_FLOAT, false, sizeof(simple), OFFSET(simple, Normal) }));
  Layout.push_back(location({ 2, 4, GL_FLOAT, false, sizeof(simple), OFFSET(simple, Color) }));
  Layout.push_back(location({ 3, 2, GL_FLOAT, false, sizeof(simple), OFFSET(simple, Tex) }));
  return Layout;
}


int simple::GetSize() {
  return sizeof(simple);
}


} // End of 'vertices' namespace
} // End of 'spectral' namespace
