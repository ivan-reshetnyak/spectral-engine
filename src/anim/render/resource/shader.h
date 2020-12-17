/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <string>

#include "def.h"

namespace spectral {


class shader {
private:
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


} // End of 'spectral' namespace
