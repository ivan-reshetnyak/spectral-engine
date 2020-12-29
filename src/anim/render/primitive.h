/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <memory>

#include <windows.h>

#include "glew/glew.h"

#include "../../def.h"
#include "../animation.h"
#include "buffer.h"
#include "geometry.h"
#include "resource/material.h"

namespace spectral {


class primitive {
public:
  primitive() = default;
  primitive( animation *Anim );
  primitive( animation *Anim, std::shared_ptr<geometry> Geometry, std::shared_ptr<material> Material );
  ~primitive();
  void Set( animation *Anim );
  void Set( std::shared_ptr<geometry> Geometry, std::shared_ptr<material> Material );
  void SetMaterial( std::shared_ptr<material> Material );
  void Draw();

protected:
  buffer Buffer;
  std::shared_ptr<geometry> Geometry;
  std::shared_ptr<material> Material;
  animation *Anim;

  primitive & operator=( const primitive &&P );
  primitive & operator=( const primitive &P ) = delete;
  primitive( const primitive &P ) = delete;
  virtual void Render() = 0;
};


} // End of 'spectral' namespace
