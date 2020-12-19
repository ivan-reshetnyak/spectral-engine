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


material::material( std::shared_ptr<shader> Shader ) : Shader(Shader) {
}


material::~material() {
}


void material::SetUniforms( void ) {
  for (auto &i : UnifConstFloat)
    Shader->SetUniform(i.first, i.second);
  for (auto &i : UnifDynFloat)
    Shader->SetUniform(i.first, *i.second);
  for (auto &i : UnifConstInt)
    Shader->SetUniform(i.first, i.second);
  for (auto &i : UnifDynInt)
    Shader->SetUniform(i.first, *i.second);
  for (auto &i : UnifConstMatrix)
    Shader->SetUniform(i.first, i.second);
  for (auto &i : UnifDynMatrix)
    Shader->SetUniform(i.first, *i.second);
  for (auto &i : UnifConstVec)
    Shader->SetUniform(i.first, i.second);
  for (auto &i : UnifDynVec)
    Shader->SetUniform(i.first, *i.second);
}


void material::Apply( animation *Anim ) {
  Shader->Enable();
  SetUniforms();

  for (const auto &Texture : Textures) {
    Texture->Apply();
    Shader->SetUniform(Texture->GetName(), (int)Texture->GetSamplerNumber());
  }
}


material * material::SetUniform( const std::string &Name, float Val ) {
  UnifConstFloat[std::string(Name)] = Val;
  return this;
}


material * material::SetUniform( const std::string &Name, float *Ptr ) {
  UnifDynFloat[std::string(Name)] = Ptr;
  return this;
}


material * material::SetUniform( const std::string &Name, int Val ) {
  UnifConstInt[std::string(Name)] = Val;
  return this;
}


material * material::SetUniform( const std::string &Name, int *Ptr ) {
  UnifDynInt[std::string(Name)] = Ptr;
  return this;
}


material * material::SetUniform( const std::string &Name, const vec &Val ) {
  UnifConstVec[std::string(Name)] = Val;
  return this;
}


material * material::SetUniform( const std::string &Name, vec *Ptr ) {
  UnifDynVec[std::string(Name)] = Ptr;
  return this;
}


material * material::SetUniform( const std::string &Name, const matrix &Val ) {
  UnifConstMatrix[std::string(Name)] = Val;
  return this;
}


material * material::SetUniform( const std::string &Name, matrix *Ptr ) {
  UnifDynMatrix[std::string(Name)] = Ptr;
  return this;
}


material * material::Add( std::shared_ptr<texture> Texture ) {
  Textures.push_back(Texture);
  return this;
}


} // End of 'spectral' namespace
