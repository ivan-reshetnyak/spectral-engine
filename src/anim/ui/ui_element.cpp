/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "ui_element.h"

namespace spectral {
namespace ui {


element::element( const mouse &Mouse, const rect<float> &BoundBox ) :
    BoundBox(BoundBox), Mouse(Mouse) {
}


element::~element() {
}


void element::Update() {
  if (Mouse[mouse::button::LEFT] == mouse::state::CLICK && BoundBox.IsInside(Mouse.GetCoordsRelative()))
    OnClick();
}


void element::Render() {
}


void element::OnClick() {
}


} // End of 'ui' namespace
} // End of 'spectral' namespace
