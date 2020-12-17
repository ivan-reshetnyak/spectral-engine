/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <memory>

#include <windows.h>

#include "gl/glew.h"

#include "def.h"
#include "../animation.h"
#include "buffer.h"
#include "geometry.h"
#include "resource/material.h"

namespace spectral {


class primitive {
public:
  primitive( animation *Anim );
  primitive( animation *Anim, const geometry &Geometry, std::shared_ptr<material> Material );
  ~primitive();
  void Set( const geometry &Geometry, std::shared_ptr<material> Material );
  void SetMaterial( std::shared_ptr<material> Material );
  void Draw();

protected:
  buffer Buffer;
  std::shared_ptr<material> Material;
  animation *Anim;

  primitive( const primitive &P ) = delete;
  primitive & operator=( const primitive &P ) = delete;
  virtual void Render() = 0;
};


} // End of 'spectral' namespace
