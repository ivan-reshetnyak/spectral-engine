/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/


#include "pch.h"

#include "def.h"
#include "primitive.h"

namespace spectral {


primitive::primitive( animation *Anim ) : Anim(Anim), VBuf(-1), IBuf(-1), VABuf(-1) {
}


primitive::~primitive() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteVertexArrays(1, (GLuint *)&VABuf);
  glDeleteBuffers(1, (GLuint *)&VBuf);
  glDeleteBuffers(1, (GLuint *)&IBuf);
}


void primitive::Render() {
  // TODO: Material->Apply(Ani);
  glBindVertexArray(VABuf);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
  glBindBuffer(GL_ARRAY_BUFFER, VBuf);

  glDrawElements(GL_TRIANGLES, NoofI, GL_UNSIGNED_INT, NULL);
  glUseProgram(0);
}


void primitive::SetBuffers( vertex *V, INT *I, INT NoofV, INT NoofI ) {
  if (VABuf == 0)
    return;

  this->NoofI = NoofI;

  glGenBuffers(1, &VBuf);
  glBindBuffer(GL_ARRAY_BUFFER, VBuf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * NoofV, V, GL_STATIC_DRAW);

  glGenBuffers(1, &IBuf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, I, GL_STATIC_DRAW);

  glGenVertexArrays(1, &VABuf);
  glBindVertexArray(VABuf);

  struct vertex_attrib_array_f {
    int
      Index,
      Size,
      Type;
    bool IsNormalised;
    int Stride;
    const void *Pointer;
  };
  static const vertex_attrib_array_f VertexAttribArraysF[] = {
    { 0, 3, GL_FLOAT, false, sizeof(vertex), OFFSET(vertex, Pos)    },
    { 1, 3, GL_FLOAT, false, sizeof(vertex), OFFSET(vertex, Norm)   },
    { 2, 4, GL_FLOAT, false, sizeof(vertex), OFFSET(vertex, Col)    },
    { 3, 2, GL_FLOAT, false, sizeof(vertex), OFFSET(vertex, UV)     },
    { 4, 2, GL_FLOAT, false, sizeof(vertex), OFFSET(vertex, Height) }};
  for (const auto &it : VertexAttribArraysF) {
    glVertexAttribPointer(it.Index, it.Size, it.Type, it.IsNormalised, it.Stride, it.Pointer);
    glEnableVertexAttribArray(it.Index);
  }
  glVertexAttribIPointer(5, 1, GL_INT,          sizeof(vertex), OFFSET(vertex, ID));
  glEnableVertexAttribArray(5);

  /* TODO: What are those?
  glVertexAttribPointer( 6, 2, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, P0));
  glVertexAttribPointer( 7, 2, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, P1));
  glVertexAttribPointer( 8, 2, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, H0));
  glVertexAttribPointer( 9, 2, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, H1));
  glEnableVertexAttribArray(6);
  glEnableVertexAttribArray(7);
  glEnableVertexAttribArray(8);
  glEnableVertexAttribArray(9);
  */

  /* Cleanup just in case */
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void primitive::DeleteBuffers() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  if (VABuf != -1)
    glDeleteVertexArrays(1, (GLuint *)&VABuf);
  if (VBuf != -1)
    glDeleteBuffers(1, (GLuint *)&VBuf);
  if (IBuf != -1)
    glDeleteBuffers(1, (GLuint *)&IBuf);
}


} // End of 'spectral' namespace
