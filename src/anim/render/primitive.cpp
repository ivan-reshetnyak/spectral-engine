/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/


#include "pch.h"

#include "def.h"
#include "primitive.h"
#include "resource/shader.h"

namespace spectral {


primitive::primitive( animation *Anim ) : Anim(Anim) {
}


primitive::primitive( animation *Anim, std::shared_ptr<geometry> Geometry, std::shared_ptr<material> Material ) :
    primitive(Anim) {
  Set(Geometry, Material);
}


primitive::~primitive() {
}


void primitive::Draw() {
  shader::SetLayout(Geometry->Vertices);
  Material->Apply(Anim);

  Render();

  buffer::Unbind();
  shader::Disable();
}


void primitive::Set( std::shared_ptr<geometry> Geometry, std::shared_ptr<material> Material ) {
  this->Geometry = Geometry;
  Buffer.Generate(*Geometry);
  SetMaterial(Material);
}


void primitive::SetMaterial( std::shared_ptr<material> Material ) {
  this->Material = Material;
}


} // End of 'spectral' namespace
