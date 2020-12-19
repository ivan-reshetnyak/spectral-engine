/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <string>
#include <unordered_map>

#include "def.h"
#include "anim/animation.h"
#include "util/resource_manager.h"
#include "shader.h"

namespace spectral {


class material {
private:
  friend resource_manager_named<material>;
  class manager : public resource_manager_named<material> {
  public:
    ptr Get( const std::string &Name ) override {
      auto Iterator = Storage.find(Name);
      if (Iterator == Storage.end())
        // Resource not found
        return Storage.insert({Name, ptr(new material())}).first->second;
      return Iterator->second;
    }

    ptr Add( const std::string &Name, std::shared_ptr<shader> Shader ) {
      return Storage.insert({Name, ptr(new material(Shader))}).first->second;
    }
  };

  std::shared_ptr<shader> Shader;
  // TODO: std::vector<texture *> Textures;
  std::unordered_map<std::string, float> UnifConstFloat;
  std::unordered_map<std::string, float *> UnifDynFloat;
  std::unordered_map<std::string, int> UnifConstInt;
  std::unordered_map<std::string, int *> UnifDynInt;
  std::unordered_map<std::string, vec> UnifConstVec;
  std::unordered_map<std::string, vec *> UnifDynVec;
  std::unordered_map<std::string, matrix> UnifConstMatrix;
  std::unordered_map<std::string, matrix *> UnifDynMatrix;

  material( std::shared_ptr<shader> Shader = nullptr );
  void SetUniforms( void );

public:
  static manager Manager;
  ~material();
  // TODO: void AddTexture( texture *Texture );
  void Apply( animation *Anim );
  void SetUniform( const std::string &Name, float Val );
  void SetUniform( const std::string &Name, float *Ptr );
  void SetUniform( const std::string &Name, int Val );
  void SetUniform( const std::string &Name, int *Ptr );
  void SetUniform( const std::string &Name, const vec &Val );
  void SetUniform( const std::string &Name, vec *Ptr);
  void SetUniform( const std::string &Name, const matrix &Val );
  void SetUniform( const std::string &Name, matrix *Ptr);
};


} // End of 'spectral' namespace
