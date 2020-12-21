/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "ui_clickable.h"

namespace spectral {
namespace ui {


clickable::clickable( const mouse &Mouse, const rect<float> &BoundBox ) :
    bounded(BoundBox), Mouse(Mouse) {
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


button::button( const mouse &Mouse, const rect<float> &BoundBox, const callback &Callback ) :
    clickable(Mouse, BoundBox), Callback(Callback) {
}


button * button::Set( const callback &NewCallback ) {
  Callback = NewCallback;
  return this;
}


void button::OnClick() {
  Callback();
}


} // End of 'ui' namespace
} // End of 'spectral' namespace
