/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "gl/glew.h"

#include "tex_raw.h"

namespace spectral {
namespace tex {


raw::raw( const std::string &Name, int SamplerNumber ) : texture(Name, SamplerNumber) {
}


raw::raw( const std::string &Name, int SamplerNumber,
          int Width, int Height, std::shared_ptr<float> Pixels ) : texture(Name, SamplerNumber) {
  Load(Width, Height, Pixels);
}


void raw::Load( int Width, int Height, std::shared_ptr<float> Pixels ) {
  this->Width = Width;
  this->Height = Height;

  Apply();

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Set to 1 to support any image size
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA_FLOAT32_ATI, Width, Height, 0, GL_ALPHA, GL_FLOAT, &*Pixels);

  glTextureParameteri(ID, GL_TEXTURE_MAX_LEVEL, 0);
  glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_CLAMP);
}


} // End of 'tex' namespace
} // End of 'spectral' namespace
