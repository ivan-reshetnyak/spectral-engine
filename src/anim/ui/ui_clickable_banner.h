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


class clickable_banner : public button {
public:
  using callback = std::function<void ()>;

  clickable_banner( animation *Anim, const rect<float> &BoundBox,
                    std::shared_ptr<material> Material,
                    const callback &Callback = [](){} );
  virtual ~clickable_banner() = default;
  virtual void Render() override;

protected:
  callback Callback;
  banner Banner;
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
