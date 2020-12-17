/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "math/color.h"
#include "math/vec.h"

namespace spectral {


using color = color_t<float>;
using vec = vec_t<float>;


#define OFFSET(Type, Field) \
  ((void *)(&((Type *)0)->Field))

#define SIZE(Array) \
  (sizeof(Array) / sizeof((Array)[0]))


} // End of 'spectral' namespace
