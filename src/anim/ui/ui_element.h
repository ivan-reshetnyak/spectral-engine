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
  element( const mouse &Mouse, const rect<float> &BoundBox );
  virtual ~element();
  virtual void Update();
  virtual void Render();

protected:
  rect<float> BoundBox;
  const mouse &Mouse;

  virtual void OnClick();
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
