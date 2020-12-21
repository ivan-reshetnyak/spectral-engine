/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "util/rect.h"
#include "../control/mouse.h"
#include "ui_element.h"

namespace spectral {
namespace ui {


class clickable : public element {
public:
  clickable( const mouse &Mouse, const rect<float> &BoundBox );
  virtual ~clickable();
  virtual void Update();
  virtual void Render();

protected:
  rect<float> BoundBox;
  const mouse &Mouse;

  virtual void OnClick();
};


} // End of 'ui' namespace
} // End of 'spectral' namespace