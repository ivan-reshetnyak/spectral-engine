/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../../def.h"
#include "../../../anim/animation.h"
#include "../../../util/resource_manager.h"
#include "shader.h"
#include "texture.h"

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
  std::vector<std::shared_ptr<texture>> Textures;
  std::unordered_map<std::string, float> UnifConstFloat;
  std::unordered_map<std::string, float *> UnifDynFloat;
  std::unordered_map<std::string, int> UnifConstInt;
  std::unordered_map<std::string, int *> UnifDynInt;
  std::unordered_map<std::string, vec> UnifConstVec;
  std::unordered_map<std::string, vec *> UnifDynVec;
  std::unordered_map<std::string, color> UnifConstCol;
  std::unordered_map<std::string, color *> UnifDynCol;
  std::unordered_map<std::string, matrix> UnifConstMatrix;
  std::unordered_map<std::string, matrix *> UnifDynMatrix;

  material( std::shared_ptr<shader> Shader = nullptr );
  void SetUniforms( void );

public:
  static manager Manager;
  ~material();
  void Apply( animation *Anim );
  material * SetUniform( const std::string &Name, float Val );
  material * SetUniform( const std::string &Name, float *Ptr );
  material * SetUniform( const std::string &Name, int Val );
  material * SetUniform( const std::string &Name, int *Ptr );
  material * SetUniform( const std::string &Name, const vec &Val );
  material * SetUniform( const std::string &Name, vec *Ptr);
  material * SetUniform( const std::string &Name, const color &Val );
  material * SetUniform( const std::string &Name, color *Ptr);
  material * SetUniform( const std::string &Name, const matrix &Val );
  material * SetUniform( const std::string &Name, matrix *Ptr);
  material * Add( std::shared_ptr<texture> Texture );
};


} // End of 'spectral' namespace
