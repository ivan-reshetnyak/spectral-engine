/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <string>
#include <unordered_map>

#include "def.h"
#include "util/resource_manager.h"

namespace spectral {


class shader {
private:
  friend class resource_manager<shader>;
  int Program;
  std::string Name;

  shader();
  shader( const std::string &FileNamePrefix );
  void Load( const std::string &FileNamePrefix );
  static void SaveLog( const std::string &Text );
  static char * LoadText( const std::string &FileName );
  // TODO: VOID SetUniform( const char *Name, const matr &Val );

public:
  ~shader();
  void Enable();
  void Disable();
  int GetProgram();
  void SetUniform( const std::string &Name, float Val );
  void SetUniform( const std::string &Name, int Val );
};


using shader_manager = resource_manager<shader>;


} // End of 'spectral' namespace
