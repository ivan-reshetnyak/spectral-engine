/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "buffer.h"

namespace spectral {


void buffer::Generate( const geometry &Geometry ) {
  if (VertexArray != 0)
    return;

  /* Vertex buffer */
  glGenBuffers(1, &Vert);                            // Generate free buffer name
  glBindBuffer(GL_ARRAY_BUFFER, Vert);               // Bind buffer
  glBufferData(GL_ARRAY_BUFFER,
              sizeof(vertex) * Geometry.NumOfV,
              Geometry.Vertices, GL_STATIC_DRAW);  // Set data

  /* Index buffer */
  glGenBuffers(1, &Ind);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ind);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                sizeof(INT) * Geometry.NumOfI,
                Geometry.Indices, GL_STATIC_DRAW);

  /* Vertex array buffer */
  glGenVertexArrays(1, &VertexArray);
  glBindVertexArray(VertexArray);

  /* Set shader layout */
  

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  NumOfI = Geometry.NumOfI;
}

buffer::buffer() : Ind(0), Vert(0), VertexArray(0) {
}

buffer::buffer( const geometry &Geometry ) : buffer() {
  Generate(Geometry);
}


void buffer::Unbind() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


int buffer::GetNumOfIndices() const {
  return NumOfI;
}


unsigned buffer::GetIndexBuf() const {
  return Ind;
}


unsigned buffer::GetVertexBuf() const {
  return Vert;
}


unsigned buffer::GetVertexArray() const {
  return VertexArray;
}


} // End of 'spectral' namespace
