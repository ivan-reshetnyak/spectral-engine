/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <functional>

#include "../render/resource/material.h"
#include "../render/prim/points.h"
#include "ui_bounded.h"

namespace spectral {
namespace ui {


class banner : public bounded {
public:
  banner( animation *Anim, const rect<float> &BoundBox,
          std::shared_ptr<material> Material );
  virtual ~banner() = default;
  virtual void Render() override;

protected:
  std::shared_ptr<material> Material;
  prim::points Primitive;
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
