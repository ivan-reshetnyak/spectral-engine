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


primitive::primitive( animation *Anim, const geometry &Geometry, std::shared_ptr<material> Material ) :
    Buffer(Geometry), Anim(Anim) {
}


primitive::~primitive() {
}


void primitive::Draw() {
  shader::SetLayout();
  Material->Apply(Anim);

  Render();

  buffer::Unbind();
  shader::Disable();
}


void primitive::Set( const geometry &Geometry, std::shared_ptr<material> Material ) {
  Buffer.Generate(Geometry);
  SetMaterial(Material);
}


void primitive::SetMaterial( std::shared_ptr<material> Material ) {
  this->Material = Material;
}


} // End of 'spectral' namespace
