/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "util/rect.h"
#include "../control/mouse.h"
#include "ui_bounded.h"

namespace spectral {
namespace ui {


class clickable : public bounded {
public:
  clickable( const mouse &Mouse, const rect<float> &BoundBox );
  virtual ~clickable();
  virtual void Update();
  virtual void Render();

protected:
  const mouse &Mouse;

  virtual void OnClick();
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
