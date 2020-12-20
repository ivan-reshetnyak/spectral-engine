/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <functional>

#include "../render/resource/material.h"
#include "../render/prim/points.h"
#include "ui_element.h"

namespace spectral {
namespace ui {


class button : public element {
public:
  using callback = std::function<void ()>;

  button( animation *Anim,
          const element &Base, const callback &Callback,
          std::shared_ptr<material> Material );
  virtual ~button();
  virtual void Render() override;

protected:
  std::shared_ptr<material> Material;
  callback Callback;
  prim::points Primitive;

  virtual void OnClick();
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
