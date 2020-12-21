/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "ui_clickable.h"

namespace spectral {
namespace ui {


clickable::clickable( const mouse &Mouse, const rect<float> &BoundBox ) :
    BoundBox(BoundBox), Mouse(Mouse) {
}


clickable::~clickable() {
}


void clickable::Update() {
  if (Mouse[mouse::button::LEFT] == mouse::state::CLICK && BoundBox.IsInside(Mouse.GetCoordsRelative()))
    OnClick();
}


void clickable::Render() {
}


void clickable::OnClick() {
}


} // End of 'ui' namespace
} // End of 'spectral' namespace
