/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "def.h"

namespace spectral {


class camera {
public:
  enum class mode {
    DIRECTED, FOCUSED
  } Mode;

  vec Position, LookAt, Direction, Up, Right;
  matrix View, Projection, VP;
  float Near, Far, Top, Bottom, LeftP, RightP;

  camera( float Near, float Far, float Bottom,
          float Top, float LeftP, float RightP,
          const vec &Position = vec(0, 1, -1),
          const vec &LookAt = vec(0, 0, 0),
          const vec &Up0 = vec(0, 1, 0) );
  void UpdateMatrices( void );
  void Set( float Near, float Far, float Bottom,
            float Top, float LeftP, float RightP );
  void Set( const vec &Pos, const vec &At, const vec &Up );
  void Set( mode NewMode );
  void Move( const vec &Shift );
};


} // End of 'spectral' namespace
