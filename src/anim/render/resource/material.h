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
  friend class resource_manager<material>;
  std::string Name;
  color
    Ka,  // Ambient
    Kd,  // Diffuse
    Ks;  // Specular
  float Shininess;
  shader *Shader;
  // TODO: std::vector<texture *> Textures;

  std::unordered_map<std::string, float> UnifFloat;
  std::unordered_map<std::string, int> UnifInt;
  // TODO: std::unordered_map<std::string, matr> UnifMatr;

public:
  material( const std::string &Name, shader *Shader,
            const color &Ka = color(0.6f, 0.6f, 0.6f, 1.0f),
            const color &Kd = color(0.9f, 0.9f, 0.9f, 1.0f),
            const color &Ks = color(1.0f, 1.0f, 1.0f, 1.0f),
            float Shininess = 1 );
  ~material();
  // TODO: void AddTexture( texture *Texture );
  void Apply( animation *Anim );
  void SetUniform( const std::string &Name, float Val );
  void SetUniform( const std::string &Name, int Val );
  // TODO: void SetUniform( const std::string &Name, const matr &Val );
};


using material_manager = resource_manager<material>;


} // End of 'spectral' namespace
