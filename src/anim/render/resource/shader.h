/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <string>
#include <unordered_map>

#include "def.h"

namespace spectral {


class shader {
private:
  friend class shader_manager;
  int Program;
  std::string Name;

  shader();
  shader( const std::string &FileNamePrefix );
  void Load( const std::string &FileNamePrefix );
  static void SaveLog( const std::string &Text );
  static char * LoadText( const std::string &FileName );
  void SetUniform( const std::string &Name, float Val );
  void SetUniform( const std::string &Name, int Val );
  // TODO: VOID SetUniform( const char *Name, const matr &Val );

public:
  ~shader();
  void Enable();
  void Disable();
};


class shader_manager
{
public:
  shader_manager();
  ~shader_manager();
  shader * GetShader( const std::string &Name );

private:
  std::unordered_map<std::string, shader *> Shaders;
};


} // End of 'spectral' namespace
