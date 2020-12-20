/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "gl/glew.h"

#include "trimesh.h"

namespace spectral {
namespace prim {


trimesh::trimesh( animation *Anim ) : primitive(Anim) {
}


trimesh::trimesh( animation *Anim, std::shared_ptr<geometry> Geometry,
                  std::shared_ptr<material> Material ) : primitive(Anim, Geometry, Material) {
}


trimesh::~trimesh() {
}


void trimesh::Render() {
  glBindVertexArray(Buffer.GetVertexArray());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer.GetIndexBuf());
  glDrawElements(GL_TRIANGLES, Buffer.GetNumOfIndices(), GL_UNSIGNED_INT, nullptr);
}

} // End of 'prim' namespace
} // End of 'spectral' namespace
