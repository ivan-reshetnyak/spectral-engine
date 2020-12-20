/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <cstdlib>

namespace spectral {


__inline float random() {
  return (float)rand() / RAND_MAX;
}


__inline float random( float From, float To ) {
  return From + random() * (To - From);
}


} // End of 'spectral' namespace
