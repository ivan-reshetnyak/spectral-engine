/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "gl/glew.h"

#include "texture.h"

namespace spectral {


unsigned texture::LastAppliedTextureID = -1;


texture::texture( const std::string &Name, int SamplerNumber ) :
    Sampler(SamplerNumber), Width(0), Height(0), Name(Name) {
  glGenTextures(1, &ID);
}


const std::string & texture::GetName() const {
  return Name;
}


unsigned texture::GetSamplerNumber() const {
  return Sampler;
}


unsigned texture::SAMPLER( int N ) {
  return GL_TEXTURE0 + N;
}


void texture::Apply() const {
  if (LastAppliedTextureID != ID) {
    glActiveTexture(SAMPLER(Sampler));
    glBindTexture(GL_TEXTURE_2D, ID);
    LastAppliedTextureID = ID;
  }
}


} // End of 'spectral' namespace
