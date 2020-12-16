/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

namespace spectral {


struct tex_coord {
  float U, V;

  tex_coord() = default;
  tex_coord( const float &U, const float &V );
};


/*
TODO: struct vertex {
  vecf Pos;
  vecf Norm;
  color Col;
  uv UV;
  uv Height;
  INT ID;
  uv P0, P1, H0, H1;

  vertex( VOID ) {
  }

  vertex( const vecf &Pos ) : Pos(Pos) {
  }
};
*/


} // End of 'spectral' namespace
