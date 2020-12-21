/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <memory>
#include <vector>

#include "ui_element.h"

namespace spectral {
namespace ui {


class layout : public element {
public:
  layout() = default;
  virtual ~layout() = default;
  virtual void Update();
  virtual void Render();
  layout * Add( std::shared_ptr<element> NewElement );

protected:
  std::vector<std::shared_ptr<element>> Elements;
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
