/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "gl/glew.h"

#include "texture.h"

#define TEXTURE_SAMPLER(N) \
  (GL_TEXTURE0 + N)


namespace spectral {


unsigned texture::LastAppliedTextureID = -1;


texture::texture( int SamplerNumber ) : Sampler(SamplerNumber), Width(0), Height(0) {
  glGenTextures(1, &ID);
}


texture::texture( int SamplerNumber, const std::string &FileName ) : texture(SamplerNumber) {
  Load(FileName);
}


texture::texture( int SamplerNumber, int Width, int Height, const float *Pixels ) : texture(SamplerNumber) {
  Load(Width, Height, Pixels);
}


void texture::Load( int Width, int Height, const float *Pixels ) {
  this->Width = Width;
  this->Height = Height;

  glActiveTexture(TEXTURE_SAMPLER(Sampler));
  glBindTexture(GL_TEXTURE_2D, ID);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Set to 1 to support any image size
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA_FLOAT32_ATI, Width, Height, 0, GL_ALPHA, GL_FLOAT, Pixels);

  glTextureParameteri(ID, GL_TEXTURE_MAX_LEVEL, 0);
  glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_CLAMP);
}


void texture::Load( const std::string &FileName ) {
  // TODO: Use libpng
}

} // End of 'spectral' namespace
