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


class button : public clickable {
public:
  using callback = std::function<void ()>;

  button( const mouse &Mouse, const rect<float> &BoundBox,
          const callback &Callback = [](){} );
  button * Set( const callback &Callback );
  virtual ~button() = default;

protected:
  callback Callback;

  virtual void OnClick() override;
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
