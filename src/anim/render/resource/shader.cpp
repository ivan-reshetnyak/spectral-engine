/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include <cstdio>

#include <array>

#include "gl/glew.h"

#include "def.h"
#include "../vertex.h"
#include "shader.h"

namespace spectral {


shader::manager shader::Manager;


shader::shader() {
}


shader::shader( const std::string &FileNamePrefix ) {
  std::string Path = "../assets/shaders/" + FileNamePrefix + "/";
  Load(Path);
}


shader::~shader() {
}


void shader::Load( const std::string &FileNamePrefix ) {
  static const int MaxNumOfShaders = 5;
  int Result, i;
  char *ShaderSource;
  std::array<UINT, MaxNumOfShaders>
    Shaders = { 0 },
    ShTypes = { GL_VERTEX_SHADER, GL_GEOMETRY_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_FRAGMENT_SHADER };
  std::array<std::string, MaxNumOfShaders> Suff = { "vert", "geom", "tctrl", "teval", "frag" };
  bool IsOk = true;
  static char Buf[1000];  // Needs to be char *

  int NumOfShaders = Shaders.size();
  for (i = 0; i < NumOfShaders; ++i) {
    sprintf(Buf, "%s.%s", FileNamePrefix.c_str(), Suff[i].c_str());
    if ((ShaderSource = LoadText(Buf)) == nullptr)
      continue;
    if ((Shaders[i] = glCreateShader(ShTypes[i])) == 0) {
      IsOk = false;
      SaveLog("Error creating shader");
      break;
    }

    glShaderSource(Shaders[i], 1, &ShaderSource, nullptr);
    delete ShaderSource;
    glCompileShader(Shaders[i]);
    glGetShaderiv(Shaders[i], GL_COMPILE_STATUS, &Result);
    if (Result != 1) {
      glGetShaderInfoLog(Shaders[i], sizeof(Buf), &Result, Buf);
      SaveLog(Buf);
      IsOk = FALSE;
      break;
    }
  }

  if (IsOk)
    if ((Program = glCreateProgram()) == 0)
      IsOk = FALSE;
    else {
      for (i = 0; i < NumOfShaders; ++i)
        if (Shaders[i] != 0)
          glAttachShader(Program, Shaders[i]);
      glLinkProgram(Program);
      glGetProgramiv(Program, GL_LINK_STATUS, &Result);
      if (Result != 1) {
        glGetProgramInfoLog(Program, sizeof(Buf), &Result, Buf);
        SaveLog(Buf);
        IsOk = FALSE;
      }
    }
  if (!IsOk) {
    for (i = 0; i < NumOfShaders; ++i)
      if (Shaders[i] != 0) {
        if (Program != 0)
          glDetachShader(Program, Shaders[i]);
        glDeleteShader(Shaders[i]);
      }
    if (Program != 0)
      glDeleteProgram(Program);
    Program = 0;
    return;
  }
  Name = FileNamePrefix;
}


// cstdio is faster than streams, right?
void shader::SaveLog( const std::string &Text ) {
  FILE *F;

  if ((F = fopen("../logs/shader.log", "a")) != nullptr) {
    fprintf(F, "%s\n", Text.c_str());
    fclose(F);
  }
}

char * shader::LoadText( const std::string &FileName ) {
  FILE *F;
  char *mem = nullptr;

  if ((F = fopen(FileName.c_str(), "r")) != nullptr) {
    long len;

    fseek(F, 0, SEEK_END);
    len = ftell(F);

    if ((mem = (char *)malloc(len + 1)) != nullptr) {
      fseek(F, 0, SEEK_SET);
      len = fread(mem, 1, len, F);
      mem[len] = 0;
    }
    fclose(F);
  }
  return mem;
}


void shader::Enable() {
  glUseProgram(Program);
}


void shader::Disable() {
  glUseProgram(0);
}


void shader::SetUniform( const std::string &Name, float Val ) const {
  int loc = glGetUniformLocation(Program, Name.c_str());
  if (loc != -1)
    glUniform1f(loc, Val);
}


void shader::SetUniform( const std::string &Name, int Val ) const {
  int loc = glGetUniformLocation(Program, Name.c_str());
  if (loc != -1)
    glUniform1i(loc, Val);
}


void shader::SetUniform( const std::string &Name, matrix &Val ) const {
  int loc = glGetUniformLocation(Program, Name.c_str());
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, false, Val.GetData());
}


void shader::SetUniform( const std::string &Name, vec &Val ) const {
  int loc = glGetUniformLocation(Program, Name.c_str());
  if (loc != -1)
    glUniform3f(loc, Val.X, Val.Y, Val.Z);
}


int shader::GetProgram() {
  return Program;
}


void shader::SetLayout( vertex * Vertices ) {
  auto Layout = Vertices->GetLayout();
  for (const auto &it : Layout ) {
    glVertexAttribPointer(it.Index, it.Size, it.Type, it.IsNormalised, it.Stride, it.Pointer);
    glEnableVertexAttribArray(it.Index);
  }
}


} // End of 'spectral' namespace
