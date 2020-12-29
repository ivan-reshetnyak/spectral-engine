/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "../../util/rect.h"
#include "ui_element.h"

namespace spectral {
namespace ui {


class bounded : public element {
public:
  bounded( const rect<float> &BoundBox );
  virtual ~bounded() = default;

protected:
  rect<float> BoundBox;
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
