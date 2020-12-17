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
}


} // End of 'prim' namespace
} // End of 'spectral' namespace
