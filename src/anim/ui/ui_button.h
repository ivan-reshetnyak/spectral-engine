/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <functional>

#include "../render/resource/material.h"
#include "../render/prim/points.h"
#include "ui_banner.h"
#include "ui_clickable.h"

namespace spectral {
namespace ui {


class button : public clickable {
public:
  using callback = std::function<void ()>;

  button( animation *Anim, const rect<float> &BoundBox,
          std::shared_ptr<material> Material,
          const callback &Callback = [](){} );
  button * Set( const callback &Callback );
  virtual ~button();
  virtual void Render() override;

protected:
  callback Callback;
  banner Banner;

  virtual void OnClick() override;
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
