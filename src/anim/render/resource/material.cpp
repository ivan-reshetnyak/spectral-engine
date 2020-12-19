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
    Shader->SetUniform(i.first.c_str(), i.second);
  for (auto &i : UnifDynFloat)
    Shader->SetUniform(i.first.c_str(), *i.second);
  for (auto &i : UnifConstInt)
    Shader->SetUniform(i.first.c_str(), i.second);
  for (auto &i : UnifDynInt)
    Shader->SetUniform(i.first.c_str(), *i.second);
  for (auto &i : UnifConstMatrix)
    Shader->SetUniform(i.first.c_str(), i.second);
  for (auto &i : UnifDynMatrix)
    Shader->SetUniform(i.first.c_str(), *i.second);
  for (auto &i : UnifConstVec)
    Shader->SetUniform(i.first.c_str(), i.second);
  for (auto &i : UnifDynVec)
    Shader->SetUniform(i.first.c_str(), *i.second);
}


void material::Apply( animation *Anim ) {
  Shader->Enable();
  SetUniforms();

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
  UnifConstFloat[std::string(Name)] = Val;
}


void material::SetUniform( const std::string &Name, float *Ptr ) {
  UnifDynFloat[std::string(Name)] = Ptr;
}


void material::SetUniform( const std::string &Name, int Val ) {
  UnifConstInt[std::string(Name)] = Val;
}


void material::SetUniform( const std::string &Name, int *Ptr ) {
  UnifDynInt[std::string(Name)] = Ptr;
}


void material::SetUniform( const std::string &Name, const vec &Val ) {
  UnifConstVec[std::string(Name)] = Val;
}


void material::SetUniform( const std::string &Name, vec *Ptr ) {
  UnifDynVec[std::string(Name)] = Ptr;
}


void material::SetUniform( const std::string &Name, const matrix &Val ) {
  UnifConstMatrix[std::string(Name)] = Val;
}


void material::SetUniform( const std::string &Name, matrix *Ptr ) {
  UnifDynMatrix[std::string(Name)] = Ptr;
}


} // End of 'spectral' namespace
