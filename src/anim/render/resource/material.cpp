/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "gl/glew.h"

#include "material.h"

namespace spectral {


material::material( const std::string &Name, shader *Shader,
                    const color &Ka,
                    const color &Kd,
                    const color &Ks,
                    float Shininess ) :
    Ka(Ka), Kd(Kd), Ks(Ks), Shininess(Shininess), Shader(Shader), Name(Name) {
}


material::~material() {
}


void material::Apply( animation *Anim ) {
  int loc;
  // matr MatrWVP = Ani->World * Ani->Camera.Matr.M * Ani->Camera.Proj.M;
  // matr MatrNW = Ani->World.Inversing();

  Shader->Enable();

  /* TODO: Pass MVP matrices
  loc = glGetUniformLocation(Shader->GetProgram(), "MatrWVP");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (FLT *)MatrWVP);
  loc = glGetUniformLocation(Shader->GetProgram(), "MatrWorld");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (FLT *)Ani->World);
  loc = glGetUniformLocation(Shader->GetProgram(), "MatrView");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (FLT *)Ani->Camera.Matr.M);
  loc = glGetUniformLocation(Shader->GetProgram(), "MatrProj");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (FLT *)Ani->Camera.Proj.M);
  loc = glGetUniformLocation(Shader->GetProgram(), "MatrNWorld");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (FLT *)MatrNW);
  */

  loc = glGetUniformLocation(Shader->GetProgram(), "Time");
  if (loc != -1)
    glUniform1f(loc, (float)Anim->GetTimer().GetTime());

  /* TODO: Pass camera
  loc = glGetUniformLocation(Shader->GetProgram(), "CameraPos");
  if (loc != -1)
    glUniform3fv(loc, 1, &Ani->Camera.Loc.X);
  */

  /* Setup general uniforms */
  for (auto &i : UnifFloat)
    Shader->SetUniform(i.first.c_str(), i.second);
  for (auto &i : UnifInt)
    Shader->SetUniform(i.first.c_str(), i.second);
  /* TODO: Pass matrix uniforms
  for (auto &i : UnifMatr)
    Shader->SetUniform(i.first.c_str(), i.second);
  */

  /* TODO: Pass textures
  for (INT i = 0; i < Textures.size(); i++) {
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
