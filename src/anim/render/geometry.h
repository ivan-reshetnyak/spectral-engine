/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "vertex.h"

namespace spectral {


class geometry {
public:
  virtual void Render() = 0;
  vertex *VertexArray;

protected:
  geometry( void );
  virtual ~geometry( void );
};


} // End of 'spectral' namespace
