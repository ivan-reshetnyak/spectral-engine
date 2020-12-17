/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "vertex.h"

namespace spectral {


tex_coord::tex_coord( const float &U, const float &V ) : U(U), V(V) {
}


vertex::vertex() {
}


vertex::vertex( const vec &Position,
                const vec &Normal,
                const tex_coord &Tex,
                const color &Color ) :
    Position(Position), Normal(Normal),
    Tex(Tex), Color(Color) {
}


vertex::vertex( const vertex &Other ) {
  Position = Other.Position;
  Normal   = Other.Normal;
  Tex      = Other.Tex;
  Color    = Other.Color;
}


} // End of 'spectral' namespace
