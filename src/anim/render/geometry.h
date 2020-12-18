/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "util/resource_manager.h"
#include "vertex.h"

namespace spectral {

class geometry {
public:
  int
    NumOfV, NumOfI,
    *Indices;
  vertex *Vertices;

  geometry( void );
  geometry( int NumOfV, vertex *Vertices, int NumOfI, int *Indices );
  ~geometry( void );
};


} // End of 'spectral' namespace
