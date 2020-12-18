/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "gl/glew.h"

#include "material.h"

namespace spectral {


material::manager material::Manager;


material::material( std::shared_ptr<shader> Shader,
                    const color &Ka, const color &Kd, const color &Ks,
                    float Shininess ) :
    Ka(Ka), Kd(Kd), Ks(Ks), Shininess(Shininess), Shader(Shader) {
}


material::~material() {
}


void material::Apply( animation *Anim ) {
  Shader->Enable();

  Shader->SetUniform("Time", (float)Anim->GetTimer().GetTime());
  Shader->SetUniform("World", Anim->World);
  Shader->SetUniform("VP", Anim->Camera.VP);

  /* Pass generic uniforms */
  for (auto &i : UnifFloat)
    Shader->SetUniform(i.first.c_str(), i.second);
  for (auto &i : UnifInt)
    Shader->SetUniform(i.first.c_str(), i.second);

  /* TODO: Pass textures
  for (INT i = 0; i < Textures.size(); ++i) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, Textures[i]->GetNo());
    loc = glGetUniformLocation(Shader->GetProgram(), Textures[i]->Name);
    if (loc != -1)
      glUniform1i(loc, i);
  }
  */
}


void material::SetUniform( const std::string &Name, float Val ) {
  UnifFloat[std::string(Name)] = Val;
}


void material::SetUniform( const std::string &Name, int Val ) {
  UnifInt[std::string(Name)] = Val;
}


} // End of 'spectral' namespace
