/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "ui_element.h"

namespace spectral {
namespace ui {


class hideable : public element {
public:
  hideable( const element &Element, std::shared_ptr<element> Base, bool Hidden = false );
  virtual ~hideable() = default;
  virtual void Update() override;
  virtual void Render() override;
  bool IsHidden() const;
  void Hide();
  void Show();
  void Toggle();

protected:
  bool Hidden;
  std::shared_ptr<element> Base;
};


} // End of 'ui' namespace
} // End of 'spectral' namespace
