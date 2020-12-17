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

    ptr Add( const std::string &Name, std::shared_ptr<shader> Shader,
             const color &Ka = color(0.6f, 0.6f, 0.6f, 1.0f),
             const color &Kd = color(0.9f, 0.9f, 0.9f, 1.0f),
             const color &Ks = color(1.0f, 1.0f, 1.0f, 1.0f),
             float Shininess = 1 ) {
      return Storage.insert({Name, ptr(new material(Shader, Ka, Kd, Ks, Shininess))}).first->second;
    }
  };

  color
    Ka,  // Ambient
    Kd,  // Diffuse
    Ks;  // Specular
  float Shininess;
  std::shared_ptr<shader> Shader;
  // TODO: std::vector<texture *> Textures;
  std::unordered_map<std::string, float> UnifFloat;
  std::unordered_map<std::string, int> UnifInt;
  // TODO: std::unordered_map<std::string, matr> UnifMatr;

  material( std::shared_ptr<shader> Shader = nullptr,
            const color &Ka = color(0.6f, 0.6f, 0.6f, 1.0f),
            const color &Kd = color(0.9f, 0.9f, 0.9f, 1.0f),
            const color &Ks = color(1.0f, 1.0f, 1.0f, 1.0f),
            float Shininess = 1 );

public:
  static manager Manager;
  ~material();
  // TODO: void AddTexture( texture *Texture );
  void Apply( animation *Anim );
  void SetUniform( const std::string &Name, float Val );
  void SetUniform( const std::string &Name, int Val );
  // TODO: void SetUniform( const std::string &Name, const matr &Val );
};


} // End of 'spectral' namespace
