/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "def.h"

namespace spectral {


class world {
public:
  vec Wind;
  float Gravity;
  matrix Transformation;

  world( float Gravity = -9.81, const vec &Wind = vec(0, 0, 0) );
};


} // End of 'spectral' namespace
