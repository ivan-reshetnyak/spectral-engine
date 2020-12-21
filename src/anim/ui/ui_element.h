/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "util/rect.h"
#include "../control/mouse.h"

namespace spectral {
namespace ui {


class element {
public:
  element() = default;
  virtual ~element() = default;
  virtual void Update();
  virtual void Render();
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
