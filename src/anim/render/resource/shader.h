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
  friend resource_manager_named<shader>;
  class manager : public resource_manager_named<shader> {
  public:
    ptr Get( const std::string &Name ) override {
      auto Iterator = Storage.find(Name);
      if (Iterator == Storage.end())
        // Resource not found
        return Storage.insert({Name, ptr(new shader(Name))}).first->second;
      return Iterator->second;
    }
  };

  int Program;
  std::string Name;

  shader();
  shader( const std::string &FileNamePrefix );
  void Load( const std::string &FileNamePrefix );
  static void SaveLog( const std::string &Text );
  static char * LoadText( const std::string &FileName );

public:
  ~shader();
  void Enable();
  static void Disable();
  int GetProgram();
  void SetUniform( const std::string &Name, float Val ) const;
  void SetUniform( const std::string &Name, int Val ) const;
  void SetUniform( const std::string &Name, matrix &Val ) const;
  static void SetLayout();

  static manager Manager;
};


} // End of 'spectral' namespace
