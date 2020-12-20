/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "gl/glew.h"

#include "points.h"

namespace spectral {
namespace prim {


points::points( animation *Anim ) : primitive(Anim) {
}


points::points( animation *Anim, std::shared_ptr<geometry> Geometry,
                std::shared_ptr<material> Material ) : primitive(Anim, Geometry, Material) {
}


points::~points() {
}


points & points::operator=( const points &&Other ) {
  primitive::operator=(std::move(Other));
  return *this;
}


void points::Render() {
  glBindVertexArray(Buffer.GetVertexArray());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer.GetIndexBuf());
  glDrawElements(GL_POINTS, Buffer.GetNumOfIndices(), GL_UNSIGNED_INT, nullptr);
}

} // End of 'prim' namespace
} // End of 'spectral' namespace
