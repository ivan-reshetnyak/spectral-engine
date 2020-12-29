/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "glew/glew.h"

#include "util/resource_manager.h"
#include "geometry.h"
#include "vertex.h"

namespace spectral {


class buffer  {
public:
  buffer();
  buffer( const geometry &Geometry );
  void Generate( const geometry &Geometry );
  static void Unbind();
  int GetNumOfIndices() const;
  unsigned GetIndexBuf() const;
  unsigned GetVertexBuf() const;
  unsigned GetVertexArray() const;

private:
  int NumOfI;
  unsigned
    Ind,                                   // Index buffer
    Vert,                                  // Vertex buffer
    VertexArray;                           // Vertex array buffer
};


} // End of 'spectral' namespace
