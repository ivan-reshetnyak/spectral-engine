/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"
#include "trimesh.h"

namespace spectral {
namespace prim {


trimesh::trimesh( animation *Anim ) : primitive(Anim) {
}


trimesh::~trimesh() {
}


void trimesh::CreateQuad( const vec &P0, const vec &P1, const vec &P2, const vec &P3 ) {
  DeleteBuffers();
  vertex v[4] = { P0, P1, P2, P3 };
  INT i[6] = { 0, 1, 2, 0, 2, 3 };
  SetBuffers(v, i, 4, 6);
}


} // End of 'prim' namespace
} // End of 'spectral' namespace
